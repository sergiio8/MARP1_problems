#include <iostream>
#include <stdexcept>
#include <vector>
#include <deque>
#include <unordered_set>


using namespace std;
using Adys = std::vector<int>;  // lista de adyacentes a un vértice

class Digrafo {
   
   int _V;   // número de vértices
   int _A;   // número de aristas
   std::vector<Adys> _ady;   // vector de listas de adyacentes
   
public:
   
   /**
    * Crea un grafo dirigido con V vértices.
    */
   Digrafo(int V) : _V(V), _A(0), _ady(_V) {}
   
   /**
    * Crea un grafo dirigido a partir de los datos en el flujo de entrada (si puede).
    * primer es el índice del primer vértice del grafo en el entrada.
    */
   Digrafo(std::istream & flujo, int primer = 0) : _A(0) {
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
    * Añade la arista dirigida v-w al grafo.
    * @throws domain_error si algún vértice no existe
    */
   void ponArista(int v, int w) {
      if (v < 0 || v >= _V || w < 0 || w >= _V)
         throw std::domain_error("Vertice inexistente");
      ++_A;
      _ady[v].push_back(w);
   }
   
   
   /**
    * Comprueba si hay arista de u a v.
    */
   bool hayArista(int u, int v) const {
      for (int w : _ady[u])
         if (w == v) return true;
      return false;
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
    * Devuelve el grafo dirigido inverso.
    */
   Digrafo inverso() const {
      Digrafo inv(_V);
      for (int v = 0; v < _V; ++v) {
         for (int w : _ady[v]) {
            inv.ponArista(w, v);
         }
      }
      return inv;
   }
   
   
   /**
    * Muestra el grafo en el stream de salida o (para depurar)
    */
   void print(std::ostream& o = std::cout) const {
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
 * Para mostrar grafos por la salida estándar.
 */
inline std::ostream & operator<<(std::ostream & o, Digrafo const& g) {
   g.print(o);
   return o;
}

void dfs(const Digrafo& G, int v, bool& imposible, vector<bool>& marcaje, vector<bool>& apilado, deque<int>& postorden, unordered_set<int>& visitados){
   marcaje[v] = true;
   apilado[v] = true;
   visitados.erase(v);
   for (int w : G.ady(v)){
      if (!marcaje[w]){
         dfs(G, w, imposible, marcaje, apilado, postorden, visitados); 
      }
      else if (apilado[w]) {
         imposible = true;
      }
   }
   apilado[v] = false;
   postorden.push_front(v);

}

void resolver(const Digrafo& G, bool& imposible, vector<bool>& marcaje, vector<bool>& apilado, deque<int>& postorden, unordered_set<int>& visitados){
   while (!visitados.empty()){
      dfs(G, *visitados.begin(), imposible, marcaje, apilado, postorden, visitados);
   }
}

bool resuelveCaso() {
    Digrafo g = Digrafo(cin, 1);
    if (!cin) return false;
    bool imp = false;
    vector<bool> marcaje(g.V(), false);
    deque<int> postorden;
    vector<bool> apilado(g.V(), false);
    unordered_set<int> visitados;
    for (int i = 0; i < g.V(); ++i) visitados.insert(i);
    resolver(g, imp, marcaje, apilado, postorden, visitados);
    if (imp) cout << "Imposible\n";
    else {
       while (!postorden.empty()){
          cout << postorden.front() + 1 << ' ';
          postorden.pop_front();
       }
       cout << '\n';
    }

  

    return true;
}


int main() {
    while (resuelveCaso());
    return 0;
}