#include "./include/binary_search_tree.hpp"

using namespace std;

int main() {
  ifstream in("input.txt");
  ofstream out("output.txt");

  BinarySearchTree bst(in);
  cout << "Tree root: " << bst.get_root()->get_info();

  out << std::endl << "Preorder visit" << std::endl;
  bst.preorder_visit_in_file(bst.get_root(), out);

  Node* x = bst.search(bst.get_root(), 15);
  bst.print_predecessor_in_file(x, out);

  x = bst.search(bst.get_root(), 15);
  bst.print_successor_in_file(x, out);

  in.close();
  out.close();

  return 0;
}