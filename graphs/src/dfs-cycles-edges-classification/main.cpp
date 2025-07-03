#include "./include/graph.hpp"

using namespace std;

int main(int argc, char **argv) {
  ifstream input("input.txt");
  ofstream output("output.txt");

  Graph graph(input);

  graph.dfs();
  graph.print_into_file(output);
  cout << endl;
  graph.print_edges();

  input.close();
  output.close();

  return 0;
}