#include <iostream>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <unordered_set>
using namespace std;

using Adys = std::vector<int>;  // lista de adyacentes a un vértice

class Grafo {
private:
   int _V;  // número de vértices
   int _A;  // número de aristas
   std::vector<Adys> _ady;  // vector de listas de adyacentes
public:
   
   /**
    * Crea un grafo con V vértices.
    */
   Grafo(int V) : _V(V), _A(0), _ady(_V) {}
   
   /**
    * Crea un grafo a partir de los datos en el flujo de entrada (si puede).
    * primer es el índice del primer vértice del grafo en el entrada.
    */
   Grafo(std::istream & flujo, int primer = 0) : _A(0) {
      flujo >> _V;
      if (!flujo) return;
      _ady.resize(_V);
      int E, v, w;
      flujo >> E;
      while (E--) {
         flujo >> v >> w;
         ponArista(v - primer, w - primer);
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
    * Añade la arista v-w al grafo.
    * @throws domain_error si algún vértice no existe
    */
   void ponArista(int v, int w) {
      if (v < 0 || v >= _V || w < 0 || w >= _V)
         throw std::domain_error("Vertice inexistente");
      ++_A;
      _ady[v].push_back(w);
      _ady[w].push_back(v);
   }
   
   /**
    * Devuelve la lista de adyacencia de v.
    * @throws domain_error si v no existe
    */
   Adys const& ady(int v) const {
      if (v < 0 || v >= _V)
         throw std::domain_error("Vertice inexistente");
      return _ady[v];
   }
   
   /**
    * Muestra el grafo en el stream de salida o (para depurar)
    */
   void print(std::ostream & o = std::cout) const {
      o << _V << " vértices, " << _A << " aristas\n";
      for (int v = 0; v < _V; ++v) {
         o << v << ": ";
         for (int w : _ady[v]) {
            o << w << " ";
         }
         o << "\n";
      }
   }
};

/**
 * Para mostrar grafos por la salida estándar
 */
inline std::ostream & operator<<(std::ostream & o, Grafo const& g){
   g.print(o);
   return o;
}



void dfs(const Grafo& G, int v, vector<bool>& marcaje, bool& sol, vector<int>& aristas, unordered_set<int>& visitados){
   marcaje[v] = true;
   visitados.erase(v);
   for (int w : G.ady(v)){
      if (!marcaje[w]){
         aristas[w] = v;
         dfs(G, w, marcaje, sol, aristas, visitados); 
      }
      else {
         if (aristas[v] != w) sol = false;
      }
   }
}

bool resolver(const Grafo& G, vector<bool>& marcaje, bool& sol, vector<int>& aristas, unordered_set<int>& visitados){
    dfs(G, *visitados.begin(), marcaje, sol, aristas, visitados);
    return visitados.size() == 0 && sol;
}


bool resuelveCaso() {
    int V, A;
    cin >> V >> A;
    if (!cin) return false;

       Grafo g = Grafo(V);
       for (int i = 0; i < A; ++i) {
         int v1, v2;
         cin >> v1 >> v2;
         g.ponArista(v1, v2);
       }
       vector<bool> marcaje(V, false);
       vector<int> aristas(V, -1);
       unordered_set<int> visitados;
       for (int i = 0; i < V; ++i) {
         visitados.insert(i);
       }
       bool sol = true;
       if (resolver(g, marcaje, sol, aristas, visitados)) cout << "SI\n";
       else cout << "NO\n";
    
    return true; 
}


int main() {
    while (resuelveCaso()); 
    return 0;
}