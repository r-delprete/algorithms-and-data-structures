#include "./include/max_heap.hpp"

using namespace std;

int main(int argc, char** argv) {
  ifstream input("input.txt");
  ifstream input2("input2.txt");
  ofstream output("output.txt");

  MaxHeap mh2(input2);
  MaxHeap mh(input2);
  mh2.print("\nHeap with brackets and comma");
  unique_ptr<int> max = mh2.extract_max();
  cout << "\nMax heap value => ";
  if (max)
    cout << *max;
  else
    cout << "NULL";
  cout << endl;

  mh2.heap_sort();
  mh2.print("\nAfter heap sort");

  mh.load(input);
  mh.print("\nHeap without brackets and comma");

  int old_value = 20;
  int new_value = 40;
  mh.increase_key(40, 20);
  mh.print("\nAfter increasing " + to_string(20) + " to " + to_string(40));
  max = mh.extract_max();
  cout << "\nMax heap value => ";
  if (max)
    cout << *max;
  else
    cout << "NULL";
  cout << endl;

  input.close();
  input2.close();
  output.close();

  return 0;
}