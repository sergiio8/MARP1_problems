#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <cmath>

using namespace std;

struct tEdificio {
    long long int ini;
    long long int fin;
};

bool operator<(const tEdificio& e1, const tEdificio& e2){
    return e1.ini < e2.ini || (e1.ini == e2.ini && e1.fin < e2.fin);
}

bool resuelveCaso() {
   long long int N;
   cin >> N;
   if (N == 0) return false;

   vector<tEdificio> edificios(N);
   for (long long int i = 0; i < N; ++i){
       long long int a, b;
       cin >> a >> b;
       tEdificio e;
       e.ini = a;
       e.fin = b;
       edificios[i] = e;
    }
    
    sort(edificios.begin(), edificios.end());

    long long int cont = 0;
    long long int i = 0;
    while (i < N){
        int min = edificios[i].fin;
        long long int aux = i + 1;
        while (aux < N && edificios[aux].ini < min){
            if (edificios[aux].fin < min) min = edificios[aux].fin;
            aux++;
        }
        cont++;
        i = aux;
    }

    cout << cont << '\n';

    return true;
}


int main() {
    while (resuelveCaso());
    return 0;
}