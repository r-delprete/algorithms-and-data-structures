#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>

using namespace std;

class Node {
private:
  int key;
  Node* left = nullptr;
  Node* right = nullptr;
  Node* parent = nullptr;

public:
  Node(int key, Node* left = nullptr, Node* right = nullptr, Node* parent = nullptr)
      : key(key), left(left), right(right), parent(parent) {};

  int get_key() { return key; };
  void set_key(int new_key) { this->key = new_key; };

  Node* get_left() { return left; };
  void set_left(Node* new_left) { left = new_left; };

  Node* get_right() { return right; };
  void set_right(Node* new_right) { right = new_right; };

  Node* get_parent() { return parent; }
  void set_parent(Node* new_parent) { parent = new_parent; };

  void print_node() { cout << "Node " << key << endl; };
};

#endif