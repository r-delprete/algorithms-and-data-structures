#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
#include <string>

class Node {
private:
  int key;
  char huffman_char;
  Node* left;
  Node* right;
  Node* parent;

public:
  Node(int key, char huffman_char)
      : key(key), huffman_char(huffman_char), left(nullptr), right(nullptr), parent(nullptr) {}

  int get_key() { return key; }
  char get_huffman_char() { return key; }
  Node* get_left() { return left; }
  Node* get_right() { return right; }
  Node* get_parent() { return parent; }

  void set_key(int new_key) { key = new_key; }
  void set_huffman_char(int new_huffman_char) { huffman_char = new_huffman_char; }
  void set_left(Node* new_left) { left = new_left; }
  void set_right(Node* new_right) { right = new_right; }
  void set_parent(Node* new_parent) { parent = new_parent; }

  std::string get_info() {
    std::string result = "Node: " + std::to_string(key) + " - Character: " + huffman_char + " - [Parent: ";
    if (parent)
      result += std::to_string(parent->key);
    else
      result += "NULL";

    result += " - Left: ";
    if (left)
      result += std::to_string(left->key);
    else
      result += "NULL";

    result += " - Right: ";
    if (right)
      result += std::to_string(right->key);
    else
      result += "NULL";

    result += "]\n";
    return result;
  }
};

#endif  // NODE_HPP