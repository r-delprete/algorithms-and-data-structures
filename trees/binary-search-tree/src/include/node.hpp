#include <iostream>

template <typename T>
class Node {
private:
  T key;
  char character;
  Node<T>*parent, *left, *right;

public:
  Node(T key, char character = '*') : key(key), character(character) { parent = left = right = nullptr; }
  ~Node() {
    delete left;
    delete right;
  }

  T get_key() { return key; }
  char get_character() { return character; }
  Node<T>*& get_left() { return left; }
  Node<T>*& get_right() { return right; }
  Node<T>*& get_parent() { return parent; }

  void set_key(T key) { this->key = key; }
  void set_character(char character) { this->character = character; }
  void set_left(Node<T>* left) { this->left = left; }
  void set_right(Node<T>* right) { this->right = right; }
  void set_parent(Node<T>* parent) { this->parent = parent; }

  void print(std::ostream& out = std::cout) {
    out << "(Key: " << key << " - Character: " << character << ")";

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
};