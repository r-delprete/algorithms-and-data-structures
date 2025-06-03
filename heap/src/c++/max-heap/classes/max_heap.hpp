#ifndef HEAP_HPP
#define HEAP_HPP

#include <iostream>
#include <vector>

using namespace std;

/**
 * MaxHeap class which implements a max heap data structure.
 * It provides methods for maintaining the max heap property, building the heap from a vector, and performing heap sort.
 */
class MaxHeap {
private:
  vector<int> max_heap;

  /**
   * Function to maintain the max heap property.
   * It checks if the current node is smaller than its children and swaps it with the larger child.
   * This process is repeated recursively until the max heap property is restored.
   * @param node_index The index of the node to be heapified.
   * @param heap_size The size of the heap.
   */
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

  /**
   * Function to build a max heap from the given vector.
   * It starts from the last non-leaf node and applies max_heapify to each node.
   */
  void build_max_heap() {
    int heap_size = max_heap.size();

    for (int i = heap_size / 2 - 1; i >= 0; i--) {
      max_heapify(i, heap_size);
    }
  };

public:
  /**
   * Default constructor for MaxHeap.
   * Initializes an empty max heap.
   * Execute the build_max_heap function to ensure the heap property is maintained.
   */
  MaxHeap(const vector<int>& data) : max_heap(data) { build_max_heap(); };

  const vector<int> get_max_heap() const { return this->max_heap; };

  /**
   * Function to get the index of the parent node of a given node.
   * @param node_index The index of the node whose parent index is to be found.
   * @return The index of the parent node.
   */
  int parent(int node_index) const { return (node_index - 1) / 2; };

  /**
   * Function to get the index of the left child of a given node.
   * @param node_index The index of the node whose left child's index is to be found.
   * @return The index of the left child node.
   */
  int left(int node_index) const { return 2 * node_index + 1; };

  /**
   * Function to get the index of the right child of a given node.
   * @param node_index The index of the node whose right child's index is to be found.
   * @return The index of the right child node.
   */
  int right(int node_index) const { return 2 * node_index + 2; };

  /**
   * Function to print the elements of the max heap.
   */
  void print_heap() const {
    for (int val : max_heap) {
      cout << val << " ";
    }
    cout << endl;
  };

  /**
   * Function to sort the elements of the max heap using heap sort algorithm.
   */
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