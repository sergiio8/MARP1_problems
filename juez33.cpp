#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

bool resuelveCaso() {
   long long int N;
   cin >> N;
   if (!cin) return false;

   vector<long long int> enemigos(N);
   for (int i = 0; i < N; ++i){
       long long int a;
       cin >> a;
       enemigos[i] = a;
    }
    vector<long long int> defensa(N);
    for (int i = 0; i < N; ++i){
       long long int a;
       cin >> a;
       defensa[i] = a;
    }

    sort(enemigos.begin(), enemigos.end());
    sort(defensa.begin(), defensa.end());

    int j = 0;
    int cont = 0;
    for (int i = 0; i < N && j < N; ++i){
        while (j < N && defensa[j] < enemigos[i]){
            j++;
        }
        if (j < N) cont++;
        j++;
    }
    

    cout << cont << '\n'; 

    return true;
}


int main() {
    while (resuelveCaso());
    return 0;
}