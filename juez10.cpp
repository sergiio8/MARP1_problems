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
#include <unordered_map>


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


struct tTema{
    string tema;
    int citas;
    int ind;
};

bool operator<(const tTema& t1, const tTema& t2){
    return (t1.citas > t2.citas)|| (t1.citas == t2.citas && t1.ind > t2.ind);
}

bool resuelveCaso() {
    int eventos;
    cin >> eventos;
    if (!cin) return false;
    
    unordered_map<string, int > m;
    PriorityQueue<tTema> mont = PriorityQueue<tTema>();
    for (int i = 0; i < eventos; ++i){
        string a;
        cin >> a;
        if (a == "C"){
            string tema;
            cin >> tema;
            int citas;
            cin >> citas;
            if (!m.count(tema)){
                m[tema] = citas;
                tTema t;
                t.tema = tema;
                t.citas = citas;
                t.ind = i;
                mont.push(t);
            }
            else {
                m[tema] += citas;
                tTema t;
                t.tema = tema;
                t.citas = m[tema];
                t.ind = i;
                mont.push(t);
            }
        }
        else if (a == "E"){
            string tema;
            cin >> tema;
            int citas;
            cin >> citas;
            m[tema] -= citas;
            tTema t;
            t.tema = tema;
            t.citas = m[tema];
            t.ind = i;
            mont.push(t);
        }
        else if (a == "TC"){
            vector<tTema> sol;
            for (int i = 0; i < 3 && mont.size() > 0; ++i){
                while (mont.size() > 0 && m[mont.top().tema] != mont.top().citas) mont.pop();
                if (mont.size() > 0){
                    sol.push_back(mont.top());
                    mont.pop();
                }
            }
            for (int i = 0; i < sol.size(); ++i){
                cout << i + 1 << ' ' << sol[i].tema << '\n';
            }
            for (int i = sol.size() - 1; i >= 0; --i){
                mont.push(sol[i]);
            }
        }

    }
    cout << "---\n";
    
   
    
    return true; 
}


int main() {
    while (resuelveCaso()); 
    return 0;
}


