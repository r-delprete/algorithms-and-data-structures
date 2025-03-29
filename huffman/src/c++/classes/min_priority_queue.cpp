#include "min_priority_queue.hpp"

MinPriorityQueue::MinPriorityQueue(vector<Node> nodes) {
  if (!nodes.empty()) {
    for (Node& node : nodes) {
      heap.push_back(node);
      heapify_up(heap.size() - 1);
    }
  }
}

// Function to perform "heapify" upwards to maintain the min-heap property
void MinPriorityQueue::heapify_up(int index) {
  if (index == 0) return;  // If we are at the root, we cannot go higher
  int parent = (index - 1) / 2;
  if (heap[index] < heap[parent]) {
    heap[index].swap(heap[parent]);
    heapify_up(parent);  // Continue climbing up the tree
  }
}

// Function to perform "heapify" downwards to maintain the min-heap property
void MinPriorityQueue::heapify_down(int index) {
  int left_child = 2 * index + 1;
  int right_child = 2 * index + 2;
  int smallest = index;

  // Find the smallest child (left child)
  if (left_child < heap.size() && heap[left_child] < heap[smallest]) {
    smallest = left_child;
  }

  // Find the smallest child (right child)
  if (right_child < heap.size() && heap[right_child] < heap[smallest]) {
    smallest = right_child;
  }

  // If the current node is not the smallest, swap with the smallest child
  if (smallest != index) {
    heap[index].swap(heap[smallest]);
    heapify_down(smallest);  // Continue to descend the tree
  }
}

// Function to insert an element into the priority queue
void MinPriorityQueue::insert(const Node& value) {
  heap.push_back(value);        // Add the element at the end of the heap
  heapify_up(heap.size() - 1);  // Maintain the heap property by climbing up
}

// Function to extract the element with the highest priority (minimum value)
Node* MinPriorityQueue::extract_min() {
  if (heap.empty()) {
    throw runtime_error("Priority queue is empty.");
  }

  Node* min_value = &heap[0];  // The element with the highest priority is at the root
  heap[0] = heap.back();       // Replace the root with the last element
  heap.pop_back();             // Remove the last element
  heapify_down(0);             // Maintain the heap property by descending

  return min_value;
}

// Function to get the element with the highest priority without removing it
Node MinPriorityQueue::get_min() const {
  if (heap.empty()) {
    throw runtime_error("Priority queue is empty.");
  }
  return heap[0];  // The root contains the element with the highest priority
}

// Function to check if the priority queue is empty
bool MinPriorityQueue::is_empty() const { return heap.empty(); }

// Function to return the size of the priority queue
size_t MinPriorityQueue::size() const { return heap.size(); }

// Function to print the queue
void MinPriorityQueue::print_queue() {
  for (Node& node : heap) {
    cout << node.get_node() << endl;
  }
}