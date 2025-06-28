#include <fstream>
#include <sstream>
#include <string>

#include "node.hpp"

enum VisitType { inorder, preorder, postorder };

template <typename T>
class BinarySearchTree {
private:
  Node<T>* root;

  void insert_recursive(Node<T>*& start, Node<T>* node) {
    if (!start) {
      start = node;
      return;
    }

    if (node->get_key() < start->get_key()) {
      insert_recursive(start->get_left(), node);
      start->get_left()->set_parent(start);
    } else {
      insert_recursive(start->get_right(), node);
      start->get_right()->set_parent(start);
    }
  }

  void delete_subtree(Node<T>* node) {
    if (!node) return;

    delete_subtree(node->get_left());
    delete_subtree(node->get_right());
    delete node;
  }

  void inorder_visit(Node<T>* node = nullptr, std::ostream& out = std::cout) {
    if (!node) return;

    inorder_visit(node->get_left(), out);
    node->print(out);
    inorder_visit(node->get_right(), out);
  }

  void preorder_visit(Node<T>* node = nullptr, std::ostream& out = std::cout) {
    if (!node) return;

    node->print(out);
    preorder_visit(node->get_left(), out);
    preorder_visit(node->get_right(), out);
  }

  void postorder_visit(Node<T>* node = nullptr, std::ostream& out = std::cout) {
    if (!node) return;

    postorder_visit(node->get_left(), out);
    postorder_visit(node->get_right(), out);
    node->print(out);
  }

public:
  BinarySearchTree() : root(nullptr) {}

  BinarySearchTree(std::ifstream& input) : root(nullptr) { load(input); }

  ~BinarySearchTree() { delete_subtree(root); }

  Node<T>* get_root() { return root; }

  void load(std::ifstream& input) {
    std::string line;
    while (std::getline(input, line)) {
      std::string formatted = line;
      if (line.front() == '<') formatted = formatted.substr(1);
      if (line.back() == '>') formatted = formatted.substr(0, line.size() - 1);

      std::size_t delim_pos = formatted.find(',');
      std::istringstream stream;
      T key;
      char character;
      if (delim_pos != std::string::npos) {
        stream.str(formatted.substr(0, delim_pos));
        stream >> key;
        stream.clear();
        stream.str(formatted.substr(delim_pos + 1));
        stream >> character;
      } else {
        stream.str(formatted);
        stream >> key >> character;
      }

      insert(new Node<T>(key, character));
      stream.clear();
    }
  }

  void insert(Node<T>* node) { insert_recursive(root, node); }

  void visit(VisitType type = VisitType::inorder, Node<T>* node = nullptr, std::ostream& out = std::cout) {
    if (!node && !root) return;
    if (!node) node = root;

    std::string visit_type = type == VisitType::inorder     ? "INORDER"
                             : type == VisitType::postorder ? "POSTORDER"
                                                            : "PREORDER";
    out << visit_type << " visit" << std::endl;
    switch (type) {
      case VisitType::preorder: {
        preorder_visit(node, out);
        break;
      }
      case VisitType::postorder: {
        postorder_visit(node, out);
        break;
      }
      default: {
        inorder_visit(node, out);
        break;
      }
    }
  }

  Node<T>* tree_maximum(Node<T>* node) {
    while (node->get_right()) node = node->get_right();
    return node;
  }

  Node<T>* tree_minimum(Node<T>* node) {
    while (node->get_left()) node = node->get_left();
    return node;
  }

  Node<T>* predecessor(Node<T>* node) {
    if (!node) {
      std::cerr << "Invalid node for predecessor function" << std::endl;
      return nullptr;
    }

    if (node->get_left()) return tree_maximum(node->get_left());

    Node<T>* y = node->get_parent();
    while (y && y->get_left()) {
      node = y;
      y = y->get_parent();
    }

    return y;
  }

  Node<T>* successor(Node<T>* node) {
    if (!node) {
      std::cerr << "Invalid node for successor function" << std::endl;
      return nullptr;
    }

    if (node->get_right()) return tree_minimum(node->get_right());

    Node<T>* y = node->get_parent();
    while (y && y->get_right()) {
      node = y;
      y = y->get_parent();
    }

    return y;
  }

  void print_predecessor(Node<T>* node, std::ostream& out = std::cout) {
    Node<T>* pred = predecessor(node);

    if (!pred) {
      out << "No node predecessor for node ";
      node->print(out);
    } else {
      out << "Predecessor node for node ";
      node->print(out);
      out << '\t';
      pred->print(out);
    }

    out << std::endl;
  }

  void print_successor(Node<T>* node, std::ostream& out = std::cout) {
    Node<T>* succ = successor(node);

    if (!succ) {
      out << "No node successor for node ";
      node->print(out);
    } else {
      out << "Successor node for node ";
      node->print(out);
      out << '\t';
      succ->print(out);
    }

    out << std::endl;
  }

  Node<T>* search(Node<T>* node, T key) {
    if (!node || node->get_key() == key) return node;

    if (key < node->get_key()) return search(node->get_left(), key);
    return search(node->get_right(), key);
  }
};