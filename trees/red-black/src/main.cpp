#include "./include/red_black_tree.hpp"

int main() {
  RedBlackTree tree;

  tree.tree_insert(new Node(10));
  tree.tree_insert(new Node(20));
  tree.tree_insert(new Node(30));
  tree.tree_insert(new Node(15));
  tree.tree_insert(new Node(25));
  tree.tree_insert(new Node(5));
  tree.tree_insert(new Node(1));
  tree.tree_insert(new Node(21));

  cout << "Tree structure:" << endl;
  tree.print_tree(tree.get_root());
  cout << endl;

  cout << endl << "Inorder visit:" << endl;
  tree.inorder_visit(tree.get_root());

  cout << endl << "Preorder visit:" << endl;
  tree.preorder_visit(tree.get_root());

  cout << endl << "Postorder visit:" << endl;
  tree.preorder_visit(tree.get_root());

  Node* node = tree.tree_search(tree.get_root(), 10);
  if (node != nullptr) {
    tree.tree_delete(node);
    cout << endl << "post-delete: " << endl;
    tree.print_tree(tree.get_root());
    cout << endl;
  }

  return 0;
}