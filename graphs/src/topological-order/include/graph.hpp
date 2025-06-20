#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <stack>

#include "edge.hpp"

class Graph {
private:
  std::vector<Node*> nodes;
  std::vector<Edge*> edges;
  int tot_nodes, tot_edges, time = 0;
  std::stack<Node*> s;

  void dfs_visit(Node* node) {
    node->set_color(Color::gray);
    time++;
    node->set_start_discovery(time);

    for (auto& adj : node->get_adj_list()) {
      if (adj->get_color() == Color::white) {
        adj->set_predecessor(node);
        dfs_visit(adj);
      }
    }

    node->set_color(Color::black);
    time++;
    node->set_end_visit(time);

    s.push(node);
  }

  bool is_safe(Node* node, std::vector<Node*>& path, int pos) {
    bool is_adj = false;
    Node* last_node = path[pos - 1];

    for (auto& adj : last_node->get_adj_list()) {
      if (adj == node) {
        is_adj = true;
        break;
      }
    }

    if (!is_adj) return false;

    for (int i = 0; i < pos; i++) {
      if (path[i] == node) return false;
    }

    return true;
  }

  void initialize_single_source(Node* src) {
    for (auto& node : nodes) {
      node->set_predecessor(nullptr);
      node->set_distance(INT_MAX);
    }

    src->set_predecessor(nullptr);
    src->set_distance(0);
  }

  void relax(Edge* edge) {
    if (edge->get_destination()->get_distance() > edge->get_source()->get_distance() + edge->get_weight()) {
      edge->get_destination()->set_predecessor(edge->get_source());
      edge->get_destination()->set_distance(edge->get_source()->get_distance() + edge->get_weight());
    }
  }

  struct CompareNodes {
    bool operator()(Node* node1, Node* node2) { return node1->get_distance() > node2->get_distance(); }
  };

  bool hamiltonian_cycle(std::vector<Node*>& path, int pos) {
    if (pos == tot_nodes) {
      Node* last_node = get_node(pos - 1);

      for (auto& adj : last_node->get_adj_list()) {
        if (adj == path[0]) return true;
      }

      return false;
    }

    for (auto& node : nodes) {
      if (is_safe(node, path, pos)) {
        path[pos] = node;

        if (hamiltonian_cycle(path, pos + 1)) return true;

        path[pos] = nullptr;
      }
    }

    return false;
  }

public:
  Graph(std::ifstream& input_file) {
    input_file >> tot_nodes >> tot_edges;

    for (int i = 0; i < tot_nodes; i++) insert_node(new Node(i));

    for (int i = 0; i < tot_edges; i++) {
      int node1_data, node2_data, weight;

      input_file >> node1_data >> node2_data >> weight;

      Node* src = get_node(node1_data);
      Node* dest = get_node(node2_data);

      if (src && dest)
        insert_edge(new Edge(src, dest, weight));
      else
        std::cerr << "Cannot add edge because node " << node1_data << " and/or " << node2_data << " doesn't exists"
                  << std::endl;
    }
  }

  void insert_node(Node* node) {
    nodes.push_back(node);

    if (nodes.size() > tot_nodes) tot_nodes = nodes.size();
  }

  void insert_edge(Edge* edge) {
    edges.push_back(edge);

    edge->get_source()->add_adjacent(edge->get_destination());

    if (edges.size() > tot_edges) tot_edges = edges.size();
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

  void dfs() {
    for (auto& node : nodes) {
      node->set_predecessor(nullptr);
      node->set_start_discovery(INT_MAX);
      node->set_end_visit(INT_MAX);
      node->set_color(Color::white);
    }

    for (auto& node : nodes) {
      if (node->get_color() == Color::white) dfs_visit(node);
    }
  }

  void print_topological_order(std::ofstream& output_file) {
    while (!s.empty()) {
      Node* node = s.top();
      s.pop();

      output_file << node->get_node_info() << std::endl;
    }
  }

  void bellman_ford(Node* src, Node* dest) {
    initialize_single_source(src);

    for (int i = 0; i < tot_nodes; i++) {
      for (auto& edge : edges) relax(edge);
    }

    std::vector<int> path;
    Node* curr = dest;

    while (curr != nullptr) {
      path.push_back(curr->get_data());
      curr = curr->get_predecessor();
    }

    std::cout << "Distance from source " << src->get_data() << " to destination " << dest->get_data() << ": "
              << dest->get_distance() << std::endl;
    std::cout << "Minimum path" << std::endl;

    for (int i = path.size() - 1; i >= 0; i--) {
      std::cout << path[i] << "\t";
    }

    std::cout << std::endl;
  }

  void dijkstra(Node* src) {
    initialize_single_source(src);

    std::priority_queue<Node*, std::vector<Node*>, CompareNodes> pq;
    pq.push(src);

    std::set<Node*> visited;

    while (!pq.empty()) {
      Node* node = pq.top();
      pq.pop();

      if (visited.find(node) != visited.end()) continue;

      visited.insert(node);

      for (auto& adj : node->get_adj_list()) {
        Edge* edge = get_edge(node, adj);

        if (edge) {
          relax(edge);

          if (visited.find(adj) == visited.end()) pq.push(adj);
        }
      }
    }

    std::cout << "Minimum distances from source " << src->get_data() << std::endl;
    for (auto& node : nodes) {
      std::cout << "Node: " << node->get_data() << " - distance: " << node->get_distance() << std::endl;
    }
  }

  bool find_hamiltonian_cycle(int pos) {
    std::vector<Node*> path(tot_nodes, nullptr);
    path[0] = get_node(pos);

    if (hamiltonian_cycle(path, pos + 1)) {
      std::cout << "Hamiltonian cycle found" << std::endl;

      for (int i = 0; i < tot_nodes; i++) {
        std::cout << path[i]->get_data() << "\t";
      }
      std::cout << path[0]->get_data() << std::endl;

      return true;
    }

    std::cout << "No hamiltonian cycle found" << std::endl;
    return false;
  }
};

#endif  // GRAPH_HPP