#include "./include/binary_search_tree.hpp"

int main() {
  BinarySearchTree tree;

  tree.tree_insert(new Node(15));
  tree.tree_insert(new Node(6));
  tree.tree_insert(new Node(18));
  tree.tree_insert(new Node(3));
  tree.tree_insert(new Node(7));
  tree.tree_insert(new Node(17));
  tree.tree_insert(new Node(20));

  cout << "Tree structure:" << endl;
  tree.print_tree(tree.get_root());
  cout << endl;

  cout << endl << "Inorder visit:" << endl;
  tree.inorder_visit(tree.get_root());

  cout << endl << "Preorder visit:" << endl;
  tree.preorder_visit(tree.get_root());

  cout << endl << "Postorder visit:" << endl;
  tree.preorder_visit(tree.get_root());

  Node* node = tree.tree_search(tree.get_root(), 6);
  if (node != nullptr) {
    tree.tree_delete(node);
    cout << endl << "post-delete: " << endl;
    tree.print_tree(tree.get_root());
    cout << endl;
  }

  return 0;
}