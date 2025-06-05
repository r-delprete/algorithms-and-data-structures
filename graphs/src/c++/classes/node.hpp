#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

enum class Color : int { white = 0, gray = 1, black = 2 };

class Node {
private:
  const string name;
  Color color;
  Node* parent;
  int distance;
  int end_visit;
  vector<Node*> adjacency_list;
  int rank;
  int key;

public:
  // Constructor
  Node(string name, Color color = Color::white, Node* parent = nullptr, int distance = 0, int end_visit = 0,
       vector<Node*> adjacency_list = {}, int rank = 0, int key = 0)
      : name(name),
        color(color),
        parent(parent),
        distance(distance),
        end_visit(end_visit),
        adjacency_list(adjacency_list),
        rank(rank),
        key(key) {}

  // Getter
  string get_name() const { return name; }
  Color get_color() const { return color; }
  Node* get_parent() const { return parent; }
  int get_distance() const { return distance; }
  int get_end_visit() const { return end_visit; }
  int get_rank() const { return rank; }
  int get_key() const { return key; }
  vector<Node*> get_adjacency_list() const { return adjacency_list; }

  // Setter
  void set_color(Color new_color) { color = new_color; }
  void set_parent(Node* new_parent) { parent = new_parent; }
  void set_distance(int new_distance) { distance = new_distance; }
  void set_end_visit(int new_end_visit) { end_visit = new_end_visit; }
  void set_rank(int new_rank) { rank = new_rank; }
  void set_key(int new_key) { key = new_key; }
  void set_adjacency_list(vector<Node*> new_adjacency_list) { adjacency_list = new_adjacency_list; }

  // Print method
  void get_node() { cout << "Node(" << name << ")"; }

  bool operator<(const Node& other) const {
    return this->name < other.name;  // Compare node by name
  }
};

#endif  // NODE_HPP
