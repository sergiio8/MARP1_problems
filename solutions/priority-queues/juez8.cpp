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




bool resuelveCaso() {
    int edad, num_parejas;
    cin >> edad >> num_parejas;
    if (edad == 0 && num_parejas == 0) return false;
    PriorityQueue<int, greater<int> > mont1 = PriorityQueue<int, greater<int> >();
    PriorityQueue<int> mont2 = PriorityQueue<int>();

    mont1.push(edad);
    int elem = edad;
    vector<int> sol;

    
    for (int i = 0; i < num_parejas; ++i){
       int n1, n2;
       cin >> n1 >> n2;
       if (n1 < elem) mont1.push(n1);
       else mont2.push(n1);
       if (n2 < elem) mont1.push(n2);
       else mont2.push(n2);
       if (mont1.size() > mont2.size() + 1) {
          mont2.push(mont1.top());
          mont1.pop();
          sol.push_back(mont1.top());
       }
       else if (mont2.size() > mont1.size() + 1){
          mont1.push(mont2.top());
          mont2.pop();
          sol.push_back(mont2.top());
       }
       else {
          if (mont2.size() > mont1.size()) sol.push_back(mont2.top());
          else sol.push_back(mont1.top());
       }
       elem = sol.back();
    }
    for (int i = 0; i < sol.size(); ++i) cout << sol[i] << ' ';
    cout << endl;

   
       

    return true; 
}


int main() {
    while (resuelveCaso()); 
    return 0;
}


