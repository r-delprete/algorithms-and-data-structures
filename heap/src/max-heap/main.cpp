#include "./include/max_heap.hpp"

using namespace std;

int main(int argc, char** argv) {
  ifstream input("input.txt");
  ifstream input2("input2.txt");
  ofstream output("output.txt");

  MaxHeap mh2(input2);
  MaxHeap mh(input2);
  mh2.print("\nHeap with brackets and comma");
  int max = mh2.extract_max();
  cout << "\nMax heap value => ";
  (max != -1 ? cout << max : cout << "NULL");
  cout << endl;

  mh2.heap_sort();
  mh2.print("\nAfter heap sort");

  mh.load(input);
  mh.print("\nHeap without brackets and comma");

  int old_value = 25;
  int new_value = 1;
  cout << endl;
  mh.decrease_key(old_value, new_value);
  mh.print();
  mh.increase_key(1, 35);
  mh.print();
  max = mh.extract_max();
  cout << "Max heap value => ";
  (max != -1 ? cout << max : cout << "NULL");
  cout << endl;
  mh.heap_sort();
  mh.print("\nAfter heap sort");

  input.close();
  input2.close();
  output.close();

  return 0;
}