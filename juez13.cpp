#include <iostream>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <unordered_set>
#include <string>
using namespace std;

using Adys = std::vector<int>;  // lista de adyacentes a un vértice

const int MAX = 1000;
typedef long long int tMatriz[MAX][MAX];

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

void dfs_aux(const Grafo& G, long long int v, vector<bool>& marcaje, long long int& actual_component, unordered_set<long long int>& visitados){
   marcaje[v] = true;
   visitados.erase(v);
   for (int w : G.ady(v)){
      if (!marcaje[w]){
         actual_component++;
         dfs_aux(G, w, marcaje, actual_component, visitados); 
      }
   }
}

int dfs(const Grafo& G, vector<bool>& marcaje, long long int& actual_component, long long int& longest_component, unordered_set<long long int>& visitados){
    int num_components = 0;
    while (visitados.size() > 0){
        actual_component = 1;
        dfs_aux(G, *visitados.begin(), marcaje, actual_component, visitados);
        if (actual_component > longest_component) longest_component = actual_component;
        num_components++;
    }
    return num_components;
}




bool resuelveCaso() {
    int F, C;
    cin >> F >> C;

    tMatriz m;
    long long int cont = 0;

    for (int i = 0; i < F; ++i){
        string s;
        cin >> s;
        for (int j = 0; j < C; ++j){
            if (s[j] == '#') {
                m[i][j] = cont;
                cont++;
            }
            else m[i][j] = -1;
        }
    }

    if (!cin) return false;

    Grafo g = Grafo(cont + 1);

    for (int i = 0; i < F; ++i){
        for (int j = 0; j < C; ++j){
            if (m[i][j] != -1){
                if (j - 1 >= 0 && m[i][j - 1] != -1){
                    g.ponArista(m[i][j], m[i][j - 1]);
                }
                if (j + 1 < C && m[i][j + 1] != -1){
                    g.ponArista(m[i][j], m[i][j + 1]);
                }
                if (i + 1 < F && m[i + 1][j] != -1){
                    g.ponArista(m[i][j], m[i + 1][j]);
                }
                if (i - 1 >= 0 && m[i - 1][j] != -1){
                    g.ponArista(m[i][j], m[i - 1][j]);
                }
            }
        }
    }

    vector<bool> marcaje(cont + 1, false);
    unordered_set<long long int> visitados;
    long long int actual_component = 1;
    long long int longest_component = 1;
    for (int i = 0; i < cont + 1; ++i) {
        visitados.insert(i);
    }
    if (cont != 0) cout << dfs(g, marcaje, actual_component, longest_component, visitados) - 1 << ' ' << longest_component << '\n';
    else cout << "0 0\n";
    

    return true;
}


int main() {
    while (resuelveCaso());
    return 0;
}