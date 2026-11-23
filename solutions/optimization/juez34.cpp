#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <cmath>

using namespace std;

bool resuelveCaso() {
   long long int N, M;
   cin >> N >> M;
   if (!cin) return false;

   vector<int> jugadores(N);
   for (int i = 0; i < N; ++i){
       int a;
       cin >> a;
       jugadores[i] = a;
    }
    vector<int> equipaciones(M);
    for (int i = 0; i < M; ++i){
       int a;
       cin >> a;
       equipaciones[i] = a;
    }

    sort(jugadores.begin(), jugadores.end());
    sort(equipaciones.begin(), equipaciones.end());

    int j = 0;
    int i = 0;
    int cont = 0;
    while (i < N && j < M){
        while (j < M && equipaciones[j] - jugadores[i] < 0){
            j++;
        }
        if (j < M && (equipaciones[j] - jugadores[i] == 1 || equipaciones[j] - jugadores[i] == 0)) {
            cont++;
            j++;
        }
        i++;
    }
    

    cout << N - cont << '\n'; 

    return true;
}


int main() {
    while (resuelveCaso());
    return 0;
}