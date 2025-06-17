#include "./include/graph.hpp"

using namespace std;

int main(int argc, char **argv) {
  ifstream input_file("input.txt");
  ofstream output_file("output.txt");

  Graph graph(input_file);

  graph.dfs();
  graph.print_into_file(output_file);
  cout << endl;
  graph.print_edges();
}