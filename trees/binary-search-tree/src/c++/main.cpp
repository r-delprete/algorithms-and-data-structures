#include "./classes/binary_search_tree.hpp"
#include "./classes/node.hpp"

int main() {
  BinarySearchTree tree;

  tree.tree_insert(new Node(15));
  tree.tree_insert(new Node(6));
  tree.tree_insert(new Node(18));
  tree.tree_insert(new Node(3));
  tree.tree_insert(new Node(7));
  tree.tree_insert(new Node(17));
  tree.tree_insert(new Node(20));

  cout << "pre-delete:" << endl;
  tree.print_tree(tree.get_root());
  cout << endl;

  Node* node = tree.tree_search(tree.get_root(), 6);
  if (node != nullptr) {
    tree.tree_delete(node);
    cout << "post-delete: " << endl;
    tree.print_tree(tree.get_root());
    cout << endl;
  }

  return 0;
}