#include "max_heap.hpp"

Max_Heap::Max_Heap(const vector<int>& data) {
  max_heap = data;
  build_max_heap();
}

const vector<int> Max_Heap::get_max_heap() const { return this->max_heap; }

int Max_Heap::left(int node_index) const { return 2 * node_index + 1; }

int Max_Heap::right(int node_index) const { return 2 * node_index + 2; }

int Max_Heap::parent(int node_index) const { return (node_index - 1) / 2; }

void Max_Heap::max_heapify(int node_index, int heap_size) {
  int largest = node_index;
  int left = this->left(node_index);
  int right = this->right(node_index);

  if (left < heap_size && max_heap[left] > max_heap[largest]) {
    largest = left;
  }

  if (right < heap_size && max_heap[right] > max_heap[largest]) {
    largest = right;
  }

  if (largest != node_index) {
    swap(max_heap[node_index], max_heap[largest]);
    max_heapify(largest, heap_size);
  }
}

void Max_Heap::build_max_heap() {
  int heap_size = max_heap.size();

  for (int i = heap_size / 2 - 1; i >= 0; i--) {
    max_heapify(i, heap_size);
  }
}

void Max_Heap::print_heap() const {
  for (int val : max_heap) {
    cout << val << " ";
  }
  cout << endl;
}

void Max_Heap::heap_sort() {
  int heap_size = max_heap.size();
  build_max_heap();

  for (int i = heap_size - 1; i >= 1; i--) {
    swap(max_heap[0], max_heap[i]);
    heap_size--;
    max_heapify(0, heap_size);
  }
}