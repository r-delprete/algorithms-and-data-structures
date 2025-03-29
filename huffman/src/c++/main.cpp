#include <iostream>

#include "classes/huffman.hpp"

int main(int argc, const char **argv) {
  vector<Node> nodes({Node("Z", 1), Node("W", 2), Node("Y", 3), Node("V", 6), Node("X", 8)});

  Node root = huffman(nodes);

  cout << root.get_node() << endl;

  return 0;
}