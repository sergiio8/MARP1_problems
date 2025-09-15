#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <string>
using namespace std;


struct tIntervalo {
    int inicio;
    int final;
};

bool operator<(const tIntervalo& i1, const tIntervalo& i2){
    return i1.final < i2.final;
}


bool resuelveCaso() {
   int N;
   cin >> N;
   if (N == 0) return false;

   vector<tIntervalo> intervalos(N);
   for (int i = 0; i < N; ++i){
       string hora;
       cin >> hora;
       string horas;
       horas += hora.at(0);
       horas += hora.at(1);
       int h = stoi(horas);
       string mins;
       mins += hora.at(3);
       mins += hora.at(4);
       int m = stoi(mins);
       int duracion;
       cin >> duracion;
       tIntervalo inter;
       inter.inicio = h*60 + m;
       inter.final = inter.inicio + duracion + 10;
       intervalos[i] = inter;
    }

    sort(intervalos.begin(), intervalos.end());





    int i = 0;
    int cont = 1;
    while (i < N){
        int aux = i + 1;
        while (aux < N && intervalos[aux].inicio < intervalos[i].final){
            aux++;
        }
        i = aux;
        if (i < N) cont++;
    }
    

    cout << cont << '\n'; 

    return true;
}


int main() {
    while (resuelveCaso());
    return 0;
}