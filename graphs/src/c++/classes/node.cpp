#include "node.hpp"

using namespace std;

Node::Node(string name, Color color, Node* parent, int distance, int end_visit, vector<pair<Node*, int>> adjacency_list,
           int rank, int key)
    : name(name),
      color(color),
      parent(parent),
      distance(distance),
      end_visit(end_visit),
      adjacency_list(adjacency_list),
      rank(rank),
      key(key) {}

string Node::get_name() const { return name; }
Color Node::get_color() const { return color; }
Node* Node::get_parent() const { return parent; }
int Node::get_distance() const { return distance; }
int Node::get_end_visit() const { return end_visit; }
int Node::get_rank() const { return rank; }
int Node::get_key() const { return key; }
const vector<pair<Node*, int>>& Node::get_adjacency_list() const { return adjacency_list; }

void Node::set_color(Color new_color) { color = new_color; }
void Node::set_parent(Node* new_parent) { parent = new_parent; }
void Node::set_distance(int new_distance) { distance = new_distance; }
void Node::set_end_visit(int new_end_visit) { end_visit = new_end_visit; }
void Node::set_rank(int new_rank) { rank = new_rank; }
void Node::set_key(int new_key) { key = new_key; }
void Node::set_adjacency_list(vector<pair<Node*, int>> new_adjacency_list) { adjacency_list = new_adjacency_list; }

void Node::get_node() { printf("Node(%s)", name.c_str()); }

bool Node::operator<(const Node& other) const {
  return this->name < other.name;  // Compare node by name
}
