#include <iostream>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <unordered_set>
#include <string>
#include <queue>

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

void bfs(const Grafo& G, int v, vector<bool>& marcaje, const int& TTL, int& cont){
   queue<int> q;
   q.push(v);
   marcaje[v] = true;
   int nivel = 0;
   int elems = 1;
   while (!q.empty() && nivel < TTL){
       int k = q.front();
       q.pop();
       elems--;
       for (int w : G.ady(k)){
           if (!marcaje[w]){
               marcaje[w] = true;
               q.push(w);
               cont++;
            }  
        }
        if (elems == 0) {
           nivel++;
           elems = q.size();
        }
   }
}


bool resuelveCaso() {
    int N, C;
    Grafo g = Grafo(cin, 1);
    int k;
    cin >> k;
    if (!cin) return false;

    for (int i = 0; i < k; ++i){
        int ini, TTL;
        cin >> ini >> TTL;
        int cont = 0;
        vector<bool> marcaje(g.V(), false);
        bfs(g, ini - 1, marcaje, TTL, cont);
        if (TTL == 0) cout << g.V() - 1 << '\n';
        else cout << g.V() - cont - 1 << '\n';
    }
    cout << "---\n";

    return true;
    
}


int main() {
    while (resuelveCaso());
    return 0;
}