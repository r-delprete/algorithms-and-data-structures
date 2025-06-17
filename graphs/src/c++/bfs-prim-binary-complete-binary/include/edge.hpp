#ifndef EDGE_HPP
#define EDGE_HPP

#include "./node.hpp"

class Edge {
private:
  Node* src;
  Node* dest;
  int weight;

public:
  Edge(Node* src, Node* dest, int weight) : src(src), dest(dest), weight(weight) {}

  Node* get_source() { return src; }
  Node* get_destination() { return dest; }
  int get_weight() { return weight; }

  void set_source(Node* new_src) { src = new_src; }
  void set_destination(Node* new_dest) { dest = new_dest; }
  void set_weight(int new_weight) { weight = new_weight; }
};

#endif  // EDGE_HPP