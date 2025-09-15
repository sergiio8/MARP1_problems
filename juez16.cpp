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




struct instruccion {
   char tipo;
   int saltos;
};

void dfs(const Digrafo& G, int v, bool& C, bool& a_veces, bool& nunca, vector<bool>& marcaje, vector<bool>& apilado){
   marcaje[v] = true;
   apilado[v] = true;
   for (int w : G.ady(v)){
      if (!marcaje[w]){
         if (G.ady(v).size() == 2) C = true;
         dfs(G, w, C, a_veces, nunca,  marcaje, apilado); 
      }
      else if (apilado[w]) {
         if (G.ady(v).size() == 2) C = true;
         if (!C) nunca = true;
         else a_veces = true;
      }
   }
   apilado[v] = false;
}



bool resuelveCaso() {
    int N;
    cin >> N;
    if (!cin) return false;
    vector<instruccion> inst(N);
    for (int i = 0; i < N; ++i){
       char a;
       cin >> a;
       if (a == 'A'){
         instruccion ins;
         ins.tipo = 'A';
         ins.saltos = -1;
         inst[i] = ins;
       }
       else if (a == 'J'){
          instruccion ins;
          int saltos;
          cin >> saltos;
          ins.tipo = 'J';
          ins.saltos = saltos - 1;
          inst[i] = ins;
       }
       else if (a == 'C'){
          instruccion ins;
          int saltos;
          cin >> saltos;
          ins.tipo = 'C';
          ins.saltos = saltos - 1;
          inst[i] = ins;
       }
    }



    Digrafo g = Digrafo(N);

    for (int i = 0; i < N; ++i){
       if (inst[i].tipo == 'A'){
          if (i + 1 < N) g.ponArista(i, i + 1);
       }
       else if (inst[i].tipo == 'J'){
          g.ponArista(i, inst[i].saltos);
       }
       else if (inst[i].tipo == 'C'){
          g.ponArista(i, inst[i].saltos);
          if (i + 1 < N) g.ponArista(i, i + 1);
       }
    }

    bool a_veces = false;
    bool nunca = false;
    bool C = false;
    vector<bool> marcaje(g.V(), false);
    vector<bool> apilado(g.V(), false);
    dfs(g, 0, C, a_veces, nunca, marcaje, apilado);
    if (a_veces) cout << "A VECES\n";
    else if (nunca && !a_veces) cout << "NUNCA\n";
    else cout << "SIEMPRE\n";
    
    return true;
    
}


int main() {
    while (resuelveCaso());
    return 0;
}