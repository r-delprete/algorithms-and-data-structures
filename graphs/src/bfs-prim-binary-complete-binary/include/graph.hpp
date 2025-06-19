#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <fstream>
#include <iostream>
#include <queue>

#include "./edge.hpp"

class Graph {
private:
  std::vector<Node*> nodes;
  std::vector<Edge*> edges;
  int tot_nodes, tot_edges;

  struct CompareNodes {
    bool operator()(Node* node1, Node* node2) { return node1->get_distance() > node2->get_distance(); }
  };

public:
  Graph(std::ifstream& input_file) {
    input_file >> tot_nodes >> tot_edges;

    for (int i = 0; i < tot_nodes; i++) insert_node(new Node(i));

    for (int i = 0; i < tot_edges; i++) {
      int node1, node2, weight;
      input_file >> node1 >> node2 >> weight;

      Node* src = get_node(node1);
      Node* dest = get_node(node2);

      if (src && dest)
        insert_edge(new Edge(src, dest, weight));
      else
        std::cerr << "Cannot add edge because node " << node1 << " and/or " << node2 << " doesn't exists" << std::endl;
    }

    input_file.close();
  }
  void insert_node(Node* node) {
    nodes.push_back(node);
    if (nodes.size() > tot_nodes) tot_nodes = nodes.size();
  }

  Node* get_node(int data) {
    for (auto& node : nodes) {
      if (node->get_data() == data) return node;
    }

    return nullptr;
  }

  void insert_edge(Edge* edge) {
    edges.push_back(edge);

    edge->get_source()->add_adjacent(edge->get_destination());
    edge->get_destination()->add_adjacent(edge->get_source());

    if (edges.size() > tot_edges) tot_edges = edges.size();
  }

  Edge* get_edge(Node* node1, Node* node2) {
    for (auto& edge : edges) {
      if ((edge->get_source() == node1 && edge->get_destination() == node2) ||
          (edge->get_source() == node2 && edge->get_destination() == node1))
        return edge;
    }

    return nullptr;
  }

  void bfs(Node* src, std::ofstream& out) {
    for (auto& node : nodes) {
      node->set_color(Color::white);
      node->set_distance(INT_MAX);
      node->set_predecessor(nullptr);
    }

    src->set_color(Color::gray);
    src->set_distance(0);
    src->set_predecessor(nullptr);

    std::queue<Node*> q;
    q.push(src);

    while (!q.empty()) {
      Node* node = q.front();
      q.pop();

      for (auto& adj_node : node->get_adj_list()) {
        if (adj_node->get_color() == Color::white) {
          adj_node->set_predecessor(node);
          adj_node->set_distance(node->get_distance() + 1);
          adj_node->set_color(Color::gray);
          q.push(adj_node);
        }
      }

      node->set_color(Color::black);
    }

    for (auto& node : nodes) {
      node->get_predecessor()
          ? out << "Node: " << node->get_data() << " (predecessor: " << node->get_predecessor()->get_data()
                << ", distance: " << node->get_distance() << "), distance: " << node->get_distance() << std::endl
          : out << "Node: " << node->get_data() << " (predecessor: NULL), distance: " << node->get_distance()
                << std::endl;
    }
    out.close();
  }

  void prim(Node* src) {
    for (auto& node : nodes) {
      node->set_predecessor(nullptr);
      node->set_distance(INT_MAX);
    }

    src->set_distance(0);
    std::vector<bool> in_mst(tot_nodes, false);
    std::priority_queue<Node*, std::vector<Node*>, CompareNodes> pq;
    pq.push(src);

    while (!pq.empty()) {
      Node* node = pq.top();
      pq.pop();
      in_mst[node->get_data()] = true;

      for (auto& adj_node : node->get_adj_list()) {
        Edge* edge = get_edge(node, adj_node);

        if (!in_mst[adj_node->get_data()] && adj_node->get_distance() > edge->get_weight()) {
          adj_node->set_distance(edge->get_weight());
          adj_node->set_predecessor(node);
          pq.push(adj_node);
        }
      }
    }
  }

  void print_mst() {
    std::cout << std::endl << "Minimum Spanning Tree" << std::endl;
    for (auto& node : nodes) {
      node->get_predecessor()
          ? std::cout << "Node: " << node->get_data() << " (predecessor: " << node->get_predecessor()->get_data()
                      << ", distance: " << node->get_distance() << "), distance: " << node->get_distance() << std::endl
          : std::cout << "Node: " << node->get_data() << " (predecessor: NULL), distance: " << node->get_distance()
                      << std::endl;
    }
  }

  bool is_binary() {
    for (auto& node : nodes) {
      int children = 0;

      for (auto& adj_node : node->get_adj_list()) {
        if (adj_node != node->get_predecessor()) {
          children++;
        }
      }

      if (children > 2) return false;
    }

    return true;
  }

  bool is_complete_binary() {
    bool is_leaf = false;

    for (auto& node : nodes) {
      std::vector<Node*> children;

      for (auto& adj_node : node->get_adj_list()) {
        if (adj_node != node->get_predecessor()) {
          children.push_back(adj_node);
        }
      }

      if (children.size() < 2) is_leaf = true;

      if (is_leaf && !children.empty()) return false;
    }

    return true;
  }
};

#endif  // GRAPH_HPP