#include "./include/binary_search_tree.hpp"

using namespace std;

int main() {
  ifstream in("input.txt");
  ofstream out("output.txt");

  BinarySearchTree<int> bst(in);
  bst.visit(VisitType::preorder);

  cout << endl;
  bst.print_predecessor(bst.get_root());

  int key_search = 5;
  cout << endl << "Searching node with key " << key_search << "..." << endl;
  Node<int>* node_search = bst.search(bst.get_root(), key_search);
  if (node_search) {
    cout << "Node found => ";
    node_search->print();
  } else
    "Node not found";
  cout << endl;

  in.close();
  out.close();

  return 0;
}