#include "./include/binary_search_tree.hpp"
#include "./include/huffman.hpp"

using namespace std;

int main() {
  ifstream input("input.txt");
  ifstream exam_input("exam_input.txt");
  ofstream output("output.txt");

  BinarySearchTree<int> bst(exam_input);
  bst.visit(Visit::inorder);

  cout << endl;
  bst.print_predecessor(bst.get_root());
  bst.print_successor(bst.get_root());

  int key_search = 33;
  Node<int>* node_search = bst.search(bst.get_root(), key_search);

  Huffman<int> h(exam_input);
  h.print_codes();
  string huffman_input_str = "ACE";
  h.print_encode(huffman_input_str);
  h.print_decode(h.encode(huffman_input_str));

  input.close();
  exam_input.close();
  output.close();

  return 0;
}