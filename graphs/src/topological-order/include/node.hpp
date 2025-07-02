#ifndef NODE_HPP
#define NODE_HPP

#include <climits>
#include <string>
#include <vector>

enum Color { white, gray, black };

class Node {
private:
  int data;
  int distance;
  int start_discovery;
  int end_visit;
  Node* predecessor;
  std::vector<Node*> adj_list;
  Color color;

public:
  Node(int data) : data(data), distance(INT_MAX), start_discovery(INT_MAX), end_visit(INT_MAX), predecessor(nullptr) {}

  int get_data() { return data; }
  int get_distance() { return distance; }
  int get_start_discovery() { return start_discovery; }
  int get_end_visit() { return end_visit; }
  Node* get_predecessor() { return predecessor; }
  std::vector<Node*> get_adj_list() { return adj_list; }
  Color get_color() { return color; }

  void set_data(int new_data) { data = new_data; }
  void set_distance(int new_distance) { distance = new_distance; }
  void set_start_discovery(int new_start_discovery) { start_discovery = new_start_discovery; }
  void set_end_visit(int new_end_visit) { end_visit = new_end_visit; }
  void set_predecessor(Node* new_predecessor) { predecessor = new_predecessor; }
  void add_adjacent(Node* node) { adj_list.push_back(node); }
  void set_color(Color new_color) { color = new_color; }

  std::string get_info() {
    if (predecessor) {
      return "Node: " + std::to_string(data) + " => (predecessor: " + std::to_string(predecessor->data) +
             ") - start visit: " + std::to_string(start_discovery) + " - end visit: " + std::to_string(end_visit);
    }

    return "Node: " + std::to_string(data) +
           " => (predecessor: NULL) - start visit: " + std::to_string(start_discovery) +
           " - end visit: " + std::to_string(end_visit);
  }
};

#endif  // NODE_HPP