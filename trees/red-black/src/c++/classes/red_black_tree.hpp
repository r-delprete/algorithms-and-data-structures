#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include "node.hpp"

using namespace std;

class RedBlackTree {
private:
  Node* root;
  Node* nil;

  void fix_insert(Node* node) {
    node->color = Color::red;

    while (node != root && node->parent->color == Color::red) {
      Node* grandparent = node->parent->parent;

      if (node->parent == grandparent->left) {
        Node* uncle = grandparent->right;

        if (uncle->color == Color::red) {
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

        if (uncle->color == Color::red) {
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

  void transplant(Node* u, Node* v) {
    if (u->parent == nil) {
      root = v;
    } else if (u == u->parent->left) {
      u->parent->left = v;
    } else {
      u->parent->right = v;
    }
    v->parent = u->parent;
  }

  void fix_delete(Node* x) {
    while (x != root && x->color == Color::black) {
      if (x == x->parent->left) {
        Node* w = x->parent->right;
        if (w->color == Color::red) {
          w->color = Color::black;
          x->parent->color = Color::red;
          left_rotate(x->parent);
          w = x->parent->right;
        }

        if (w->left->color == Color::black && w->right->color == Color::black) {
          w->color = Color::red;
          x = x->parent;
        } else {
          if (w->right->color == Color::black) {
            w->left->color = Color::black;
            w->color = Color::red;
            right_rotate(w);
            w = x->parent->right;
          }
          w->color = x->parent->color;
          x->parent->color = Color::black;
          w->right->color = Color::black;
          left_rotate(x->parent);
          x = root;
        }
      } else {
        Node* w = x->parent->left;
        if (w->color == Color::red) {
          w->color = Color::black;
          x->parent->color = Color::red;
          right_rotate(x->parent);
          w = x->parent->left;
        }

        if (w->right->color == Color::black && w->left->color == Color::black) {
          w->color = Color::red;
          x = x->parent;
        } else {
          if (w->left->color == Color::black) {
            w->right->color = Color::black;
            w->color = Color::red;
            left_rotate(w);
            w = x->parent->left;
          }
          w->color = x->parent->color;
          x->parent->color = Color::black;
          w->left->color = Color::black;
          right_rotate(x->parent);
          x = root;
        }
      }
    }
    x->color = Color::black;
  }

public:
  RedBlackTree() {
    nil = new Node;
    nil->color = Color::black;
    nil->left = nil->right = nil->parent = nil;
    root = nil;
  }

  ~RedBlackTree() {
    delete_subtree(root);
    delete nil;
  }

  Node* get_root() const { return root; }
  Node* get_nil() const { return nil; }

  void inorder_visit(Node* node) {
    if (node == nil) return;
    inorder_visit(node->left);
    node->print();
    inorder_visit(node->right);
  }

  void preorder_visit(Node* node) {
    if (node == nil) return;
    node->print();
    preorder_visit(node->left);
    preorder_visit(node->right);
  }

  void postorder_visit(Node* node) {
    if (node == nil) return;
    postorder_visit(node->left);
    postorder_visit(node->right);
    node->print();
  }

  Node* tree_search(Node* node, int key) {
    while (node != nil && key != node->key) {
      if (key < node->key)
        node = node->left;
      else
        node = node->right;
    }
    return node;
  }

  Node* tree_minimum(Node* node) {
    while (node->left != nil) node = node->left;
    return node;
  }

  Node* tree_maximum(Node* node) {
    while (node->right != nil) node = node->right;
    return node;
  }

  void left_rotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != nil) y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == nil)
      root = y;
    else if (x == x->parent->left)
      x->parent->left = y;
    else
      x->parent->right = y;
    y->left = x;
    x->parent = y;
  }

  void right_rotate(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    if (y->right != nil) y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == nil)
      root = y;
    else if (x == x->parent->right)
      x->parent->right = y;
    else
      x->parent->left = y;
    y->right = x;
    x->parent = y;
  }

  void tree_insert(Node* z) {
    Node* y = nil;
    Node* x = root;
    while (x != nil) {
      y = x;
      if (z->key < x->key)
        x = x->left;
      else
        x = x->right;
    }
    z->parent = y;
    if (y == nil)
      root = z;
    else if (z->key < y->key)
      y->left = z;
    else
      y->right = z;
    z->left = z->right = nil;
    z->color = Color::red;
    fix_insert(z);
  }

  void tree_delete(Node* z) {
    Node* y = z;
    Node* x;
    Color y_original_color = y->color;

    if (z->left == nil) {
      x = z->right;
      transplant(z, z->right);
    } else if (z->right == nil) {
      x = z->left;
      transplant(z, z->left);
    } else {
      y = tree_minimum(z->right);
      y_original_color = y->color;
      x = y->right;
      if (y->parent == z)
        x->parent = y;
      else {
        transplant(y, y->right);
        y->right = z->right;
        y->right->parent = y;
      }
      transplant(z, y);
      y->left = z->left;
      y->left->parent = y;
      y->color = z->color;
    }
    if (y_original_color == Color::black) fix_delete(x);
  }

  void delete_subtree(Node* node) {
    if (node == nil) return;
    delete_subtree(node->left);
    delete_subtree(node->right);
    delete node;
  }

  void print_tree(Node* node, string prefix = "", bool is_left = true) {
    if (node == nil) return;
    cout << prefix << (is_left ? "├── " : "└── ");
    node->print();
    print_tree(node->left, prefix + (is_left ? "│   " : "    "), true);
    print_tree(node->right, prefix + (is_left ? "│   " : "    "), false);
  }
};

#endif
