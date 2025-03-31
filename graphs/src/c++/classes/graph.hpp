#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <climits>
#include <iostream>
#include <map>
#include <tuple>
#include <utility>
#include <vector>

#include "edge.hpp"
#include "node.hpp"

using namespace std;

enum class EdgeTypes : int { back = 0, forward = 1, cross = 2 };

class Graph {
private:
  vector<Node> nodes;
  int time = 0;
  int loops;
  int cycles;
  map<EdgeTypes, int> edges_type_count;
  vector<Edge> edges;

  void make_set(Node& node);
  Node* find_set(Node& node);
  void do_union(Node& node1, Node& node2);
  void dfs_visit(Node& node);

public:
  // Constructor
  Graph(vector<Node> nodes, vector<Edge> edges = {});

  // Getter
  /**
   * Function to get graph nodes
   * @return Graph nodes
   */
  vector<Node> get_nodes();

  /**
   * Function to do DFS visit
   */
  void dfs();
};

#endif  // GRAPH_HPP
