#include "./classes/max_heap.hpp"

int main(int argc, char **argv) {
  vector<int> data = {4, 10, 3, 5, 1};

  MaxHeap max_heap(data);

  cout << "Max heap builded: ";
  max_heap.print_heap();

  max_heap.heap_sort();
  cout << "Max heap after heap sort: ";
  max_heap.print_heap();

  return 0;
}