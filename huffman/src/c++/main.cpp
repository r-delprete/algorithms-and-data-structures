#include <iostream>

#include "classes/min_priority_queue.hpp"
#include "classes/node.hpp"

Node huffman(vector<Node> nodes) {
  MinPriorityQueue<Node, CompareNodes> queue(nodes);

  while (queue.size() > 1) {
    Node node;

    Node* left = queue.extract_min();
    Node* right = queue.extract_min();

    node.set_left_child(left);
    node.set_right_child(right);
    node.set_frequency(node.get_left_child()->get_frequency() + node.get_right_child()->get_frequency());
    node.set_combined(true);

    queue.insert(node);
  }

  return *(queue.extract_min());
}

int main(int argc, const char** argv) {
  vector<Node> nodes({Node("Z", 1), Node("W", 2), Node("Y", 3), Node("V", 6), Node("X", 8)});

  Node root = huffman(nodes);

  cout << root.get_node() << endl;

  return 0;
}