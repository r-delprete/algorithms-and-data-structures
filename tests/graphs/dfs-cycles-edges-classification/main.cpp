#include <algorithm>
#include <climits>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

enum Color { white, gray, black };
enum EdgeType { backward, forward, cross, tree };

class Node {
private:
  int data;
  int start_visit;
  int end_visit;
  int distance;
  Color color;
  Node* predecessor;
  ;
  vector<Node*> adj_list;

public:
  Node(int data)
      : data(data), start_visit(INT_MAX), end_visit(INT_MAX), distance(INT_MAX), color(white), predecessor(nullptr) {}

  int get_data() { return data; }
  int get_start_visit() { return start_visit; }
  int get_end_visit() { return end_visit; }
  Color get_color() { return color; }
  Node* get_predecessor() { return predecessor; }
  vector<Node*> get_adj_list() { return adj_list; }

  void set_data(int data) { this->data = data; }
  void set_start_visit(int start_visit) { this->start_visit = start_visit; }
  void set_end_visit(int end_visit) { this->end_visit = end_visit; }
  void set_distance(int distance) { this->distance = distance; }
  void set_color(Color color) { this->color = color; }
  void set_predecessor(Node* predecessor) { this->predecessor = predecessor; }
  void add_adjacent(Node* node) { adj_list.push_back(node); }
};

class Edge {
private:
  Node *src, *dest;
  int weight;
  EdgeType type;

public:
  Edge(Node* src, Node* dest, int weight) : src(src), dest(dest), weight(weight) {}

  Node* get_source() { return src; }
  Node* get_destination() { return dest; }
  int get_weight() { return weight; }
  EdgeType get_type() { return type; }

  void set_source(Node* src) { this->src = src; }
  void set_destination(Node* dest) { this->dest = dest; }
  void set_weight(int weight) { this->weight = weight; }
  void set_type(EdgeType type) { this->type = type; }

  string type_to_string() {
    switch (type) {
      case EdgeType::forward:
        return "forward";
      case EdgeType::backward:
        return "backward";
      case EdgeType::cross:
        return "cross";
      case EdgeType::tree:
        return "tree";
    }
  }
};

class Graph {
private:
  vector<Node*> nodes;
  vector<Edge*> edges;
  int time = 0, tot_nodes, tot_edges;

  void dfs_visit(Node* node, vector<Node*>& path) {
    node->set_color(gray);
    time++;
    node->set_start_visit(time);
    path.push_back(node);

    for (auto& adj : node->get_adj_list()) {
      Edge* edge = get_edge(node, adj);

      if (adj->get_color() == white) {
        adj->set_predecessor(node);

        if (edge) edge->set_type(tree);

        dfs_visit(adj, path);
      } else if (adj->get_color() == gray) {
        cout << "Cycle found" << endl;
        if (edge) edge->set_type(backward);

        auto it = find(path.begin(), path.end(), adj);

        if (it != path.end()) {
          for (; it != path.end(); it++) cout << (*it)->get_data() << "\t";
          cout << adj->get_data() << endl;
        }

      } else if (adj->get_color() == black) {
        if (node->get_start_visit() < adj->get_start_visit()) {
          if (edge) edge->set_type(EdgeType::forward);
        } else if (node->get_start_visit() > adj->get_start_visit()) {
          if (edge) edge->set_type(EdgeType::cross);
        }
      }
    }

    node->set_color(black);
    time++;
    node->set_end_visit(time);
    path.pop_back();
  }

public:
  Graph(ifstream& input_file) {
    input_file >> tot_nodes >> tot_edges;

    for (int i = 0; i < tot_nodes; i++) insert_node(new Node(i));

    for (int i = 0; i < tot_edges; i++) {
      int src_data, dest_data, weight;
      input_file >> src_data >> dest_data >> weight;

      Node *src = get_node(src_data), *dest = get_node(dest_data);

      if (src && dest) insert_edge(new Edge(src, dest, weight));
    }
  }

  void insert_node(Node* node) {
    nodes.push_back(node);
    if (nodes.size() > tot_nodes) tot_nodes = nodes.size();
  }

  void insert_edge(Edge* edge) {
    edges.push_back(edge);
    edge->get_source()->add_adjacent(edge->get_destination());
    if (tot_edges < edges.size()) tot_edges = edges.size();
  }

  Node* get_node(int data) {
    for (auto& node : nodes) {
      if (node->get_data() == data) return node;
    }

    cerr << "Nodes (" << data << ") not found" << endl;
    return nullptr;
  }

  Edge* get_edge(Node* src, Node* dest) {
    for (auto& edge : edges) {
      if ((edge->get_source() == src && edge->get_destination() == dest) ||
          (edge->get_source() == dest && edge->get_destination() == src))
        return edge;
    }

    cerr << "Edge (" << src->get_data() << ") -> (" << dest->get_data() << ") not found" << endl;
    return nullptr;
  }

  void dfs() {
    for (auto& node : nodes) {
      node->set_color(white);
      node->set_predecessor(nullptr);
      node->set_start_visit(INT_MAX);
      node->set_end_visit(INT_MAX);
    }

    vector<Node*> path;

    for (auto& node : nodes) {
      if (node->get_color() == white) dfs_visit(node, path);
    }
  }

  void print() {
    cout << "Nodes" << endl;
    for (auto& node : nodes) {
      node->get_predecessor() ? cout << "Node: " << node->get_data() << " - start visit: " << node->get_start_visit()
                                     << " - end visit: " << node->get_end_visit() << " - Predecessor ("
                                     << node->get_predecessor()->get_data() << ")"
                              : cout << "Node: " << node->get_data() << " - start visit: " << node->get_start_visit()
                                     << " - end visit: " << node->get_end_visit() << " - Predecessor (NULL)";
      cout << endl;
    }

    cout << endl << "Edges" << endl;
    for (auto& edge : edges) {
      Node *src = edge->get_source(), *dest = edge->get_destination();

      if (src && dest)
        cout << "(" << src->get_data() << ") -> (" << dest->get_data() << ") - Weight: " << edge->get_weight()
             << " - Type: " << edge->type_to_string() << endl;
    }

    cout << endl;
  }

  void print(ofstream& output_file) {
    output_file << "Nodes" << endl;
    for (auto& node : nodes) {
      node->get_predecessor()
          ? output_file << "Node: " << node->get_data() << " - start visit: " << node->get_start_visit()
                        << " - end visit: " << node->get_end_visit() << " - Predecessor ("
                        << node->get_predecessor()->get_data() << ")"
          : output_file << "Node: " << node->get_data() << " - start visit: " << node->get_start_visit()
                        << " - end visit: " << node->get_end_visit() << " - Predecessor (NULL)";
      output_file << endl;
    }

    output_file << endl << "Edges" << endl;
    for (auto& edge : edges) {
      Node *src = edge->get_source(), *dest = edge->get_destination();

      if (src && dest)
        output_file << "(" << src->get_data() << ") -> (" << dest->get_data() << ") - Weight: " << edge->get_weight()
                    << " - Type: " << edge->type_to_string() << endl;
    }

    output_file << endl;
  }
};

int main() {
  ifstream input_file("input.txt");
  ofstream output_file("output.txt");

  Graph g(input_file);
  g.print();

  cout << "DFS VISIT" << endl;
  output_file << "DFS VISIT" << endl;
  g.dfs();
  g.print();
  g.print(output_file);

  input_file.close();
  output_file.close();

  return 0;
}