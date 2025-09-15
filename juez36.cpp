#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <cmath>

using namespace std;

bool resuelveCaso() {
   int N;
   cin >> N;
   if (N == 0) return false;

   vector<int> rivales(N);
   for (int i = 0; i < N; ++i){
       int a;
       cin >> a;
       rivales[i] = a;
    }
    vector<int> propios(N);
    for (int i = 0; i < N; ++i){
       int a;
       cin >> a;
       propios[i] = a;
    }

    sort(rivales.begin(), rivales.end());
    sort(propios.begin(), propios.end(), greater<int>());

    int j = 0;
    int res = 0;
    while (j < N){
        if (j < N && propios[j] - rivales[j] > 0) {
            res += propios[j] - rivales[j];
        }
        j++;
    }
    

    cout << res << '\n'; 

    return true;
}


int main() {
    while (resuelveCaso());
    return 0;
}