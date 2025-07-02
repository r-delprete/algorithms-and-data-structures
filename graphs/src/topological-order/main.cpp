#include "./include/graph.hpp"

using namespace std;

int main(int argc, char** argv) {
  ifstream input("input.txt");
  ifstream input2("input2.txt");
  ofstream output("output.txt");

  Graph graph(input2);

  graph.print();
  graph.print(output);
  graph.dfs();
  graph.print_topological_order();

  graph.find_hamiltonian_cycle(0);
  cout << endl;
  output << endl;

  Node* src = graph.get_node(0);
  Node* dest = graph.get_node(3);

  if (!src) cerr << "Node " << src->get_data() << "not found" << endl;
  if (!dest) cerr << "Node " << dest->get_data() << "not found" << endl;

  if (src && dest) {
    graph.bellman_ford(src, dest);
    graph.bellman_ford(src, dest, output);
  }

  src = graph.get_node(0);

  if (!src)
    cerr << "Node " << src->get_data() << "not found" << endl;
  else {
    graph.dijkstra(src);
    graph.dijkstra(src, output);
  }

  input.close();
  output.close();

  return 0;
}