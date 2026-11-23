#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>
#include <climits>
#include <unordered_map>

using namespace std;

template <typename Valor>
class AristaDirigida {
public:
   AristaDirigida(): pimpl(nullptr) {}
   AristaDirigida(int v, int w, Valor valor): pimpl(std::make_shared<AristaDirigida_impl>(v, w, valor)) {}
   int desde() const { return pimpl->v; }
   int hasta() const { return pimpl->w; }
   Valor valor() const { return pimpl->valor; }

   void print(std::ostream & o = std::cout) const {
      o << "(" << pimpl->v << ", " << pimpl->w << ", " << pimpl->valor << ")";
   }

   bool operator<(AristaDirigida<Valor> const& b) const {
      return valor() < b.valor();
   }
   bool operator>(AristaDirigida<Valor> const& b) const {
      return b.valor() < valor();
   }
private:
   struct AristaDirigida_impl {
      int v, w;
      Valor valor;
      AristaDirigida_impl(int v, int w, Valor valor) : v(v), w(w), valor(valor) {}
   };
   std::shared_ptr<AristaDirigida_impl> pimpl;
};

template <typename Valor>
inline std::ostream& operator<<(std::ostream & o, AristaDirigida<Valor> const& ar){
   ar.print(o);
   return o;
}



template <typename Valor>
using AdysDirVal = std::vector<AristaDirigida<Valor> >;  // lista de adyacentes a un vértice

template <typename Valor>
class DigrafoValorado {
public:
   
   /**
    * Crea un grafo con V vértices.
    */
   DigrafoValorado(int v) : _V(v), _A(0), _ady(_V) {}
   
   /**
    * Crea un grafo dirigido y valorado a partir de los datos en el flujo de entrada (si puede).
    * primer es el índice del primer vértice del grafo en el entrada.
    */
   DigrafoValorado(std::istream & flujo, int primer = 0) : _A(0) {
      flujo >> _V;
      if (!flujo) return;
      _ady.resize(_V);
      int E, v, w;
      Valor c;
      flujo >> E;
      while (E--) {
         flujo >> v >> w >> c;
         AristaDirigida<int> a(v - primer, w - primer, c);
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
    * Añade la arista dirigida v-w al grafo.
    * @throws invalid_argument si algún vértice no existe
    */
   void ponArista(AristaDirigida<Valor> arista) {
      int v = arista.desde(), w = arista.hasta();
      if (v < 0 || v >= _V || w < 0 || w >= _V)
         throw std::invalid_argument("Vertice inexistente");
      ++_A;
      _ady[v].push_back(arista);
   }
   
   /**
    * Comprueba si hay arista de v a w.
    */
   bool hayArista(int v, int w) const {
      for (auto a : _ady[v])
         if (a.hasta() == w) return true;
      return false;
   }
   
   /**
    * Devuelve la lista de adyacencia de v.
    * @throws invalid_argument si v no existe
    */
   AdysDirVal<Valor> const& ady(int v) const {
      if (v < 0 || v >= _V)
         throw std::invalid_argument("Vertice inexistente");
      return _ady[v];
   }
   
   /**
    * Devuelve el grafo dirigido inverso.
    */
   DigrafoValorado<Valor> inverso() const {
      DigrafoValorado<Valor> inv(_V);
      for (auto v = 0; v < _V; ++v) {
         for (auto a : _ady[v]) {
             AristaDirigida<int> ar(a.hasta(), a.desde(), a.valor());
            inv.ponArista(ar);
         }
      }
      return inv;
   }
   
   /**
    * Muestra el grafo en el stream de salida o
    */
   void print(std::ostream& o = std::cout) const {
      o << _V << " vértices, " << _A << " aristas\n";
      for (auto v = 0; v < _V; ++v) {
         o << v << ": ";
         for (auto a : _ady[v]) {
            o << a << " ";
         }
         o << "\n";
      }
   }
   
private:
   int _V;   // número de vértices
   int _A;   // número de aristas
   std::vector<AdysDirVal<Valor> > _ady;   // vector de listas de adyacentes
   
};

/**
 * Para mostrar grafos por la salida estándar.
 */
template <typename Valor>
inline std::ostream& operator<<(std::ostream& o,const DigrafoValorado<Valor>& g){
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

void relajar(AristaDirigida<long long int> a, vector<long long int>& dist, IndexPQ<long long int>& pq, unordered_map<int, int>& cargas){
    long long int v = a.desde();
    long long int w = a.hasta();
    if (dist[w] > dist[v] + a.valor() + cargas[w]){
        dist[w] = dist[v] + a.valor() + cargas[w];
        pq.update(w, dist[w]); 
    }
}

void Dijkstra(const DigrafoValorado<long long int>& g, long long int origen, vector<long long int>& dist, IndexPQ<long long int>& pq, unordered_map<int, int>& cargas){
    dist[origen] = cargas[origen];
    pq.push(origen, dist[origen]);
    while (!pq.empty()){
        long int v = pq.top().elem;
        pq.pop();
        for (auto a : g.ady(v)){
            relajar(a, dist, pq, cargas);
        }
    }
}

bool resuelveCaso() {
   long long int N;
   cin >> N;
   if (N == 0) return false;
   unordered_map<int, int> cargas;
   for (long long int i = 0; i < N; ++i){
       long long int c;
       cin >> c;
       cargas[i] = c;
   }
   DigrafoValorado<long long int> g(N);
   long long int M;
   cin >> M;
   for (long long int i = 0; i < M; ++i){
       long long int a, b;
       long long int c;
       cin >> a >> b >> c;
       AristaDirigida<long long int> arista(a - 1, b - 1, c);
       g.ponArista(arista);
   }
    vector<long long int> dist(g.V(), INT_MAX);
    IndexPQ<long long int> pq(g.V());

    Dijkstra(g, 0, dist, pq, cargas);

   if (dist[N - 1] != INT_MAX) cout << dist[N - 1] << '\n';
   else cout << "IMPOSIBLE\n";

   return true;
}


int main() {
    while (resuelveCaso());
    return 0;
}
