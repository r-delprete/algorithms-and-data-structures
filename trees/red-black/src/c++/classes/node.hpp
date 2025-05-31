#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
#include <string>

using namespace std;

enum Color { black, red };

struct Node {
  int key;
  Node* left = nullptr;
  Node* right = nullptr;
  Node* parent = nullptr;
  Color color;

  Node() {}
  Node(int key, Node* left = nullptr, Node* right = nullptr, Node* parent = nullptr, Color color = Color::red)
      : key(key), left(left), right(right), parent(parent), color(color) {};

  string get_color() {
    switch (color) {
      case Color::black:
        return "black";
        break;
      case Color::red:
        return "red";
        break;
    }

    return "";
  }

  void print() { cout << "Node: " << key << " - Color: " << get_color() << endl; };
};

#endif