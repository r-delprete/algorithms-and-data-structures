#ifndef NODE_HPP
#define NODE_HPP

#include <climits>
#include <string>
#include <vector>

enum Color { white, black, gray };

struct Node {
  int data;
  Color color;
  Node* predecessor;
  int distance;
  std::vector<Node*> adj;

  Node(int data) : data(data), color(Color::white), predecessor(nullptr), distance(INT_MAX) {}
};

#endif  // NODE_HPP