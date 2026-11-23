#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <cmath>

using namespace std;
void resuelveCaso() {
   long long int N, V;
   cin >> N >> V;


   vector<long long int> pilas(N);
   for (long long int i = 0; i < N; ++i){
       long long int a;
       cin >> a;
       pilas[i] = a;
    }
    
    sort(pilas.begin(), pilas.end());

    long long int cont = 0;
    long long int i = 0;
    long long int j = pilas.size() - 1;


    while (i < j){
        if (pilas[i] + pilas[j] >= V){
            cont++;
            pilas[j] = -1;
            j--;
        }
        i++;
    }

    cout << cont << '\n';
}


int main() {
    int numCasos;
    cin >> numCasos;
    int i = 0;
    while (i < numCasos) {
        resuelveCaso();
        i++;
    }
    return 0;
}