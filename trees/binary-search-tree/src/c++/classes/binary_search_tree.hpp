#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include <string>

#include "node.hpp"

using namespace std;

class BinarySearchTree {
private:
  Node* root;

  void transplant(Node* root_to_sub, Node* root_sub) {
    if (root_to_sub->parent == nullptr) {
      this->set_root(root_sub);
    } else if (root_to_sub == root_to_sub->parent->left) {
      root_to_sub->parent->left = root_sub;
    } else {
      root_to_sub->parent->right = root_sub;
    }

    if (root_sub != nullptr) {
      root_sub->parent = root_to_sub->parent;
    }
  };

public:
  BinarySearchTree(Node* root = nullptr) : root(root) {};
  ~BinarySearchTree() {
    cout << "Destroying tree..." << endl;
    delete_subtree(root);
    cout << "Tree destroyed" << endl;
  };

  Node* get_root() { return root; };
  void set_root(Node* new_root) { root = new_root; };

  void inorder_visit(Node* node) {
    if (node == nullptr) return;

    inorder_visit(node->left);
    node->print();
    inorder_visit(node->right);
  };

  void preorder_visit(Node* node) {
    if (node == nullptr) return;

    node->print();
    preorder_visit(node->left);
    preorder_visit(node->right);
  };

  void postorder_visit(Node* node) {
    if (node == nullptr) return;

    postorder_visit(node->right);
    postorder_visit(node->left);
    node->print();
  };

  Node* tree_search(Node* node, int key) {
    if (node == nullptr || key == node->key) {
      return node;
    }

    if (key < node->key) {
      return tree_search(node->left, key);
    } else {
      return tree_search(node->right, key);
    }
  };

  Node* tree_minimum(Node* node) {
    while (node->left != nullptr) {
      node = node->left;
    }

    return node;
  };

  Node* tree_maximum(Node* node) {
    while (node->right != nullptr) {
      node = node->right;
    }

    return node;
  };

  Node* tree_successor(Node* node) {
    if (node->right != nullptr) {
      return tree_minimum(node->right);
    }

    Node* successor = node->parent;

    while (successor != nullptr && node == successor->right) {
      node = successor;
      successor = successor->parent;
    }

    return successor;
  };

  Node* tree_predecessor(Node* node) {
    if (node->left != nullptr) {
      return tree_maximum(node->left);
    }

    Node* predecessor = node->parent;

    while (predecessor != nullptr && node == predecessor->left) {
      node = predecessor;
      predecessor = predecessor->parent;
    }

    return predecessor;
  };

  void tree_insert(Node* node) {
    Node* new_parent = nullptr;
    Node* tracker = root;

    while (tracker != nullptr) {
      new_parent = tracker;

      if (node->key < tracker->key) {
        tracker = tracker->left;
      } else {
        tracker = tracker->right;
      }
    }

    node->parent = new_parent;
    if (new_parent == nullptr) {
      root = node;
    } else if (node->key < new_parent->key) {
      new_parent->left = node;
    } else {
      new_parent->right = node;
    }
  };

  void tree_delete(Node* node) {
    if (node->left == nullptr) {
      transplant(node, node->right);
    } else if (node->right == nullptr) {
      transplant(node, node->left);
    } else {
      Node* tmp = tree_minimum(node->right);

      if (tmp->parent != node) {
        transplant(tmp, tmp->right);
        tmp->right = node->right;
        node->right->parent = tmp;
      }

      transplant(node, tmp);
      tmp->left = node->left;
      tmp->left->parent = tmp;
    }
  };

  void print_tree(Node* node, string prefix = "", bool is_left = true) {
    if (node != nullptr) {
      cout << prefix;

      cout << (is_left ? "├── " : "└── ");
      cout << node->key << endl;

      print_tree(node->left, prefix + (is_left ? "│   " : "    "), true);

      print_tree(node->right, prefix + (is_left ? "│   " : "    "), false);
    }
  };

  void delete_subtree(Node* node) {
    if (node == nullptr) return;

    delete_subtree(node->left);
    delete_subtree(node->right);
    delete node;
  }
};
#endif