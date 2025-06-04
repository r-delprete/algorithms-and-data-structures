#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
#include <string>

using namespace std;

class Node {
private:
  string symbol;
  int frequency;
  Node* left_child;
  Node* right_child;
  bool combined;

public:
  Node(string symbol = "", int frequency = 0, Node* left_child = nullptr, Node* right_child = nullptr,
       bool combined = false)
      : symbol(symbol), frequency(frequency), left_child(left_child), right_child(right_child), combined(combined) {}

  // Getter
  string get_symbol() const { return symbol; }
  int get_frequency() const { return frequency; }
  Node* get_left_child() const { return left_child; }
  Node* get_right_child() const { return right_child; }
  bool is_combined() const { return combined; }

  // Setter
  void set_frequency(int freq) { frequency = freq; }
  void set_left_child(Node* left) { left_child = left; }
  void set_right_child(Node* right) { right_child = right; }
  void set_combined(bool value) { combined = value; }

  string get_node(int level = 0) {
    string indent(level * 2, ' ');
    string left = (left_child != nullptr) ? "\n" + indent + "├─ Left: " + left_child->get_node(level + 1) : "";
    string right = (right_child != nullptr) ? "\n" + indent + "└─ Right: " + right_child->get_node(level + 1) : "";

    return indent + (symbol != "" ? "symbol: " + symbol + " - " : "") + "frequency: " + to_string(frequency) + left +
           right;
  }

  bool operator<(Node& other) {
    if (frequency != other.frequency) {
      return frequency < other.frequency;
    }

    return combined && !other.combined;
  }

  void swap(Node& other) {
    std::swap(symbol, other.symbol);
    std::swap(frequency, other.frequency);
    std::swap(left_child, other.left_child);
    std::swap(right_child, other.right_child);
    std::swap(combined, other.combined);
  }
};

struct CompareNodes {
  bool operator()(const Node& a, const Node& b) const {
    if (a.get_frequency() != b.get_frequency()) {
      return a.get_frequency() > b.get_frequency();  // Opposite sign for min-heap
    }
    return !a.is_combined() && b.is_combined();
  }
};

#endif