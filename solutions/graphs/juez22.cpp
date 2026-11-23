#include <iostream>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <unordered_set>
#include <string>
using namespace std;

const int MAX = 1000;
typedef long long int tMatriz[MAX][MAX];


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

   void anadir(int k){
       p.push_back(k);
       ncjtos++;
       tam.push_back(1);
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

   int max() const {
       int max = 1;
       for (int i = 0; i < tam.size(); ++i){
           if (tam[i] > max) max = tam[i];
       }
       return max;
   }



};



bool resuelveCaso() {
    int F, C;
    cin >> F >> C;
    if (!cin) return false;

    vector<vector<int> > m(F, vector<int>(C, -1));
    ConjuntosDisjuntos c(C*F + 1);
    long long int cont = 0;
    char a;
    cin.get(a);
    for (int i = 0; i < F; ++i){
        for (int j = 0; j < C; ++j){
            cin.get(a);
            if (a == ' ') {
                m[i][j] = -1;
            }
            else {
                m[i][j] = cont;
                if (j - 1 >= 0 && m[i][j - 1] != -1){
                    c.unir(m[i][j], m[i][j - 1]);
                }
                if (i - 1 >= 0 && m[i - 1][j] != -1){
                    c.unir(m[i][j], m[i - 1][j]);
                }
                if (j - 1 >= 0 && i - 1 >= 0 && m[i - 1][j - 1] != -1){
                    c.unir(m[i][j], m[i - 1][j - 1]);
                }
                if (j + 1 < C && i - 1 >= 0 && m[i - 1][j + 1] != -1){
                    c.unir(m[i][j], m[i - 1][j + 1]);
                }
                cont++;
            }
        }
        cin.get(a);
    }
    int N;
    cin >> N;
    
    
    /*for (int i = 0; i < F; ++i){
        for (int j = 0; j < C; ++j){
            if (m[i][j] != -1){
                if (j - 1 >= 0 && m[i][j - 1] != -1){
                    c.unir(m[i][j], m[i][j - 1]);
                }
                if (j + 1 < C && m[i][j + 1] != -1){
                    c.unir(m[i][j], m[i][j + 1]);
                }
                if (i + 1 < F && m[i + 1][j] != -1){
                    c.unir(m[i][j], m[i + 1][j]);
                }
                if (i - 1 >= 0 && m[i - 1][j] != -1){
                    c.unir(m[i][j], m[i - 1][j]);
                }
                if (j - 1 >= 0 && i - 1 >= 0 && m[i - 1][j - 1] != -1){
                    c.unir(m[i][j], m[i - 1][j - 1]);
                }
                if (j - 1 >= 0 && i + 1 < F && m[i + 1][j - 1] != -1){
                    c.unir(m[i][j], m[i + 1][j - 1]);
                }
                if (j + 1 < C && i + 1 < F && m[i + 1][j + 1] != -1){
                    c.unir(m[i][j], m[i + 1][j + 1]);
                }
                if (j + 1 < C && i - 1 >= 0 && m[i - 1][j + 1] != -1){
                    c.unir(m[i][j], m[i - 1][j + 1]);
                }
            }
        }
    }*/

    cout << c.max() << ' ';
    
    for (int i = 0; i < N; ++i){
        int x_in, y_in;
        cin >> x_in >> y_in;
        int x = x_in - 1;
        int y = y_in - 1;
        m[x][y] = cont + 1;
        if (y - 1 >= 0 && m[x][y - 1] != -1){
            c.unir(m[x][y], m[x][y - 1]);
        }
        if (y + 1 < C && m[x][y + 1] != -1){
            c.unir(m[x][y], m[x][y + 1]);
        }
        if (x + 1 < F && m[x + 1][y] != -1){
            c.unir(m[x][y], m[x + 1][y]);
        }
        if (x - 1 >= 0 && m[x - 1][y] != -1){
            c.unir(m[x][y], m[x - 1][y]);
        }
        if (y - 1 >= 0 && x - 1 >= 0 && m[x - 1][y - 1] != -1){
            c.unir(m[x][y], m[x - 1][y - 1]);
        }
        if (y - 1 >= 0 && x + 1 < F && m[x + 1][y - 1] != -1){
            c.unir(m[x][y], m[x + 1][y - 1]);
        }
        if (y + 1 < C && x + 1 < F && m[x + 1][y + 1] != -1){
            c.unir(m[x][y], m[x + 1][y + 1]);
        }
        if (y + 1 < C && x - 1 >= 0 && m[x - 1][y + 1] != -1){
            c.unir(m[x][y], m[x - 1][y + 1]);
        }
        cont++;
        cout << c.max() << ' ';
    }
    cout << '\n';
    

    return true;
}


int main() {
    while (resuelveCaso());
    return 0;
}