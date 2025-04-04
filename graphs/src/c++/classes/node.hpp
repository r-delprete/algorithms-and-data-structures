#ifndef NODE_HPP
#define NODE_HPP

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
       vector<Node*> adjacency_list = {}, int rank = 0, int key = 0);

  // Getter
  string get_name() const;
  Color get_color() const;
  Node* get_parent() const;
  int get_distance() const;
  int get_end_visit() const;
  int get_rank() const;
  int get_key() const;
  vector<Node*> get_adjacency_list() const;

  // Setter
  void set_color(Color new_color);
  void set_parent(Node* new_parent);
  void set_distance(int new_distance);
  void set_end_visit(int new_end_visit);
  void set_rank(int new_rank);
  void set_key(int new_key);
  void set_adjacency_list(vector<Node*> new_adjacency_list);

  // Print method
  void get_node();

  bool operator<(const Node& other) const;
};

#endif  // NODE_HPP
