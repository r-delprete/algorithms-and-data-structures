#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include "node.hpp"

using namespace std;

class RedBlackTree {
private:
  Node* root = nullptr;

  void fix_insert(Node* node) {
    node->color = Color::red;

    while (node != root && node->parent != nullptr && node->parent->color == Color::red) {
      Node* grandparent = node->parent->parent;

      if (grandparent == nullptr) break;

      if (node->parent == grandparent->left) {
        Node* uncle = grandparent->right;

        if (uncle != nullptr && uncle->color == Color::red) {
          node->parent->color = Color::black;
          uncle->color = Color::black;
          grandparent->color = Color::red;
          node = grandparent;
        } else {
          if (node == node->parent->right) {
            node = node->parent;
            left_rotate(node);
          }
          node->parent->color = Color::black;
          grandparent->color = Color::red;
          right_rotate(grandparent);
        }
      } else {
        Node* uncle = grandparent->left;

        if (uncle != nullptr && uncle->color == Color::red) {
          node->parent->color = Color::black;
          uncle->color = Color::black;
          grandparent->color = Color::red;
          node = grandparent;
        } else {
          if (node == node->parent->left) {
            node = node->parent;
            right_rotate(node);
          }
          node->parent->color = Color::black;
          grandparent->color = Color::red;
          left_rotate(grandparent);
        }
      }
    }

    root->color = Color::black;
  }

public:
  RedBlackTree(Node* root = nullptr) : root(root) {};
  ~RedBlackTree() {
    cout << endl << "Destroying tree..." << endl;
    delete_subtree(root);
    cout << "Tree destroyed" << endl;
  };

  Node* get_root() const { return root; };
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

  void print_tree(Node* node, string prefix = "", bool is_left = true) {
    if (node != nullptr) {
      cout << prefix;

      cout << (is_left ? "├── " : "└── ");
      node->print();

      print_tree(node->left, prefix + (is_left ? "│   " : "    "), true);

      print_tree(node->right, prefix + (is_left ? "│   " : "    "), false);
    }
  };

  void delete_subtree(Node* node) {
    if (node == nullptr) return;

    delete_subtree(node->left);
    delete_subtree(node->right);
    delete node;
  };

  void left_rotate(Node* node) {
    Node* y = node->right;
    node->right = y->left;

    if (y->left != nullptr) {
      y->left->parent = node;
    }

    y->parent = node->parent;

    if (node->parent == nullptr) {
      root = y;
    } else if (node == node->parent->left) {
      node->parent->left = y;
    } else {
      node->parent->right = y;
    }

    y->left = node;
    node->parent = y;
  }

  void right_rotate(Node* node) {
    Node* y = node->left;
    node->left = y->right;

    if (y->right != nullptr) {
      y->right->parent = node;
    }

    y->parent = node->parent;

    if (node->parent == nullptr) {
      root = y;
    } else if (node == node->parent->left) {
      node->parent->left = y;
    } else {
      node->parent->right = y;
    }

    y->right = node;
    node->parent = y;
  }

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

    fix_insert(node);
  };
};

#endif