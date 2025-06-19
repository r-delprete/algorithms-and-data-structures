#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include <fstream>
#include <string>
#include <unordered_map>

#include "node.hpp"

class BinarySearchTree {
private:
  Node* root;
  std::unordered_map<char, std::string> huffman_map;

  Node* insert_recursive(Node* start_node, Node* node) {
    if (start_node == nullptr) return node;

    if (node->get_key() < start_node->get_key()) {
      Node* left = insert_recursive(start_node->get_left(), node);
      start_node->set_left(left);
      left->set_parent(start_node);
    } else {
      Node* right = insert_recursive(start_node->get_right(), node);
      start_node->set_right(right);
      right->set_parent(start_node);
    }

    return start_node;
  }

public:
  BinarySearchTree(std::ifstream& input_file) : root(nullptr) {
    int key;
    char character;

    while (input_file >> key >> character) insert(new Node(key, character));
  }

  Node* get_root() { return root; }

  void insert(Node* node) { root = insert_recursive(root, node); }

  Node* tree_minimum(Node* node) {
    while (node->get_left()) node = node->get_left();
    return node;
  }

  Node* tree_maximum(Node* node) {
    while (node->get_right()) node = node->get_right();
    return node;
  }

  Node* get_successor(Node* node) {
    if (!node) return nullptr;
    if (node->get_right()) return tree_minimum(node->get_right());

    Node* y = node->get_parent();
    while (y && node == y->get_right()) {
      node = y;
      y = y->get_parent();
    }

    return y;
  }

  Node* get_predecessor(Node* node) {
    if (!node) return nullptr;
    if (node->get_left()) return tree_maximum(node->get_left());

    Node* y = node->get_parent();
    while (y && node == y->get_parent()) {
      node = y;
      y = y->get_parent();
    }

    return y;
  }

  void print_successor_in_file(Node* node, std::ofstream& out) {
    Node* succ = get_successor(node);

    if (succ)
      out << "Successor for node " << node->get_key() << " -> " << succ->get_info() << std::endl;
    else
      out << "No successor found for node: " << node->get_key() << std::endl;
  }

  void print_predecessor_in_file(Node* node, std::ofstream& out) {
    Node* pred = get_predecessor(node);

    if (pred)
      out << std::endl << "Predecessor for node " << node->get_key() << " -> " << pred->get_info() << std::endl;
    else
      out << std::endl << "No predecessor found for node: " << node->get_key() << std::endl;
  }

  void preorder_visit_in_file(Node* node, std::ofstream& out) {
    if (!node) return;

    out << node->get_info();
    preorder_visit_in_file(node->get_left(), out);
    preorder_visit_in_file(node->get_right(), out);
  }

  Node* search(Node* node, int key) {
    if (!node || key == node->get_key()) return node;

    if (key < node->get_key())
      return search(node->get_left(), key);
    else
      return search(node->get_right(), key);
  }
};

#endif  // BINARY_SEARCH_TREE_HPP
