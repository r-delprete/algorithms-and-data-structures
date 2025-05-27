#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include <string>

#include "node.hpp"

using namespace std;

class BinarySearchTree {
private:
  Node* root;

  void transplant(Node* root_to_sub, Node* root_sub) {
    if (root_to_sub->get_parent() == nullptr) {
      this->set_root(root_sub);
    } else if (root_to_sub == root_to_sub->get_parent()->get_left()) {
      root_to_sub->get_parent()->set_left(root_sub);
    } else {
      root_to_sub->get_parent()->set_right(root_sub);
    }

    if (root_sub != nullptr) {
      root_sub->set_parent(root_to_sub->get_parent());
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

    inorder_visit(node->get_left());
    node->print_node();
    inorder_visit(node->get_right());
  };

  void preorder_visit(Node* node) {
    if (node == nullptr) return;

    node->print_node();
    preorder_visit(node->get_left());
    preorder_visit(node->get_right());
  };

  void postorder_visit(Node* node) {
    if (node == nullptr) return;

    postorder_visit(node->get_right());
    postorder_visit(node->get_left());
    node->print_node();
  };

  Node* tree_search(Node* node, int key) {
    if (node == nullptr || key == node->get_key()) {
      return node;
    }

    if (key < node->get_key()) {
      return tree_search(node->get_left(), key);
    } else {
      return tree_search(node->get_right(), key);
    }
  };

  Node* tree_minimum(Node* node) {
    while (node->get_left() != nullptr) {
      node = node->get_left();
    }

    return node;
  };

  Node* tree_maximum(Node* node) {
    while (node->get_right() != nullptr) {
      node = node->get_right();
    }

    return node;
  };

  Node* tree_successor(Node* node) {
    if (node->get_right() != nullptr) {
      return tree_minimum(node->get_right());
    }

    Node* successor = node->get_parent();

    while (successor != nullptr && node == successor->get_right()) {
      node = successor;
      successor = successor->get_parent();
    }

    return successor;
  };

  Node* tree_predecessor(Node* node) {
    if (node->get_left() != nullptr) {
      return tree_maximum(node->get_left());
    }

    Node* predecessor = node->get_parent();

    while (predecessor != nullptr && node == predecessor->get_left()) {
      node = predecessor;
      predecessor = predecessor->get_parent();
    }

    return predecessor;
  };

  void tree_insert(Node* node) {
    Node* new_parent = nullptr;
    Node* tracker = root;

    while (tracker != nullptr) {
      new_parent = tracker;

      if (node->get_key() < tracker->get_key()) {
        tracker = tracker->get_left();
      } else {
        tracker = tracker->get_right();
      }
    }

    node->set_parent(new_parent);
    if (new_parent == nullptr) {
      root = node;
    } else if (node->get_key() < new_parent->get_key()) {
      new_parent->set_left(node);
    } else {
      new_parent->set_right(node);
    }
  };

  void tree_delete(Node* node) {
    if (node->get_left() == nullptr) {
      transplant(node, node->get_right());
    } else if (node->get_right() == nullptr) {
      transplant(node, node->get_left());
    } else {
      Node* tmp = tree_minimum(node->get_right());

      if (tmp->get_parent() != node) {
        transplant(tmp, tmp->get_right());
        tmp->set_right(node->get_right());
        node->get_right()->set_parent(tmp);
      }

      transplant(node, tmp);
      tmp->set_left(node->get_left());
      tmp->get_left()->set_parent(tmp);
    }
  };

  void print_tree(Node* node, string prefix = "", bool is_left = true) {
    if (node != nullptr) {
      cout << prefix;

      cout << (is_left ? "├── " : "└── ");
      cout << node->get_key() << endl;

      print_tree(node->get_left(), prefix + (is_left ? "│   " : "    "), true);

      print_tree(node->get_right(), prefix + (is_left ? "│   " : "    "), false);
    }
  };

  void delete_subtree(Node* node) {
    if (node == nullptr) return;

    delete_subtree(node->get_left());
    delete_subtree(node->get_right());
    delete node;
  }
};
#endif