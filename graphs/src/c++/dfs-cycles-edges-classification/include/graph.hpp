#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <algorithm>
#include <fstream>
#include <iostream>

#include "edge.hpp"

class Graph {
private:
  std::vector<Node*> nodes;
  std::vector<Edge*> edges;
  int tot_nodes, tot_edges, time, cycles_count;

  void dfs_visit(Node* node, std::vector<Node*> path) {
    node->set_color(Color::gray);
    path.push_back(node);

    time += 1;
    node->set_start_discovery(time);

    for (auto& adj : node->get_adj_list()) {
      Edge* edge = get_edge(node, adj);

      if (adj->get_color() == Color::white) {
        adj->set_predecessor(node);
        edge->set_type(EdgeType::tree);
        dfs_visit(adj, path);
      } else if (adj->get_color() == Color::gray) {
        std::cout << "Cycle found" << std::endl;
        edge->set_type(EdgeType::backward);

        auto it = find(path.begin(), path.end(), adj);

        if (it != path.end()) {
          for (; it != path.end(); it++) {
            std::cout << (*it)->get_data() << "\t";
          }

          std::cout << adj->get_data() << std::endl << std::endl;

          cycles_count++;
        }
      } else if (adj->get_color() == Color::black) {
        if (node->get_start_discovery() < adj->get_start_discovery())
          edge->set_type(EdgeType::forward);
        else if (node->get_start_discovery() > adj->get_start_discovery())
          edge->set_type(EdgeType::cross);
      }
    }

    time += 1;
    node->set_end_visit(time);
    node->set_color(Color::black);
    path.pop_back();
  }

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
        std::cerr << "Cannot add edge because " << node1 << " and/or " << node2 << " doesn't exists" << std::endl;
    }

    input_file.close();
  }

  Node* get_node(int data) {
    for (auto& node : nodes) {
      if (node->get_data() == data) return node;
    }

    return nullptr;
  }

  Edge* get_edge(Node* src, Node* dest) {
    for (auto& edge : edges) {
      if ((edge->get_source() == src && edge->get_destination() == dest) ||
          (edge->get_source() == dest && edge->get_destination() == src))
        return edge;
    }

    return nullptr;
  }

  void insert_node(Node* node) {
    nodes.push_back(node);

    if (nodes.size() > tot_nodes) tot_nodes = nodes.size();
  }

  void insert_edge(Edge* edge) {
    edges.push_back(edge);

    edge->get_source()->add_adjacent(edge->get_destination());
    edge->get_destination()->add_adjacent(edge->get_source());

    if (edges.size() > tot_edges) tot_edges = edges.size();
  }

  void dfs() {
    std::vector<Node*> path;

    for (auto& node : nodes) {
      node->set_predecessor(nullptr);
      node->set_start_discovery(INT_MAX);
      node->set_end_visit(INT_MAX);
    }

    for (auto& node : nodes) {
      if (node->get_color() == Color::white) dfs_visit(node, path);
    }
  }

  int get_cycles_count() { return cycles_count; }

  void print_into_file(std::ofstream& output_file) {
    for (auto& node : nodes) {
      if (node->get_predecessor()) {
        output_file << "Node: " << node->get_data() << " - (predecessor: " << node->get_predecessor()->get_data() << ")"
                    << " - start discovery: " << node->get_start_discovery()
                    << " - end_visit: " << node->get_end_visit() << std::endl;
      } else {
        output_file << "Node: " << node->get_data() << " - (predecessor: NULL)"
                    << " - start discovery: " << node->get_start_discovery()
                    << " - end_visit: " << node->get_end_visit() << std::endl;
      }
    }
  }

  void print_edges() {
    for (auto& edge : edges) edge->print();
  }
};

#endif  // GRAPH_HPP