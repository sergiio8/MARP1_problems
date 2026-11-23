/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Manuel Montenegro Montes
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

/*
 * Aquí se introducen los recorridos parametrizados con respecto
 * al tipo de acción que se desea realizar en cada visita.
 */

using namespace std;

#include <cassert>
#include <iostream>
#include <iterator>
#include <memory>
#include <queue>
#include <stack>
#include <climits>
#include <cmath>

template <class T> class BinTree {

private:
  struct TreeNode;
  using NodePointer = std::shared_ptr<TreeNode>;

public:
  BinTree() : root_node(nullptr) {}

  BinTree(const T &elem)
      : root_node(std::make_shared<TreeNode>(nullptr, elem, nullptr)) {}

  BinTree(const BinTree &left, const T &elem, const BinTree &right)
      : root_node(std::make_shared<TreeNode>(left.root_node, elem,
                                             right.root_node)) {}

  bool empty() const { return root_node == nullptr; }

  const T &root() const {
    assert(root_node != nullptr);
    return root_node->elem;
  }

  BinTree left() const {
    assert(root_node != nullptr);
    BinTree result;
    result.root_node = root_node->left;
    return result;
  }

  BinTree right() const {
    assert(root_node != nullptr);
    BinTree result;
    result.root_node = root_node->right;
    return result;
  }

  void display(std::ostream &out) const { display_node(root_node, out); }

  template <typename U> void preorder(U func) const {
    preorder(root_node, func);
  }

  template <typename U> void inorder(U func) const { inorder(root_node, func); }

  template <typename U> void postorder(U func) const {
    postorder(root_node, func);
  }

  template <typename U> void levelorder(U func) const;

private:
  struct TreeNode {
    TreeNode(const NodePointer &left, const T &elem, const NodePointer &right)
        : elem(elem), left(left), right(right) {}

    T elem;
    NodePointer left, right;
  };

  NodePointer root_node;

  static void display_node(const NodePointer &root, std::ostream &out) {
    if (root == nullptr) {
      out << ".";
    } else {
      out << "(";
      display_node(root->left, out);
      out << " " << root->elem << " ";
      display_node(root->right, out);
      out << ")";
    }
  }

  template <typename U> static void preorder(const NodePointer &node, U func);

  template <typename U> static void inorder(const NodePointer &node, U func);

  template <typename U> static void postorder(const NodePointer &node, U func);
};

template <typename T>
template <typename U>
void BinTree<T>::preorder(const NodePointer &node, U func) {
  if (node != nullptr) {
    func(node->elem);
    preorder(node->left, func);
    preorder(node->right, func);
  }
}

template <typename T>
template <typename U>
void BinTree<T>::inorder(const NodePointer &node, U func) {
  if (node != nullptr) {
    inorder(node->left, func);
    func(node->elem);
    inorder(node->right, func);
  }
}

template <typename T>
template <typename U>
void BinTree<T>::postorder(const NodePointer &node, U func) {
  if (node != nullptr) {
    postorder(node->left, func);
    postorder(node->right, func);
    func(node->elem);
  }
}

template <typename T>
template <typename U>
void BinTree<T>::levelorder(U func) const {
  std::queue<NodePointer> pending;
  if (root_node != nullptr) {
    pending.push(root_node);
  }
  while (!pending.empty()) {
    NodePointer current = pending.front();
    pending.pop();
    func(current->elem);
    if (current->left != nullptr) {
      pending.push(current->left);
    }
    if (current->right != nullptr) {
      pending.push(current->right);
    }
  }
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const BinTree<T> &tree) {
  tree.display(out);
  return out;
}

template <typename T> 
BinTree<T> read_tree(std::istream &in) {
  char c;
  in >> c;
  if (c == '.') {
    return BinTree<T>();
  } else {
    assert(c == '(');
    BinTree<T> left = read_tree<T>(in);
    T elem;
    in >> elem;
    BinTree<T> right = read_tree<T>(in);
    in >> c;
    assert(c == ')');
    BinTree<T> result(left, elem, right);
    return result;
  }
}

template <typename T>
struct tSol{
    bool equilibrado;
    bool busqueda;
    T max;
    T min;
    int altura;
};


template <typename T>
tSol<T> resolver(BinTree<T> t, T t1, T t2){
    if (t.empty()){
        return {true, true, t1, t2, 0};
    }
    else {
        if (t.left().empty() && t.right().empty()) return {true, true, t.root(), t.root(), 1};
        else if (t.left().empty() && !t.right().empty()){
            tSol<T> der = resolver(t.right(), t1, t2);
            return {der.equilibrado &&  der.altura <= 1, der.busqueda && t.root() < der.min, max(t.root(), der.max), min(t.root(), der.min), 1 + der.altura};
        }
        else if (!t.left().empty() && t.right().empty()){
            tSol<T> izq = resolver(t.left(), t1,t2);
            return {izq.equilibrado && izq.altura <= 1, izq.busqueda && t.root() > izq.max, max(t.root(), izq.max), min(t.root(), izq.min), 1 + izq.altura};
        }
        else {
            tSol<T> izq = resolver(t.left(), t1, t2);
            tSol<T> der = resolver(t.right(), t1, t2);
            return {izq.equilibrado && der.equilibrado && abs(izq.altura - der.altura) <= 1, izq.busqueda && der.busqueda && t.root() > izq.max && t.root() < der.min, max(t.root(), max(izq.max, der.max)), min(t.root(), min(izq.min, der.min)), 1 + max(der.altura, izq.altura)};
        }
    }
    
}



bool resuelveCaso() {
    char a;
    cin >> a;
    if (!cin) return false;
    if (a == 'N'){
        BinTree<int> t = read_tree<int>(cin);
        if (resolver<int>(t, 1, 1).equilibrado && resolver<int>(t, 1, 1).busqueda) cout << "SI\n";
        else cout << "NO\n";
    }
    else {
        BinTree<string> t = read_tree<string>(cin);
        if (resolver<string>(t, "a", "a").equilibrado && resolver<string>(t, "a", "a").busqueda) cout << "SI\n";
        else cout << "NO\n";
    }

    return true;

}


int main() {
    while (resuelveCaso());
    return 0;
}
