#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>

#include "edge.hpp"
#include "node.hpp"

class Graph {
private:
  std::vector<Node*> nodes;
  std::vector<Edge*> edges;
  int time = 0, tot_nodes, tot_edges;
  std::stack<Node*> s;

  void dfs_visit(Node* node) {
    node->set_color(Color::black);
    time++;
    node->set_start_discovery(time);

    for (auto& adj : node->get_adj_list()) {
      if (adj->get_color() == Color::white) {
        adj->set_predecessor(node);
        dfs_visit(adj);
      }
    }

    time++;
    node->set_end_visit(time);
    node->set_color(Color::black);

    s.push(node);
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
      edge->get_destination()->set_distance(edge->get_source()->get_distance() + edge->get_weight());
      edge->get_destination()->set_predecessor(edge->get_source());
    }
  }

  struct Compare {
    bool operator()(Node* node1, Node* node2) { return node1->get_data() > node2->get_data(); }
  };

  bool is_in_set(std::set<Node*>& s, Node* node) { return s.find(node) != s.end(); }

  bool is_node_valid(std::vector<Node*>& path, Node* node, int pos) {
    Node* last = path[pos - 1];

    for (auto& adj : last->get_adj_list()) {
      if (adj == node) {
        for (auto& path_node : path) {
          if (path_node == node) return false;
        }
        return true;
      }
    }
    return false;
  }

  bool hamiltonian_cycle(std::vector<Node*>& path, int pos) {
    if (pos == tot_nodes) {
      Node* last = path[pos - 1];
      for (auto& adj : last->get_adj_list()) {
        if (adj == path[0]) return true;
      }

      return false;
    }

    for (auto& node : nodes) {
      if (is_node_valid(path, node, pos)) {
        path[pos] = node;
        if (hamiltonian_cycle(path, pos + 1)) return true;
        path[pos] = nullptr;
      }
    }

    return false;
  }

public:
  Graph(std::ifstream& input) { load_from_file(input); }

  Graph() {}

  ~Graph() {
    for (auto& node : nodes) delete node;
    for (auto& edge : edges) delete edge;
  }

  void load_from_file(std::ifstream& input) {
    std::string line;
    std::getline(input, line);
    std::string formatted = line;
    if (line.front() == '<') formatted = formatted.substr(1);
    if (line.back() == '>') formatted = formatted.substr(0, line.size() - 1);

    std::size_t delim_pos = formatted.find(',');
    std::istringstream stream;
    if (delim_pos != std::string::npos) {
      stream.str(formatted.substr(0, delim_pos));
      stream >> tot_nodes;
      stream.clear();

      stream.str(formatted.substr(delim_pos + 1));
      stream >> tot_edges;
    } else {
      stream.str(formatted);
      stream >> tot_nodes >> tot_edges;
    }
    stream.clear();

    for (int i = 0; i < tot_nodes; i++) insert_node(new Node(i));

    while (std::getline(input, line)) {
      stream.clear();
      std::string formatted = line;
      if (line.front() == '<') formatted = formatted.substr(1);
      if (line.back() == '>') formatted = formatted.substr(0, line.size() - 1);
      stream.str(formatted);

      std::string token;
      int src_data, dest_data, weight;
      if (std::getline(stream, token, ',')) src_data = stoi(token);
      if (std::getline(stream, token, ',')) dest_data = stoi(token);
      if (std::getline(stream, token, ',')) weight = stoi(token);

      Node* src = get_node(src_data);
      Node* dest = get_node(dest_data);

      if (src && dest) insert_edge(new Edge(src, dest, weight));
    }
  }

  void insert_node(Node* node) {
    nodes.push_back(node);
    if (nodes.size() > tot_nodes) tot_nodes = nodes.size();
  }

  void insert_edge(Edge* edge) {
    edge->get_source()->add_adjacent(edge->get_destination());
    edges.push_back(edge);
    if (edges.size() > tot_edges) tot_edges = edges.size();
  }

  Node* get_node(int data) {
    for (auto& node : nodes) {
      if (node->get_data() == data) return node;
    }
    std::cerr << "Node (" << data << " not found" << std::endl;
    return nullptr;
  }

  Edge* get_edge(Node* src, Node* dest) {
    for (auto& edge : edges) {
      if ((edge->get_source() == src && edge->get_destination() == dest) ||
          (edge->get_source() == dest && edge->get_destination() == src))
        return edge;
    }

    std::cerr << "Edge (" << src->get_data() << ") -> (" << dest->get_data() << ")" << " not found" << std::endl;
    return nullptr;
  }

  void dfs() {
    for (auto& node : nodes) {
      node->set_predecessor(nullptr);
      node->set_color(Color::white);
      node->set_start_discovery(INT_MAX);
      node->set_end_visit(INT_MAX);
    }

    for (auto& node : nodes) {
      if (node->get_color() == Color::white) dfs_visit(node);
    }
  }

  void print_topological_order(std::ostream& out = std::cout) {
    out << "Topological order" << std::endl;

    while (!s.empty()) {
      Node* node = s.top();
      s.pop();

      if (node->get_predecessor())
        out << "Node (" << node->get_data() << ") => start visit: " << node->get_start_discovery()
            << " - end visit: " << node->get_end_visit() << " - predecessor: (" << node->get_predecessor()->get_data()
            << ")";
      else
        out << "Node (" << node->get_data() << ") => start visit: " << node->get_start_discovery()
            << " - end visit: " << node->get_end_visit() << " - predecessor: (NULL)";
      out << std::endl;
    }
    out << std::endl;
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

  void bellman_ford(Node* src, Node* dest, std::ostream& out = std::cout) {
    initialize_single_source(src);

    for (int i = 0; i < tot_nodes; i++) {
      for (auto& edge : edges) relax(edge);
    }

    std::vector<Node*> path;
    Node* current = dest;
    while (current) {
      path.push_back(current);
      current = current->get_predecessor();
    }

    out << "BELLMAN FORD" << std::endl;
    out << "Minimum path from (" << src->get_data() << ") to (" << dest->get_data() << ") => " << dest->get_distance()
        << std::endl;

    out << "Path" << std::endl;
    for (int i = path.size() - 1; i >= 0; i--) out << "(" << path[i]->get_data() << ")" << (i != 0 ? " -> " : "");
    out << std::endl;
  }

  void dijkstra(Node* src, std::ostream& out = std::cout) {
    initialize_single_source(src);

    std::priority_queue<Node*, std::vector<Node*>, Compare> pq;
    std::set<Node*> visited;
    pq.push(src);

    while (!pq.empty()) {
      Node* node = pq.top();
      pq.pop();

      if (is_in_set(visited, node)) continue;
      visited.insert(node);

      for (auto& adj : node->get_adj_list()) {
        Edge* edge = get_edge(node, adj);

        if (edge) {
          relax(edge);
          if (!is_in_set(visited, adj)) pq.push(adj);
        }
      }
    }

    out << std::endl << "DIJKSTRA" << std::endl;
    out << "Minimum distance from (" << src->get_data() << "):" << std::endl;
    for (auto& node : nodes) out << "(" << node->get_data() << ") - distance: " << node->get_distance() << std::endl;
    out << std::endl;
  }

  bool find_hamiltonian_cycle(int pos, std::ostream& out = std::cout) {
    std::vector<Node*> path(tot_nodes, nullptr);
    path[0] = get_node(pos);

    if (hamiltonian_cycle(path, pos + 1)) {
      out << "Hamiltonian cycle found" << std::endl;

      for (auto& node : path) out << "(" << node->get_data() << ") -> ";
      out << "(" << path[0]->get_data() << ")" << std::endl;

      return true;
    }

    out << "No hamiltonian cycle found" << std::endl;
    return false;
  }
};

#endif