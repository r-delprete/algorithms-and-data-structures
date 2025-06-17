#ifndef EDGE_HPP
#define EDGE_HPP

#include "./node.hpp"

struct Edge {
  Node* src;
  Node* dest;
  int weight;

  Edge(Node* src, Node* dest, int weight) : src(src), dest(dest), weight(weight) {}
};

#endif  // EDGE_HPP