#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
#include <string>

using namespace std;

class Node {
private:
  string symbol;
  int frequency;
  Node* left_child;
  Node* right_child;
  bool combined;

public:
  Node(string symbol = "", int frequency = 0, Node* left_child = nullptr, Node* right_child = nullptr,
       bool combined = false);

  // Getter
  string get_symbol() const;
  int get_frequency() const;
  Node* get_left_child() const;
  Node* get_right_child() const;
  bool is_combined() const;

  // Setter
  void set_frequency(int freq);
  void set_left_child(Node* left);
  void set_right_child(Node* right);
  void set_combined(bool value);

  string get_node(int level = 0);

  bool operator<(Node& other);
  void swap(Node& other);
};

#endif