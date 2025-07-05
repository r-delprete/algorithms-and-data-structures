#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include <fstream>
#include <sstream>
#include <string>

#include "logger.hpp"
#include "node.hpp"

enum Visit { inorder, preorder, postorder };

template <typename T>
class BinarySearchTree {
  Node<T>* root;

  void delete_tree(Node<T>*& node) {
    if (!node) return;

    delete_tree(node->get_child(Child::left));
    delete_tree(node->get_child(Child::right));
    delete node;
  }

  void insert_recursive(Node<T>*& start, Node<T>* node) {
    if (!start) {
      start = node;
      return;
    }

    if (node->get_key() < start->get_key()) {
      insert_recursive(start->get_child(Child::left), node);
      start->get_child(Child::left)->set_parent(start);
    } else {
      insert_recursive(start->get_child(Child::right), node);
      start->get_child(Child::right)->set_parent(start);
    }
  }

  void inorder_visit(Node<T>* node, std::ostream& out = std::cout) {
    if (!node) return;

    inorder_visit(node->get_child(Child::left), out);
    node->print(out);
    inorder_visit(node->get_child(Child::right), out);
  }

  void preorder_visit(Node<T>* node, std::ostream& out = std::cout) {
    if (!node) return;

    node->print(out);
    preorder_visit(node->get_child(Child::left), out);
    preorder_visit(node->get_child(Child::right), out);
  }

  void postorder_visit(Node<T>* node, std::ostream& out = std::cout) {
    if (!node) return;

    postorder_visit(node->get_child(Child::left), out);
    postorder_visit(node->get_child(Child::right), out);
    node->print(out);
  }

public:
  BinarySearchTree() : root(nullptr) {}

  BinarySearchTree(std::ifstream& input) : root(nullptr) { load(input); }

  ~BinarySearchTree() { delete_tree(root); }

  Node<T>*& get_root() { return root; }

  void load(std::ifstream& input) {
    input.clear();
    input.seekg(0, std::ios::beg);

    std::string line;
    while (std::getline(input, line)) {
      if (line.front() == '<') line = line.substr(1);
      if (line.back() == '>') line.pop_back();
      for (auto& c : line) c = c == ',' ? ' ' : c;

      std::istringstream ss(line);
      T key;
      char ch;
      ss >> key >> ch;

      ss.clear();

      insert(new Node<T>(key, ch));
    }
  }

  void insert(Node<T>* node) { insert_recursive(root, node); }

  void visit(Visit visit, Node<T>* node = nullptr, std::ostream& out = std::cout) {
    if (!node && !root) return;
    if (!node) node = root;

    switch (visit) {
      case Visit::inorder: {
        inorder_visit(node, out);
        return;
      }

      case Visit::preorder: {
        preorder_visit(node, out);
        return;
      }

      case Visit::postorder: {
        postorder_visit(node, out);
        return;
      }

      default: {
        log("Invalid visit type", LogLevel::ERROR);
        return;
      }
    }
  }

  Node<T>*& tree_minimum(Node<T>*& node) {
    while (node->get_child(Child::left)) node = node->get_child(Child::left);

    return node;
  }

  Node<T>*& tree_maximum(Node<T>*& node) {
    while (node->get_child(Child::right)) node = node->get_child(Child::right);

    return node;
  }

  Node<T>* predecessor(Node<T>* node) {
    if (!node) {
      log("Invalid node for predecessor function", LogLevel::ERROR);
      return nullptr;
    }

    if (node->get_child(Child::left)) return tree_maximum(node->get_child(Child::left));

    Node<T>* parent = node->get_parent();
    while (parent && node == parent->get_child(Child::left)) {
      node = parent;
      parent = parent->get_parent();
    }

    return parent;
  }

  Node<T>* successor(Node<T>* node) {
    if (!node) {
      log("Invalid node for successor function", LogLevel::ERROR);
      return nullptr;
    }

    if (node->get_child(Child::right)) return tree_minimum(node->get_child(Child::right));

    Node<T>* parent = node->get_parent();
    while (parent && node == parent->get_child(Child::right)) {
      node = parent;
      parent = parent->get_parent();
    }

    return parent;
  }

  void print_predecessor(Node<T>* node, std::ostream& out = std::cout) {
    Node<T>* pred = predecessor(node);

    if (!pred) {
      out << "No predecessor for node ";
      node->print(out);
    } else {
      out << "Predecessor for node ";
      node->print(out);
      out << "\t";
      pred->print(out);
    }

    out << std::endl;
  }

  void print_successor(Node<T>* node, std::ostream& out = std::cout) {
    Node<T>* succ = successor(node);

    if (!succ) {
      out << "No successor for node ";
      node->print(out);
    } else {
      out << "Successor for node ";
      node->print(out);
      out << "\t";
      succ->print(out);
    }

    out << std::endl;
  }

  Node<T>* search(Node<T>* node, T key) {
    std::ostringstream ss;
    ss << "Searching node with key " << key;
    log(ss.str());
    ss.clear();
    ss.str("");

    if (!node) {
      ss << "Node (" << key << ") not found";
      log(ss.str(), LogLevel::ERROR);
      return nullptr;
    }

    if (node->get_key() == key) {
      ss << "Node (" << node->get_key() << ") found";
      log(ss.str());

      return node;
    }

    if (key < node->get_key()) return search(node->get_child(Child::left), key);
    return search(node->get_child(Child::right), key);
  }
};

#endif