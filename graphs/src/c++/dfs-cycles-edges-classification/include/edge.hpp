#ifndef EDGE_HPP
#define EDGE_HPP

#include <iostream>
#include <string>

#include "node.hpp"

enum EdgeType { tree, backward, forward, cross };

class Edge {
private:
  Node* src;
  Node* dest;
  int weight;
  EdgeType type;

public:
  Edge(Node* src, Node* dest, int weight) : src(src), dest(dest), weight(weight) {}

  Node* get_source() { return src; }
  Node* get_destination() { return dest; }
  int get_weight() { return weight; }
  EdgeType get_type() { return type; }
  std::string print_type() {
    switch (type) {
      case EdgeType::tree:
        return "tree edge";
        break;
      case EdgeType::backward:
        return "backward edge";
        break;
      case EdgeType::cross:
        return "cross edge";
        break;
      case EdgeType::forward:
        return "forward edge";
        break;
      default:
        break;
    }
  }

  void set_source(Node* new_src) { src = new_src; }
  void set_destination(Node* new_dest) { dest = new_dest; }
  void set_weight(int new_weight) { weight = new_weight; }
  void set_type(EdgeType new_type) { type = new_type; }

  void print() {
    std::cout << "(src: " << src->get_data() << " -> dest: " << dest->get_data() << "), weight: " << weight
              << std::endl;
  }
};

#endif  // EDGE_HPP