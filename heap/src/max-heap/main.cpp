#include "./include/max_heap.hpp"

using namespace std;

int main(int argc, char** argv) {
  ifstream input_file("input.txt");
  ofstream output_file("output.txt");

  MaxHeap mh(input_file);

  mh.print_in_file(output_file);
  mh.print();

  mh.increase_key(10, 22);
  cout << endl << "After increase key:" << endl;
  mh.print();

  int* max = mh.extract_max();

  if (max) cout << endl << "Maximum value: " << *max << endl;

  mh.heap_sort();

  cout << endl << "After heap sort:" << endl;
  mh.print();

  return 0;
}