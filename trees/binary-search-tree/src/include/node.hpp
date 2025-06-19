#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>

using namespace std;

struct Node {
  int key;
  Node* left = nullptr;
  Node* right = nullptr;
  Node* parent = nullptr;

  Node(int key, Node* left = nullptr, Node* right = nullptr, Node* parent = nullptr)
      : key(key), left(left), right(right), parent(parent) {};

  void print() { cout << "Node " << key << endl; };
};

#endif