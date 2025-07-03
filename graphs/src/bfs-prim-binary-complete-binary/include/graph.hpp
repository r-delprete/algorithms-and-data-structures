#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <unordered_set>

#include "edge.hpp"
#include "node.hpp"

class Graph {
private:
  std::vector<Node*> nodes;
  std::vector<Edge*> edges;
  int tot_nodes, tot_edges;

  struct Compare {
    bool operator()(Node* node1, Node* node2) { return node1->get_data() > node2->get_data(); }
  };

public:
  Graph() {}

  Graph(std::ifstream& input) { load(input); }

  ~Graph() {
    for (auto& node : nodes) delete node;
    for (auto& edge : edges) delete edge;
  }

  void load(std::ifstream& input) {
    input.clear();
    input.seekg(0, std::ios::beg);

    nodes.clear();
    edges.clear();

    std::string totals_token;
    std::getline(input, totals_token);
    if (totals_token.front() == '<') totals_token = totals_token.substr(1);
    if (totals_token.back() == '>') totals_token.pop_back();

    for (char& c : totals_token) c = c == ',' ? ' ' : c;
    std::istringstream stream(totals_token);
    stream >> tot_nodes >> tot_edges;
    stream.clear();

    for (int i = 0; i < tot_nodes; i++) insert_node(new Node(i));

    std::string line;
    while (std::getline(input, line)) {
      if (line.front() == '<') line = line.substr(1);
      if (line.back() == '>') line.pop_back();

      for (char& c : line) c = c == ',' ? ' ' : c;
      stream.str(line);

      int src_data, dest_data, weight;
      stream >> src_data >> dest_data >> weight;

      Node *src = get_node(src_data), *dest = get_node(dest_data);
      if (src && dest) insert_edge(new Edge(src, dest, weight));
      stream.clear();
    }
  }

  void insert_node(Node* node) {
    nodes.push_back(node);
    tot_nodes = tot_nodes < nodes.size() ? nodes.size() : tot_nodes;
  }

  void insert_edge(Edge* edge) {
    edge->get_source()->add_adjacent(edge->get_destination());
    edge->get_destination()->add_adjacent(edge->get_source());
    edges.push_back(edge);
    tot_edges = tot_edges < edges.size() ? edges.size() : tot_edges;
  }

  Node* get_node(int node_data) {
    for (auto& node : nodes) {
      if (node->get_data() == node_data) return node;
    }

    std::cerr << "Cannot find node (" << node_data << ")" << std::endl;
    return nullptr;
  }

  Edge* get_edge(Node* src, Node* dest) {
    for (auto& edge : edges) {
      if ((edge->get_source() == src && edge->get_destination() == dest) ||
          (edge->get_source() == dest && edge->get_destination() == src))
        return edge;
    }

    std::cerr << "Edge (" << src->get_data() << ") -> (" << dest->get_data() << ") not found" << std::endl;
    return nullptr;
  }

  void print(std::ostream& out = std::cout, std::string message = "Graph") {
    out << message << std::endl;

    out << "Nodes" << std::endl;
    for (auto& node : nodes) out << node->get_info() << std::endl;
    out << std::endl;

    out << "Edges" << std::endl;
    for (auto& edge : edges) out << edge->get_info() << std::endl;
    out << std::endl;
  }

  void bfs(Node* src) {
    for (auto& node : nodes) {
      node->set_color(Color::white);
      node->set_predecessor(nullptr);
      node->set_distance(INT_MAX);
    }

    src->set_color(Color::gray);
    src->set_distance(0);

    std::queue<Node*> q;
    q.push(src);

    while (!q.empty()) {
      Node* node = q.front();
      q.pop();

      for (auto& adj : node->get_adj_list()) {
        if (adj->get_color() == Color::white) {
          adj->set_color(Color::gray);
          adj->set_predecessor(node);
          adj->set_distance(node->get_distance() + 1);
          q.push(adj);
        }
      }

      node->set_color(Color::black);
    }
  }

  void prim(Node* src) {
    for (auto& node : nodes) {
      node->set_distance(INT_MAX);
      node->set_predecessor(nullptr);
    }

    src->set_distance(0);

    std::priority_queue<Node*, std::vector<Node*>, Compare> pq;
    pq.push(src);

    std::unordered_set<Node*> in_mst;

    while (!pq.empty()) {
      Node* node = pq.top();
      pq.pop();
      in_mst.insert(node);

      for (auto& adj : node->get_adj_list()) {
        Edge* edge = get_edge(node, adj);
        if (!in_mst.count(adj) && adj->get_distance() > edge->get_weight()) {
          adj->set_predecessor(node);
          adj->set_distance(edge->get_weight());
          pq.push(adj);
        }
      }
    }
  }

  void print_mst(std::ostream& out = std::cout, std::string message = "Minimum Spanning Tree") {
    out << message << std::endl;
    for (auto& node : nodes) out << node->get_info() << std::endl;
    out << std::endl;
  }

  bool is_binary() {
    for (auto& node : nodes) {
      int children = 0;

      for (auto& adj : node->get_adj_list()) {
        if (adj != node->get_predecessor()) children++;
      }

      if (children > 2) return false;
    }

    return true;
  }

  bool is_complete_binary() {
    bool is_leaf = false;

    for (auto& node : nodes) {
      std::vector<Node*> children;

      for (auto& adj : node->get_adj_list()) {
        if (adj != node->get_predecessor()) children.push_back(adj);
      }

      if (children.size() < 2) is_leaf = true;

      if (is_leaf && !children.empty()) return false;
    }

    return true;
  }
};

#endif