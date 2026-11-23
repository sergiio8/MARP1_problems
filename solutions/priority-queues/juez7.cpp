//
//  PriorityQueue.h
//
//  Implementación de colas con prioridad de mínimos (el elemento más
//  prioritario es el menor) mediante montículos binarios
//
//  Facultad de Informática
//  Universidad Complutense de Madrid
//
//  Copyright (c) 2020 Alberto Verdejo
//
#include <iostream>
#include <vector>
#include <functional>
#include <stdexcept>


using namespace std;

// Comparator dice cuándo un valor de tipo T es más prioritario que otro
template <typename T = int, typename Comparator = std::less<T> >
class PriorityQueue {
   
   // vector que contiene los datos
   std::vector<T> array;     // primer elemento en la posición 1
   
   /* Objeto función que sabe comparar elementos.
    antes(a,b) es cierto si a es más prioritario que b (a debe salir antes que b) */
   Comparator antes;
   
public:
   
   PriorityQueue(Comparator c = Comparator()) : array(1), antes(c) {}
   
   /* Constructor a partir de un vector de elementos */
   PriorityQueue(std::vector<T> const& v_ini, Comparator c = Comparator()) :
   array(v_ini.size() + 1), antes(c) {
      for (auto i = 0; i < v_ini.size(); ++i)
         array[i + 1] = v_ini[i];
      monticulizar();
   }

   
   /* Insertar el elemento x (que incluye su prioridad).
    Si no hay espacio, el array se agranda. */
   void push(T const& x) {
      array.push_back(x);
      flotar(array.size() - 1);
   }
   
   /* Devuelve el número de elementos en la cola. */
   int size() const { return int(array.size()) - 1; }
   
   /* Averigua si la cola con prioridad está vacía. */
   bool empty() const { return size() == 0; }
   
   /* Si la cola no es vacía, devuelve el elemento más prioritario. */
   T const& top()  const {
      if (empty()) throw std::domain_error("La cola vacia no tiene top");
      else return array[1];
   }
   
   /* Si la cola no es vacía, elimina el elemento más prioritario. */
   void pop() {
      if (empty())
         throw std::domain_error("Imposible eliminar el primero de una cola vacia");
      else {
         array[1] = std::move(array.back());
         array.pop_back();
         if (!empty()) hundir(1);
      }
   }
   
   /* Si la cola no es vacía, elimina y devuelve el elemento más prioritario. */
   void pop(T & prim) {
      if (empty())
         throw std::domain_error("Imposible eliminar el primero de una cola vacia");
      else {
         prim = std::move(array[1]);
         array[1] = std::move(array.back());
         array.pop_back();
         if (!empty()) hundir(1);
      }
   }
   
private:
   
   /* Flota el elemento situado en la posición i del montículo. */
   void flotar(int i) {
      T elem = std::move(array[i]);
      int hueco = i;
      while (hueco != 1 && antes(elem, array[hueco / 2])) {
         array[hueco] = std::move(array[hueco / 2]);
         hueco /= 2;
      }
      array[hueco] = std::move(elem);
   }
   
   /* Hunde el elemento situado en la posición n del montículo. */
   void hundir(int i) {
      T elem = std::move(array[i]);
      int hueco = i;
      int hijo = 2 * hueco; // hijo izquierdo, si existe
      while (hijo <= size())  {
         // cambiar al hijo derecho si existe y va antes que el izquierdo
         if (hijo < size() && antes(array[hijo + 1], array[hijo]))
            ++hijo;
         // flotar el hijo si va antes que el elemento hundiéndose
         if (antes(array[hijo], elem)) {
            array[hueco] = std::move(array[hijo]);
            hueco = hijo; hijo = 2 * hueco;
         }
         else break;
      }
      array[hueco] = std::move(elem);
   }
   
   /* Convierte un vector en un montículo. */
   void monticulizar() {
      for (auto i = size() / 2; i > 0; --i)
         hundir(i);
   }
};

struct partido {
    double votos;
    double ind;
    double escanos;
    double coeficiente;
};

bool operator<(const partido& p1, const partido& p2){
    return (p1.coeficiente > p2.coeficiente) || ((p1.coeficiente == p2.coeficiente) && (p1.votos > p2.votos)) || ((p1.coeficiente == p2.coeficiente) && (p1.votos == p2.votos) && (p1.ind < p2.ind));
}


bool resuelveCaso() {
    double C, N;
    cin >> C >> N;
    if (C == 0 && N == 0) return false;
    
    vector<int> v(C);
    for (int i = 0; i < C; ++i) v[i] = 0;

    PriorityQueue<partido> mont = PriorityQueue<partido>();

    for (int i = 0; i < C; ++i){
        double votos;
        cin >> votos;
        partido p;
        p.votos = votos;
        p.ind = i;
        p.escanos = 0;
        p.coeficiente = votos;
        mont.push(p);
    }

    while (N > 0){
        partido min = mont.top();
        mont.pop();
        v[min.ind]++;
        partido nuevo;
        nuevo.votos = min.votos;
        nuevo.ind = min.ind;
        nuevo.escanos = min.escanos + 1;
        nuevo.coeficiente = min.votos/(min.escanos + 2);
        mont.push(nuevo);
        N = N - 1;
    }

    for (int i = 0; i < v.size(); ++i){
        cout << v[i] << ' ';
    }
    cout << endl;

    return true; 
}


int main() {
    while (resuelveCaso()); 
    return 0;
}


