#include "./classes/graph.hpp"

using namespace std;

int main(int argc, char** argv) {
  ifstream input_file("input.txt");
  ofstream output_file("output.txt");

  Graph graph(input_file);

  Node* src = graph.get_node(0);

  if (src)
    graph.bfs(src, output_file);
  else
    cerr << "Cannot execute BFS because source doesn't exists" << endl;

  if (graph.is_complete_binary())
    cout << endl << "BF tree is complete binary" << endl;
  else
    cout << endl << "BF tree is not complete binary" << endl;

  if (src) {
    graph.prim(src);
    graph.print_mst();
  } else {
    cerr << "Cannot execute Prim because source doesn't exists" << endl;
  }

  if (graph.is_binary())
    cout << endl << "MST is a binary tree" << endl;
  else
    cout << endl << "MST is not a binary tree" << endl;
}