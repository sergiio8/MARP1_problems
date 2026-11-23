#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

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

#include <iostream>
#include <vector>
#include <functional>
#include <stdexcept>

// Comparator dice cuándo un valor de tipo T es más prioritario que otro
template <typename T = int, typename Comparator = std::less<T> >
class PriorityQueue {
   
   // vector que contiene los datos
   std::vector<T> array;     // primer elemento en la posición 1
   
   /* Objeto función que sabe comparar elementos.
    antes(a,b) es cierto si a es más prioritario que b (a debe salir antes que b) */
   Comparator antes;
   
public:
   
   PriorityQueue(Comparator c = Comparator()) : array(1), antes(c) {}
   
   /* Constructor a partir de un vector de elementos */
   PriorityQueue(std::vector<T> const& v_ini, Comparator c = Comparator()) :
   array(v_ini.size() + 1), antes(c) {
      for (auto i = 0; i < v_ini.size(); ++i)
         array[i + 1] = v_ini[i];
      monticulizar();
   }

   
   /* Insertar el elemento x (que incluye su prioridad).
    Si no hay espacio, el array se agranda. */
   void push(T const& x) {
      array.push_back(x);
      flotar(array.size() - 1);
   }
   
   /* Devuelve el número de elementos en la cola. */
   int size() const { return int(array.size()) - 1; }
   
   /* Averigua si la cola con prioridad está vacía. */
   bool empty() const { return size() == 0; }
   
   /* Si la cola no es vacía, devuelve el elemento más prioritario. */
   T const& top()  const {
      if (empty()) throw std::domain_error("La cola vacia no tiene top");
      else return array[1];
   }
   
   /* Si la cola no es vacía, elimina el elemento más prioritario. */
   void pop() {
      if (empty())
         throw std::domain_error("Imposible eliminar el primero de una cola vacia");
      else {
         array[1] = std::move(array.back());
         array.pop_back();
         if (!empty()) hundir(1);
      }
   }
   
   /* Si la cola no es vacía, elimina y devuelve el elemento más prioritario. */
   void pop(T & prim) {
      if (empty())
         throw std::domain_error("Imposible eliminar el primero de una cola vacia");
      else {
         prim = std::move(array[1]);
         array[1] = std::move(array.back());
         array.pop_back();
         if (!empty()) hundir(1);
      }
   }
   
private:
   
   /* Flota el elemento situado en la posición i del montículo. */
   void flotar(int i) {
      T elem = std::move(array[i]);
      int hueco = i;
      while (hueco != 1 && antes(elem, array[hueco / 2])) {
         array[hueco] = std::move(array[hueco / 2]);
         hueco /= 2;
      }
      array[hueco] = std::move(elem);
   }
   
   /* Hunde el elemento situado en la posición n del montículo. */
   void hundir(int i) {
      T elem = std::move(array[i]);
      int hueco = i;
      int hijo = 2 * hueco; // hijo izquierdo, si existe
      while (hijo <= size())  {
         // cambiar al hijo derecho si existe y va antes que el izquierdo
         if (hijo < size() && antes(array[hijo + 1], array[hijo]))
            ++hijo;
         // flotar el hijo si va antes que el elemento hundiéndose
         if (antes(array[hijo], elem)) {
            array[hueco] = std::move(array[hijo]);
            hueco = hijo; hijo = 2 * hueco;
         }
         else break;
      }
      array[hueco] = std::move(elem);
   }
   
   /* Convierte un vector en un montículo. */
   void monticulizar() {
      for (auto i = size() / 2; i > 0; --i)
         hundir(i);
   }
};

#include <vector>
#include <iostream>

class ConjuntosDisjuntos {
protected:
   int ncjtos;  // número de conjuntos disjuntos
   mutable std::vector<int> p;  // enlace al padre
   std::vector<int> tam;  // tamaño de los árboles
public:
   
   // crea una estructura de partición con los elementos 0..N-1,
   // cada uno en un conjunto, partición unitaria
   ConjuntosDisjuntos(int N) : ncjtos(N), p(N), tam(N,1) {
      for (int i = 0; i < N; ++i)
      p[i] = i;
   }
   
   //  devuelve el representante del conjunto que contiene a a
   int buscar(int a) const {
      if (p.at(a) == a) // es una raíz
         return a;
      else
         return p[a] = buscar(p[a]);
   }
   
   // unir los conjuntos que contengan a a y b
   void unir(int a, int b) {
      int i = buscar(a);
      int j = buscar(b);
      if (i == j) return;
      if (tam[i] > tam[j]) { // i es la raíz del árbol más grande
         tam[i] += tam[j]; p[j] = i;
      } else {
         tam[j] += tam[i]; p[i] = j;
      }
      --ncjtos;
   }

   // devuelve si a y b están en el mismo conjunto
   bool unidos(int a, int b) const {
      return buscar(a) == buscar(b);
   }
   
   // devuelve el número de elementos en el conjunto de a
   int cardinal(int a) const {
      return tam[buscar(a)];
   }
   
   // devuelve el número de conjuntos disjuntos
   int num_cjtos() const { return ncjtos; }

};

void ARM_kruskal (GrafoValorado<int> const& g, int &coste, vector<Arista<int> >& ARM, int& cont){
    PriorityQueue<Arista<int> > pq(g.aristas());
    ConjuntosDisjuntos cjutos(g.V());
    while (!pq.empty()){
        auto a = pq.top();
        pq.pop();
        int v = a.uno();
        int w = a.otro(v);
        if (!cjutos.unidos(v, w)){
            cjutos.unir(v, w);
            cont++;
            ARM.push_back(a);
            coste += a.valor();
            if (ARM.size() == g.V() - 1) break;
        }
    }
}

bool resuelveCaso() {
    GrafoValorado<int> g = GrafoValorado<int>(cin, 1);
    if (!cin) return false;
    vector<Arista<int> > ARM(g.V());
    int coste = 0;
    int cont = 0;
    ARM_kruskal(g, coste, ARM, cont);
    if (cont != g.V() - 1) cout << "No hay puentes suficientes\n";
    else cout << coste << '\n';

    return true;
}


int main() {
    while (resuelveCaso());
    return 0;
}