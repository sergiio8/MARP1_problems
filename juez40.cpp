#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <cmath>

using namespace std;
bool resuelveCaso() {
   long long int peso, personas;
   cin >> peso >> personas;
   if (!cin) return false;


   vector<long long int> usuarios(personas);
   for (long long int i = 0; i < personas; ++i){
       long long int a;
       cin >> a;
       usuarios[i] = a;
    }
    
    sort(usuarios.begin(), usuarios.end(), greater<long long int>());

    long long int cont = 0;
    long long int i = 0;
    long long int j = usuarios.size() - 1;


    while (i < j){
        if (usuarios[i] + usuarios[j] <= peso){
            cont++;
            j--;
        }
        i++;
    }

    cout << personas - cont << '\n';

    return true;
}


int main() {
    while (resuelveCaso());
    return 0;
}