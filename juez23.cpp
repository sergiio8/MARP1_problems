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
         Arista<int> a = Arista<int>(v - primer, w - primer, c);
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

void dfs(const GrafoValorado<int>& G, int v, int destino, int anchura, bool& sol, vector<bool>& marcaje){
   marcaje[v] = true;
   for (auto w : G.ady(v)){
      if (!marcaje[w.otro(v)] && anchura <= w.valor()){
         if (w.otro(v) == destino) sol = true;
         else dfs(G, w.otro(v), destino, anchura, sol, marcaje); 
      }
   }
}




bool resuelveCaso() {
    GrafoValorado<int> g = GrafoValorado<int>(cin, 1);
    if (!cin) return false;
    int K;
    cin >> K;
    for (int i = 0; i < K; ++i){
        int n1, n2, anchura;
        cin >> n1 >> n2 >> anchura;
        vector<bool> marcaje(g.V(), false);
        bool sol = false;
        dfs(g, n1 - 1, n2 - 1, anchura, sol, marcaje);
        if (sol) cout << "SI\n";
        else cout << "NO\n";
    }
   


    return true;
}


int main() {
    while (resuelveCaso());
    return 0;
}