#include "./include/min_heap.hpp"

using namespace std;

int main(int argc, char** argv) {
  ifstream input_file("input.txt");
  ofstream output_file("output.txt");

  MinHeap mh(input_file);

  mh.print_in_file(output_file);
  mh.print();

  mh.decrease_key(25, 14);
  cout << endl << "After decrease key:" << endl;
  mh.print();

  int* min = mh.extract_min();

  if (min) cout << endl << "Minimum value: " << *min << endl;

  mh.heap_sort();

  cout << endl << "After heap sort:" << endl;
  mh.print();

  return 0;
}