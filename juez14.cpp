#include <iostream>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <unordered_set>
#include <string>
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

void dfs(const Grafo& G, int v, vector<bool>& marcaje, int& cont, unordered_set<int>& comp, unordered_set<int>& visitados){
   marcaje[v] = true;
   comp.insert(v);
   visitados.erase(v);
   for (int w : G.ady(v)){
      if (!marcaje[w]){
         cont++;
         dfs(G, w, marcaje,cont, comp, visitados); 
      }
   }
}

vector<int> resolver(const Grafo& G, vector<bool>& marcaje, int& cont, unordered_set<int>& visitados){
   vector<int> sol(marcaje.size());
   while (visitados.size() > 0){
      cont = 1;
      unordered_set<int> comp;
      dfs(G, *visitados.begin(), marcaje, cont, comp, visitados);
      for (auto elem : comp){
         sol[elem] = cont;
      }
   }
   return sol;
}


bool resuelveCaso() {
    int N, M;
    cin >> N >> M;
    if (!cin) return false;

    Grafo g = Grafo(N);

    for (int i = 0; i < M; ++i){
        int k;
        cin >> k;
        if (k > 0) {
            vector<int> v(k);
            for (int j = 0; j < k; ++j){
                int a;
                cin >> a;
                v[j] = a - 1;
            }
            for (int j = 0; j < v.size() - 1; ++j){
                g.ponArista(v[j], v[j + 1]);
            }
        }
    }

    int cont = 1;
    vector<bool> marcaje(N, false);
    unordered_set<int> visitados;
    for (int i = 0; i < N; ++i) visitados.insert(i);
    vector<int> sol = resolver(g, marcaje, cont, visitados);

    for (int i = 0; i < sol.size(); ++i){
        cout << sol[i] << ' ';
    }
    cout << endl;

    return true;
}


int main() {
    while (resuelveCaso());
    return 0;
}