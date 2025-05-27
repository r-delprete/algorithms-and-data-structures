#ifndef HEAP_HPP
#define HEAP_HPP

#include <iostream>
#include <vector>

using namespace std;

class MaxHeap {
private:
  vector<int> max_heap;

  void max_heapify(int node_index, int heap_size) {
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
  };

public:
  MaxHeap(const vector<int>& data) : max_heap(data) { build_max_heap(); };

  const vector<int> get_max_heap() const { return this->max_heap; };

  int parent(int node_index) const { return (node_index - 1) / 2; };

  int left(int node_index) const { return 2 * node_index + 1; };

  int right(int node_index) const { return 2 * node_index + 2; };

  void build_max_heap() {
    int heap_size = max_heap.size();

    for (int i = heap_size / 2 - 1; i >= 0; i--) {
      max_heapify(i, heap_size);
    }
  };

  void print_heap() const {
    for (int val : max_heap) {
      cout << val << " ";
    }
    cout << endl;
  };

  void heap_sort() {
    int heap_size = max_heap.size();
    build_max_heap();

    for (int i = heap_size - 1; i >= 1; i--) {
      swap(max_heap[0], max_heap[i]);
      heap_size--;
      max_heapify(0, heap_size);
    }
  };
};

#endif