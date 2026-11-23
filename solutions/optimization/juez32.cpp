#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>
#include <unordered_set>

using namespace std;

bool resuelveCaso() {
   long long int N, L;
   cin >> N >> L;
   if (!cin) return false;

   vector<long long int> agujeros(N);
   for (int i = 0; i < N; ++i){
       long long int a;
       cin >> a;
       agujeros[i] = a;
    }
    
    int j = 0;
    int cont = 0;
    int k = agujeros[0];
    while (j < N){
        k += L;
        cont++;
        j++;
        if (j < N){
            while (j < N && agujeros[j] <= k){
                j++;
            }
            if (j < N) k = agujeros[j];
        }
    }

    cout << cont << '\n'; 

    return true;
}


int main() {
    while (resuelveCaso());
    return 0;
}