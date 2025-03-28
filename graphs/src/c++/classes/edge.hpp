#ifndef EDGE_HPP
#define EDGE_HPP

#include "node.hpp"

class Edge {
private:
  Node start_node;
  Node end_node;
  int weight;

public:
  Edge(Node start_node, Node end_node, int weight);
};

#endif