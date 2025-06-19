#ifndef NODE_HPP
#define NODE_HPP

#include <climits>
#include <vector>

enum Color { white, gray, black };

class Node {
private:
  int data;
  int start_discovery;
  int end_visit;
  Node* predecessor;
  std::vector<Node*> adj;
  Color color;

public:
  Node(int data)
      : data(data), start_discovery(INT_MAX), end_visit(INT_MAX), predecessor(nullptr), color(Color::white) {}

  int get_data() { return data; }
  int get_start_discovery() { return start_discovery; }
  int get_end_visit() { return end_visit; }
  Node* get_predecessor() { return predecessor; }
  Color get_color() { return color; }
  std::vector<Node*> get_adj_list() { return adj; }

  void set_data(int new_data) { data = new_data; }
  void set_start_discovery(int new_start_discovery) { start_discovery = new_start_discovery; }
  void set_end_visit(int new_end_visit) { end_visit = new_end_visit; }
  void set_predecessor(Node* new_predecessor) { predecessor = new_predecessor; }
  void add_adjacent(Node* node) { adj.push_back(node); }
  void set_color(Color new_color) { color = new_color; }
};

#endif  // NODE_HPP