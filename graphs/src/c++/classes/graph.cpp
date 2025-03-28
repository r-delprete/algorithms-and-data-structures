#include "graph.hpp"

#include <climits>

using namespace std;

Graph::Graph(vector<Node> nodes, vector<Edge> edges) : nodes(nodes), edges(edges) {}

vector<Node> Graph::get_nodes() { return nodes; }

void Graph::make_set(Node& node) {
  node.set_parent(&node);
  node.set_rank(0);
}

Node* Graph::find_set(Node& node) {
  if (node.get_parent() != &node) {
    node.set_parent(find_set(*node.get_parent()));
  }

  return node.get_parent();
}

void Graph::do_union(Node& node1, Node& node2) {
  Node* root1 = find_set(node1);
  Node* root2 = find_set(node2);

  if (root1 != root2) {
    if (root1->get_rank() < root2->get_rank()) {
      root1->set_parent(root2);
    } else if (root2->get_rank() < root1->get_rank()) {
      root2->set_parent(root1);
    } else if (root1->get_rank() == root2->get_rank()) {
      root2->set_parent(root1);
      root1->set_key(root1->get_key() + 1);
    }
  }
}

void Graph::dfs_visit(Node& node) {
  ++time;

  node.set_color(Color::gray);
  node.set_distance(time);

  for (pair<Node*, int> adj_node_pair : node.get_adjacency_list()) {
    Node* adj_node = adj_node_pair.first;
    if (adj_node->get_color() == Color::white) {
      adj_node->set_parent(&node);
      dfs_visit(*adj_node);
    }
  }

  ++time;
  node.set_color(Color::black);
  node.set_end_visit(time);
}

void Graph::dfs() {
  for (Node& node : nodes) {
    node.set_parent(nullptr);
    node.set_distance(INT_MAX);
    node.set_end_visit(INT_MAX);
  }

  for (Node& node : nodes) {
    if (node.get_color() == Color::white) {
      dfs_visit(node);
    }
  }
}
