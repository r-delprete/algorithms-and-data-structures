#include "node.hpp"

Node::Node(string symbol, int frequency, Node* left_child, Node* right_child, bool combined)
    : symbol(symbol), frequency(frequency), left_child(left_child), right_child(right_child), combined(combined) {}

// Getter
// Getter
string Node::get_symbol() const { return symbol; }
int Node::get_frequency() const { return frequency; }
Node* Node::get_left_child() const { return left_child; }
Node* Node::get_right_child() const { return right_child; }
bool Node::is_combined() const { return combined; }

// Setter
void Node::set_frequency(int freq) { frequency = freq; }
void Node::set_left_child(Node* left) { left_child = left; }
void Node::set_right_child(Node* right) { right_child = right; }
void Node::set_combined(bool value) { combined = value; }

string Node::get_node(int level) {
  string indent(level * 2, ' ');
  string left = (left_child != nullptr) ? "\n" + indent + "├─ Left: " + left_child->get_node(level + 1) : "";
  string right = (right_child != nullptr) ? "\n" + indent + "└─ Right: " + right_child->get_node(level + 1) : "";

  return indent + (symbol != "" ? "symbol: " + symbol + " - " : "") + "frequency: " + to_string(frequency) + left +
         right;
}

bool Node::operator<(Node& other) {
  if (frequency != other.frequency) {
    return frequency < other.frequency;
  }

  return combined && !other.combined;
}

void Node::swap(Node& other) {
  std::swap(symbol, other.symbol);
  std::swap(frequency, other.frequency);
  std::swap(left_child, other.left_child);
  std::swap(right_child, other.right_child);
  std::swap(combined, other.combined);
}
