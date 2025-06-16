#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
#include <string>

using namespace std;

class Node {
private:
  char symbol;
  int frequency;
  Node *left, *right;

public:
  Node(char symbol = '\0', int frequency = -1, Node* left = nullptr, Node* right = nullptr)
      : symbol(symbol), frequency(frequency), left(left), right(right) {}

  // Getter
  char get_symbol() const { return symbol; }
  int get_frequency() const { return frequency; }
  Node* get_left() const { return left; }
  Node* get_right() const { return right; }

  // Setter
  void set_frequency(int freq) { frequency = freq; }
  void set_left(Node* left) { left = left; }
  void set_right(Node* right) { right = right; }

  // string get_node(int level = 0) {
  //   string indent(level * 2, ' ');
  //   string left = (left_child != nullptr) ? "\n" + indent + "├─ Left: " + left_child->get_node(level + 1) : "";
  //   string right = (right_child != nullptr) ? "\n" + indent + "└─ Right: " + right_child->get_node(level + 1) : "";

  //   return indent + (symbol != '\0' ? "symbol: " + symbol + " - " : "") + "frequency: " + to_string(frequency) + left
  //   +
  //          right;
  // }

  bool operator<(Node& other) { return frequency < other.frequency; }

  void swap(Node& other) {
    std::swap(symbol, other.symbol);
    std::swap(frequency, other.frequency);
    std::swap(left, other.left);
    std::swap(right, other.right);
  }
};

struct CompareNodes {
  bool operator()(const Node& a, const Node& b) const { return a.get_frequency() > b.get_frequency(); }
};

#endif