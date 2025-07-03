#include "./include/min_heap.hpp"

using namespace std;

int main(int argc, char** argv) {
  ifstream input("input.txt");
  ifstream input2("input2.txt");
  ofstream output("output.txt");

  MinHeap heap(input);
  MinHeap heap2(input2);

  heap.print("Heap with easiest input");
  heap2.print("\nHeap with hardest input");

  unique_ptr<int> min = heap.extract_min();

  cout << endl << "Minimum value (easiest input) => ";
  min ? cout << *min : cout << "NULL";
  cout << endl;

  heap2.decrease_key(20, 1);
  heap2.print("\nAfter decrease key");

  input.close();
  input2.close();
  output.close();

  return 0;
}