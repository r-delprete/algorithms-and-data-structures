#include "./include/graph.hpp"

using namespace std;

int main(int argc, char** argv) {
  ifstream input_file("input.txt");
  ofstream output_file("output.txt");

  Graph graph(input_file);

  graph.dfs();
  graph.print_topological_order(output_file);

  graph.find_hamiltonian_cycle(0);

  Node* src = graph.get_node(0);
  Node* dest = graph.get_node(3);

  if (!src) cerr << "Node " << src->get_data() << "not found" << endl;
  if (!dest) cerr << "Node " << dest->get_data() << "not found" << endl;

  if (src && dest) graph.bellman_ford(src, dest);

  src = graph.get_node(0);

  if (!src)
    cerr << "Node " << src->get_data() << "not found" << endl;
  else
    graph.dijkstra(src);

  return 0;
}