#ifndef NODE_HPP
#define NODE_HPP

#include <climits>
#include <iostream>

enum Child { left, right };

template <typename T>
class Node {
  T key;
  char ch;
  Node<T>*left, *right, *parent;
  int frequency;

public:
  Node(T key, char ch, Node<T>* left = nullptr, Node<T>* right = nullptr, Node<T>* parent = nullptr)
      : key(key), ch(ch), left(left), right(right), parent(parent) {}

  Node(T key, int frequency = INT_MAX, char ch = '*', Node<T>* left = nullptr, Node<T>* right = nullptr,
       Node<T>* parent = nullptr)
      : key(key), frequency(frequency), ch(ch), left(left), right(right), parent(parent) {}

  ~Node() {
    delete left;
    delete right;
  }

  T& get_key() { return key; }
  char& get_character() { return ch; }
  int& get_frequency() { return frequency; }
  Node<T>*& get_child(Child dir) { return (dir == Child::left ? left : right); }
  Node<T>*& get_parent() { return parent; }

  void set_key(T key) { this->key = key; }
  void set_character(char ch) { this->ch = ch; }
  void set_frequency(int frequency) { this->frequency = frequency; }
  void set_left(Node<T>* left) { this->left = left; }
  void set_right(Node<T>* right) { this->right = right; }
  void set_parent(Node<T>* parent) { this->parent = parent; }

  void print(std::ostream& out = std::cout) {
    out << "(Key: " << key << " - Character: " << ch << ")";

    out << " - Parent: ";
    if (parent)
      out << "(Key: " << parent->get_key() << " - Character: " << parent->get_character() << ")";
    else
      out << "(NULL)";

    out << " - Left: ";
    if (left)
      out << "(Key: " << left->get_key() << " - Character: " << left->get_character() << ")";
    else
      out << "(NULL)";

    out << " - Right: ";
    if (right)
      out << "(Key: " << right->get_key() << " - Character: " << right->get_character() << ")";
    else
      out << "(NULL)";

    out << std::endl;
  }

  bool is_leaf() { return !left && !right; }
};

#endif