#include <cstdlib>
#include <ctime>
#include <iostream>
#include <map>
#include <vector>

#include "classes/edge.hpp"
#include "classes/graph.hpp"
#include "classes/node.hpp"

using namespace std;

int main(int argc, char **argv) {
  srand(time(NULL));

  Node a("a");
  Node b("b");
  Node c("c");
  Node d("d");
  Node e("e");
  Node f("f");
  Node g("g");
  vector<Node> nodes = {a, b, c, d, e, f, g};

  vector<Edge> edges;
  edges.push_back(Edge(a, b, 1 + rand() % 10));
  edges.push_back(Edge(a, d, 1 + rand() % 10));
  edges.push_back(Edge(b, c, 1 + rand() % 10));
  edges.push_back(Edge(b, d, 1 + rand() % 10));
  edges.push_back(Edge(b, e, 1 + rand() % 10));
  edges.push_back(Edge(c, e, 1 + rand() % 10));
  edges.push_back(Edge(d, e, 1 + rand() % 10));
  edges.push_back(Edge(d, f, 1 + rand() % 10));
  edges.push_back(Edge(e, f, 1 + rand() % 10));
  edges.push_back(Edge(e, g, 1 + rand() % 10));
  edges.push_back(Edge(f, g, 1 + rand() % 10));

  map<Node, vector<pair<Node *, int>>> adj_list;
  adj_list.insert({a, {{&b, 1}, {&d, 1}}});
  adj_list.insert({b, {{&a, 1}, {&c, 1}}});
  adj_list.insert({c, {{&b, 1}, {&e, 1}}});
  adj_list.insert({d, {{&a, 1}, {&b, 1}, {&e, 1}, {&f, 1}}});
  adj_list.insert({e, {{&b, 1}, {&c, 1}, {&d, 1}, {&f, 1}, {&g, 1}}});
  adj_list.insert({f, {{&d, 1}, {&e, 1}, {&g, 1}}});
  adj_list.insert({g, {{&e, 1}, {&f, 1}}});

  for (Node &node : nodes) {
    auto it = adj_list.find(node);
    if (it != adj_list.end()) {
      node.set_adjacency_list(it->second);
    } else {
      cout << "Node not found into adjacency list: " << node.get_name() << endl;
    }
  }

  Graph graph(nodes, edges);

  graph.dfs();

  for (Node node : graph.get_nodes()) {
    cout << "Node: " << node.get_name() << ", Distance: " << node.get_distance()
         << ", End visit: " << node.get_end_visit() << endl;
  }

  return 0;
}