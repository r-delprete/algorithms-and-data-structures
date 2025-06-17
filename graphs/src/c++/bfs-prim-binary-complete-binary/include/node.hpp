#ifndef NODE_HPP
#define NODE_HPP

#include <climits>
#include <string>
#include <vector>

enum Color { white, black, gray };

class Node {
private:
  int data;
  Color color;
  Node* predecessor;
  int distance;
  std::vector<Node*> adj;

public:
  Node(int data) : data(data), color(Color::white), predecessor(nullptr), distance(INT_MAX) {}

  int get_data() { return data; }
  Color get_color() { return color; }
  Node* get_predecessor() { return predecessor; }
  int get_distance() { return distance; }
  std::vector<Node*> get_adj_list() { return adj; }

  void set_data(int new_data) { data = new_data; }
  void set_color(Color new_color) { color = new_color; }
  void set_predecessor(Node* new_predecessor) { predecessor = new_predecessor; }
  void set_distance(int new_distance) { distance = new_distance; }
  void add_adjacent(Node* node) { adj.push_back(node); }
};

#endif  // NODE_HPP