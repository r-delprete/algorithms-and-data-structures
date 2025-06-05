#ifndef EDGE_HPP
#define EDGE_HPP

#include "node.hpp"

enum class EdgeTypes : int { none = -1, back = 0, forward = 1, cross = 2 };

class Edge {
private:
  Node source_node;
  Node destination_node;
  int weight;
  EdgeTypes type = EdgeTypes::none;

public:
  Edge(Node source_node, Node destination_node, int weight, EdgeTypes type = EdgeTypes::none)
      : source_node(source_node), destination_node(destination_node), weight(weight), type(type) {}
};

#endif