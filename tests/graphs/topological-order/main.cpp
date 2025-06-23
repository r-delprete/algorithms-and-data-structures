#include <climits>
#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <stack>
#include <vector>

using namespace std;

enum Color { white, gray, black };

class Node {
private:
  int data;
  int start_visit;
  int end_visit;
  Node* predecessor;
  Color color;
  vector<Node*> adj_list;
  int distance;

public:
  Node(int data) : data(data), predecessor(nullptr), start_visit(INT_MAX), end_visit(INT_MAX), distance(INT_MAX) {}

  int get_data() { return data; }
  int get_start_visit() { return start_visit; }
  int get_end_visit() { return end_visit; }
  Node* get_predecessor() { return predecessor; }
  Color get_color() { return color; }
  vector<Node*> get_adj_list() { return adj_list; }
  int get_distance() { return distance; }

  void set_data(int data) { this->data = data; }
  void set_start_visit(int start_visit) { this->start_visit = start_visit; }
  void set_end_visit(int end_visit) { this->end_visit = end_visit; }
  void set_predecessor(Node* predecessor) { this->predecessor = predecessor; }
  void set_color(Color color) { this->color = color; }
  void add_adjacent(Node* node) { this->adj_list.push_back(node); }
  void set_distance(int distance) { this->distance = distance; }
};

class Edge {
private:
  Node* src;
  Node* dest;
  int weight;

public:
  Edge(Node* src, Node* dest, int weight) : src(src), dest(dest), weight(weight) {}

  Node* get_source() { return src; }
  Node* get_destination() { return dest; }
  int get_weight() { return weight; }

  void set_source(Node* src) { this->src = src; }
  void set_destination(Node* dest) { this->dest = dest; }
  void set_weight(int weight) { this->weight = weight; }
};

class Graph {
private:
  vector<Node*> nodes;
  vector<Edge*> edges;
  int time = 0, tot_nodes, tot_edges;
  stack<Node*> s;

  void dfs_visit(Node* node) {
    node->set_color(gray);
    time++;
    node->set_start_visit(time);

    for (auto& adj : node->get_adj_list()) {
      if (adj->get_color() == white) {
        adj->set_predecessor(node);
        dfs_visit(adj);
      }
    }

    time++;
    node->set_end_visit(time);
    node->set_color(black);
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
      edge->get_destination()->set_predecessor(edge->get_source());
      edge->get_destination()->set_distance(edge->get_source()->get_distance() + edge->get_weight());
    }
  }

  struct CompareNodes {
    bool operator()(Node* node1, Node* node2) { return node1->get_distance() > node2->get_distance(); }
  };

public:
  Graph(ifstream& input_file) {
    input_file >> tot_nodes >> tot_edges;

    for (int i = 0; i < tot_nodes; i++) insert_node(new Node(i));
    for (int i = 0; i < tot_edges; i++) {
      int src_data, dest_data, weight;
      input_file >> src_data >> dest_data >> weight;

      Node* src = get_node(src_data);
      Node* dest = get_node(dest_data);

      insert_edge(new Edge(src, dest, weight));
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

    cerr << "Node with data " << data << " not found" << endl;
    return nullptr;
  }

  Edge* get_edge(Node* src, Node* dest) {
    for (auto& edge : edges) {
      if ((edge->get_source() == src || edge->get_source() == dest) &&
          (edge->get_destination() == src || edge->get_destination() == dest))
        return edge;
    }

    cerr << "Edge (" << src->get_data() << ") -> (" << dest->get_data() << ") not found" << endl;
    return nullptr;
  }

  void dfs() {
    for (auto& node : nodes) {
      node->set_predecessor(nullptr);
      node->set_start_visit(INT_MAX);
      node->set_end_visit(INT_MAX);
      node->set_color(white);
    }

    for (auto& node : nodes) {
      if (node->get_color() == white) dfs_visit(node);
    }
  }

  void print_topological_order() {
    while (!s.empty()) {
      Node* node = s.top();
      s.pop();

      node->get_predecessor() ? cout << "Node: " << node->get_data() << " - start visit: " << node->get_start_visit()
                                     << " - end visit: " << node->get_end_visit()
                                     << " - [Predecessor: " << node->get_predecessor()->get_data() << "]"
                              : cout << "Node: " << node->get_data() << " - start visit: " << node->get_start_visit()
                                     << " - end visit: " << node->get_end_visit() << " - [Predecessor: NULL]";
      cout << endl;
    }
  }

  void print_topological_order(ofstream& output_file) {
    while (!s.empty()) {
      Node* node = s.top();
      s.pop();

      node->get_predecessor()
          ? output_file << "Node: " << node->get_data() << " - start visit: " << node->get_start_visit()
                        << " - end visit: " << node->get_end_visit()
                        << " - [Predecessor: " << node->get_predecessor()->get_data() << "]"
          : output_file << "Node: " << node->get_data() << " - start visit: " << node->get_start_visit()
                        << " - end visit: " << node->get_end_visit() << " - [Predecessor: NULL]";
      output_file << endl;
    }
  }

  void print() {
    for (auto& node : nodes) {
      node->get_predecessor() ? cout << "Node: " << node->get_data() << " - start visit: " << node->get_start_visit()
                                     << " - end visit: " << node->get_end_visit()
                                     << " - [Predecessor: " << node->get_predecessor()->get_data() << "]"
                              : cout << "Node: " << node->get_data() << " - start visit: " << node->get_start_visit()
                                     << " - end visit: " << node->get_end_visit() << " - [Predecessor: NULL]";
      cout << endl;
    }
  }

  void print(ofstream& output_file) {
    for (auto& node : nodes) {
      node->get_predecessor()
          ? output_file << "Node: " << node->get_data() << " - start visit: " << node->get_start_visit()
                        << " - end visit: " << node->get_end_visit()
                        << " - [Predecessor: " << node->get_predecessor()->get_data() << "]"
          : output_file << "Node: " << node->get_data() << " - start visit: " << node->get_start_visit()
                        << " - end visit: " << node->get_end_visit() << " - [Predecessor: NULL]";
      output_file << endl;
    }
  }

  void bellman_ford(Node* src, Node* dest) {
    initialize_single_source(src);

    for (int i = 0; i < tot_nodes; i++) {
      for (auto& edge : edges) relax(edge);
    }

    vector<Node*> path;
    Node* current = dest;

    while (current) {
      path.push_back(current);
      current = current->get_predecessor();
    }

    cout << "Distance from source (" << src->get_data() << ") to (" << dest->get_data() << "): " << dest->get_distance()
         << endl;

    cout << "Minimum path" << endl;
    for (int i = path.size() - 1; i >= 0; i--) cout << path[i]->get_data() << "\t";
    cout << endl;
  }

  void dijkstra(Node* src) {
    initialize_single_source(src);

    priority_queue<Node*, vector<Node*>, CompareNodes> pq;
    pq.push(src);

    set<Node*> visited;

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

    cout << "Minimum path from source (" << src->get_data() << ")" << endl;
    for (auto& node : nodes) {
      cout << "Node: " << node->get_data() << " - distance: " << node->get_distance() << endl;
    }
  }
};

int main(void) {
  ifstream input_file("input.txt");
  ofstream output_file("output.txt");

  Graph g(input_file);
  g.dfs();

  g.print_topological_order();
  g.print_topological_order(output_file);

  cout << endl << "Bellman Ford" << endl;
  g.bellman_ford(g.get_node(0), g.get_node(3));

  cout << endl << "Dijkstra" << endl;
  g.dijkstra(g.get_node(0));

  input_file.close();
  output_file.close();

  return 0;
}