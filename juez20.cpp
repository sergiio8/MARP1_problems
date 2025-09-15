#include <iostream>
#include <stdexcept>
#include <vector>
#include <deque>
#include <unordered_set>
#include <queue>


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

int bfs(const Digrafo& g, int caras, int destino){
   if (0 == destino) return 0;
   queue<int> q;
   q.push(0);
   vector<int> distancia(destino + 1, -1);
   distancia[0] = 0;
   while (!q.empty()){
       int k = q.front();
       q.pop();
       for (int i = 1; i <= caras; ++i){
           if (g.ady(k + i).empty()) {
               if (distancia[k + i] == -1){
                   distancia[k + i] = distancia[k] + 1;
                   if (k + i == destino) return distancia[k + i];
                   else q.push(k + i);
               }
           }
           else{
               if (distancia[g.ady(k + i)[0]] == -1){
                   distancia[g.ady(k + i)[0]] = distancia[k] + 1;
                   q.push(g.ady(k + i)[0]);
               }
           }
        }
   }
}


bool resuelveCaso() {
    int N, K, S, E;
    cin >> N >> K >> S >> E;
    if (N == 0 && K == 0 && S == 0 && E == 0) return false;

    Digrafo g = Digrafo(N*N);

    for (int i = 0; i < S; ++i){
        int n1, n2;
        cin >> n1 >> n2;
        g.ponArista(n1 - 1, n2 - 1);
    }
    for (int i = 0; i < E; ++i){
        int n1, n2;
        cin >> n1 >> n2;
        g.ponArista(n1 - 1, n2 - 1);
    }

    cout << bfs(g, K, N*N - 1) << '\n';

    
    return true;
    
}


int main() {
    while (resuelveCaso());
    return 0;
}