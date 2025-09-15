#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <cmath>

using namespace std;

struct tTarea {
    long long int ini;
    long long int fin;
};

bool operator<(const tTarea& e1, const tTarea& e2){
    return e1.ini < e2.ini || (e1.ini == e2.ini && e1.fin < e2.fin);
}

bool resuelveCaso() {
   long long int C, F, N;
   cin >> C >> F >> N;
   if (C == 0 && F == 0 && N == 0) return false;

   vector<tTarea> tareas(N);
   for (long long int i = 0; i < N; ++i){
       long long int a, b;
       cin >> a >> b;
       tTarea e;
       e.ini = a;
       e.fin = b;
       tareas[i] = e;
    }
    
    sort(tareas.begin(), tareas.end());

    long long int cont = 1;
    long long int i = 0;
    long long int max = 0;
    long long int ind = -1;

    while (i < N && tareas[i].ini <= C){
        if (tareas[i].fin > C){
            if (tareas[i].fin > max) {
                max = tareas[i].fin;
                ind = i;
            }
        }
        ++i;
    }

    i = ind;
    bool imposible = false;

    if (ind == -1) imposible = true;

    while (i < N && max < F && !imposible){
        bool imposible_aux = true;
        long long int aux = i + 1;
        ind = aux;
        while (aux < N && tareas[aux].ini <= tareas[i].fin){
            imposible_aux = false;
            if (tareas[aux].fin > max) {
                max = tareas[aux].fin;
                ind = aux;
            }
            aux++;
        }
        imposible = imposible_aux;
        cont++;
        i = ind;
    }

    if (max < F || imposible) cout << "Imposible\n";
    else cout << cont << '\n';

    return true;
}


int main() {
    while (resuelveCaso());
    return 0;
}