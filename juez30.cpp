#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>
#include <queue>

using namespace std;


template <typename Valor>
class Arista {
public:
   Arista() : pimpl(nullptr) {}
   Arista(int v, int w, Valor valor) : pimpl(std::make_shared<Arista_impl>(v, w, valor)) {}
   
   int uno() const { return pimpl->v; }
   int otro(int u) const { return (u == pimpl->v) ? pimpl->w : pimpl->v; }
   Valor valor() const { return pimpl->valor; }
   
   void print(std::ostream & o = std::cout) const {
      o << "(" << pimpl->v << ", " << pimpl->w << ", " << pimpl->valor << ")";
   }
   
   bool operator<(Arista<Valor> const& b) const {
      return valor() < b.valor();
   }
   bool operator>(Arista<Valor> const& b) const {
      return b.valor() < valor();
   }
private:
   struct Arista_impl {
      int v, w;
      Valor valor;
      Arista_impl(int v, int w, Valor valor) : v(v), w(w), valor(valor) {}
   };
   
   std::shared_ptr<Arista_impl> pimpl; // puntero a la arista "de verdad"
};

template <typename Valor>
inline std::ostream& operator<<(std::ostream & o, Arista<Valor> const& ar) {
   ar.print(o);
   return o;
}


template <typename Valor>
using AdysVal = std::vector<Arista<Valor> >;  // lista de adyacentes a un vértice

template <typename Valor>
class GrafoValorado {
public:
   
   /**
    * Crea un grafo valorado con V vértices, sin aristas.
    */
   GrafoValorado(int V) : _V(V), _A(0), _ady(_V) { }
   
   /**
    * Crea un grafo valorado a partir de los datos en el flujo de entrada (si puede).
    * primer es el índice del primer vértice del grafo en el entrada.
    */
   GrafoValorado(std::istream & flujo, int primer = 0) : _A(0) {
      flujo >> _V;
      if (!flujo) return;
      _ady.resize(_V);
      int E, v, w;
      Valor c;
      flujo >> E;
      while (E--) {
         flujo >> v >> w >> c;
         Arista<int> a(v - primer, w - primer, c);
         ponArista(a);
      }
   }

   /**
    * Devuelve el número de vértices del grafo.
    */
   int V() const { return _V; }
   
   /**
    * Devuelve el número de aristas del grafo.
    */
   int A() const { return _A; }
   
   /**
    * Añade una arista al grafo.
    * @throws invalid_argument si algún vértice no existe
    */
   void ponArista(Arista<Valor> arista) {
      int v = arista.uno(), w = arista.otro(v);
      if (v < 0 || v >= _V || w < 0 || w >= _V)
         throw std::invalid_argument("Vertice inexistente");
      ++_A;
      _ady[v].push_back(arista);
      _ady[w].push_back(arista);
   }
   
   /**
    * Devuelve la lista de adyacentes de v.
    * @throws invalid_argument si v no existe
    */
   AdysVal<Valor> const& ady(int v) const {
      if (v < 0 || v >= _V)
         throw std::invalid_argument("Vertice inexistente");
      return _ady[v];
   }
   
   /**
    * Devuelve las aristas del grafo.
    */
   std::vector<Arista<Valor> > aristas() const {
      std::vector<Arista<Valor> > ars;
      for (int v = 0; v < V(); ++v)
         for (auto arista : ady(v))
            if (v < arista.otro(v))
               ars.push_back(arista);
      return ars;
   }
   
   /**
    * Muestra el grafo en el stream de salida o
    */
   void print(std::ostream& o = std::cout) const {
      o << _V << " vértices, " << _A << " aristas\n";
      for (auto v = 0; v < _V; ++v) {
         o << v << ": ";
         for (auto const& w : _ady[v]) {
            o << w << " ";
         }
         o << "\n";
      }
   }
   
private:
   int _V;   // número de vértices
   int _A;   // número de aristas
   std::vector<AdysVal<Valor> > _ady;   // vector de listas de adyacentes
};


/**
 * Para mostrar grafos por la salida estándar.
 */

template <typename Valor>
inline std::ostream& operator<<(std::ostream & o, GrafoValorado<Valor> const& g) {
   g.print(o);
   return o;
}


// T es el tipo de las prioridades
// Comparator dice cuándo un valor de tipo T es más prioritario que otro
template <typename T = int, typename Comparator = std::less<T> >
class IndexPQ {
public:
   // registro para las parejas < elem, prioridad >
   struct Par {
      int elem;
      T prioridad;
   };
   
private:
   // vector que contiene los datos (pares < elem, prio >)
   std::vector<Par> array;     // primer elemento en la posición 1
   
   // vector que contiene las posiciones en array de los elementos
   std::vector<int> posiciones;   // un 0 indica que el elemento no está
   
   /* Objeto función que sabe comparar prioridades.
    antes(a,b) es cierto si a es más prioritario que b */
   Comparator antes;
   
public:
   IndexPQ(int N, Comparator c = Comparator()) : array(1), posiciones(N, 0), antes(c) {}
   
   IndexPQ(IndexPQ<T,Comparator> const&) = default;
   
   IndexPQ<T,Comparator>& operator=(IndexPQ<T,Comparator> const&) = default;
   
   ~IndexPQ() = default;
   
   // e debe ser uno de los posibles elementos
   void push(int e, T const& p) {
      if (posiciones.at(e) != 0)
         throw std::invalid_argument("No se pueden insertar elementos repetidos.");
      else {
         Par par;
         par.elem = e;
         par.prioridad = p;
         array.push_back(par);
         posiciones[e] = size();
         flotar(size());
      }
   }
   
   void update(int e, T const& p) {
      int i = posiciones.at(e);
      if (i == 0) // el elemento e se inserta por primera vez
         push(e, p);
      else {
         array[i].prioridad = p;
         if (i != 1 && antes(array[i].prioridad, array[i/2].prioridad))
            flotar(i);
         else // puede hacer falta hundir a e
            hundir(i);
      }
   }
   
   int size() const {
      return int(array.size()) - 1;
   }
   
   bool empty() const {
      return size() == 0;
   }
   
   Par const& top() const {
      if (size() == 0)
         throw std::domain_error("No se puede consultar el primero de una cola vacia");
      else return array[1];
   }
   
   void pop() {
      if (size() == 0) throw std::domain_error("No se puede eliminar el primero de una cola vacía.");
      else {
         posiciones[array[1].elem] = 0; // para indicar que no está
         if (size() > 1) {
            array[1] = std::move(array.back());
            posiciones[array[1].elem] = 1;
            array.pop_back();
            hundir(1);
         } else
            array.pop_back();
      }
   }

private:
   
   void flotar(int i) {
      Par parmov = std::move(array[i]);
      int hueco = i;
      while (hueco != 1 && antes(parmov.prioridad, array[hueco/2].prioridad)) {
         array[hueco] = std::move(array[hueco/2]); posiciones[array[hueco].elem] = hueco;
         hueco /= 2;
      }
      array[hueco] = std::move(parmov); posiciones[array[hueco].elem] = hueco;
   }
   
   void hundir(int i) {
      Par parmov = std::move(array[i]);
      int hueco = i;
      int hijo = 2*hueco; // hijo izquierdo, si existe
      while (hijo <= size())  {
         // cambiar al hijo derecho de i si existe y va antes que el izquierdo
         if (hijo < size() && antes(array[hijo + 1].prioridad, array[hijo].prioridad))
            ++hijo;
         // flotar el hijo si va antes que el elemento hundiéndose
         if (antes(array[hijo].prioridad, parmov.prioridad)) {
            array[hueco] = std::move(array[hijo]); posiciones[array[hueco].elem] = hueco;
            hueco = hijo; hijo = 2*hueco;
         }
         else break;
      }
      array[hueco] = std::move(parmov); posiciones[array[hueco].elem] = hueco;
   }
   
};

void relajar(Arista<long long int> a, vector<long long int>& dist, vector<Arista<long long int> >& ulti, vector<long long int>& aristas, IndexPQ<long long int>& pq, int v){
    int w = a.otro(v);
    if (dist[w] > dist[v] + a.valor()){
        dist[w] = dist[v] + a.valor();
        aristas[w] = aristas[v] + 1;
        ulti[w] = a;
        pq.update(w, dist[w]); 
    }
    else if (dist[w] == dist[v] + a.valor()){
       if (aristas[w] > aristas[v] + 1){
          aristas[w] = aristas[v] + 1;
          ulti[w] = a;
       }
    }
    
}

void Dijkstra(const GrafoValorado<long long int>& g, long long int origen, vector<long long int>& aristas, vector<long long int>& dist, vector<Arista<long long int> >& ulti, IndexPQ<long long int>& pq){
    dist[origen] = 0;
    aristas[origen] = 0;
    pq.push(origen, 0);
    while (!pq.empty()){
        int v = pq.top().elem;
        pq.pop();
        for (auto a : g.ady(v)){
            relajar(a, dist, ulti, aristas, pq, v);
        }
    }
}

/*void bfs(const GrafoValorado& G, int v, vector<bool>& marcaje, int& cont){
   queue<int> q;
   q.push(v);
   marcaje[v] = true;
   int nivel = 0;
   int elems = 1;
   while (!q.empty()){
       int k = q.front();
       q.pop();
       elems--;
       for (auto w : G.ady(k)){
           if (!marcaje[w]){
               marcaje[w] = true;
               q.push(w);
            }  
        }
        if (elems == 0) {
           nivel++;
           elems = q.size();
        }
   }
}*/

bool resuelveCaso() {
   long long int N, M;
   cin >> N >> M;
   if (!cin) return false;
   GrafoValorado<long  long int> g(N);
   GrafoValorado<long long int> g_unos(N);
   for (long long int i = 0; i < M; ++i){
       long long int a, b, c;
       cin >> a >> b >> c;
       Arista<long long int> arista1(a - 1, b - 1, c);
       Arista<long long int> arista2(a - 1, b - 1, 1);
       g.ponArista(arista1);
       g_unos.ponArista(arista2);
   }

   int K;
   cin >> K;
   for (int i = 0; i < K; ++i){
       long long int origen, destino;
       cin >> origen >> destino;
       vector<long long int> dist(g.V(), 500000000);
       vector<long long int> aristas(g.V(), 5000000);
       vector<Arista<long long int> > ulti(g.V());
       IndexPQ<long long int> pq(g.V());
       Dijkstra(g, origen - 1, aristas, dist, ulti, pq);
       vector<long long int> dist2(g.V(), 500000000);
       vector<long long int> aristas2(g.V(), 5000000);
       vector<Arista<long long int> > ulti2(g.V());
       IndexPQ<long long int> pq2(g.V());
       Dijkstra(g_unos, origen - 1, aristas2, dist2, ulti2, pq2);
       
       if (dist[destino - 1] != 500000000){
           if (aristas[destino - 1] == dist2[destino - 1]) cout << dist[destino - 1] << " SI\n";
           else cout << dist[destino - 1] << " NO\n";
       }
       else cout << "SIN CAMINO\n";
   }
   cout << "---\n";

   return true;
}


int main() {
    while (resuelveCaso());
    return 0;
}