#include "min_priority_queue.hpp"

/**
 * Constructor - initializes the heap with given nodes and comparator
 * @param elements Element to insert into minimum priority queue
 * @param comp Compare function to compare minimum priority queue elements
 */
template <typename T, typename Compare>
MinPriorityQueue<T, Compare>::MinPriorityQueue(const vector<T>& elements, Compare comp) : heap(comp, elements) {}

/**
 * Inserts a new element into the priority queue
 */
template <typename T, typename Compare>
void MinPriorityQueue<T, Compare>::insert(const T& value) {
  heap.push(value);
}

/**
 * Removes and returns the minimum element from the queue
 * Returns by value to avoid ownership issues
 */
template <typename T, typename Compare>
T* MinPriorityQueue<T, Compare>::extract_min() {
  if (heap.empty()) {
    throw runtime_error("Priority queue is empty.");
  }
  T* min_value = new T(heap.top());
  heap.pop();
  return min_value;
}

/**
 * Returns a const reference to the minimum element without removing it
 */
template <typename T, typename Compare>
T MinPriorityQueue<T, Compare>::get_min() const {
  if (heap.empty()) {
    throw runtime_error("Priority queue is empty.");
  }
  return heap.top();
}

/**
 * Checks if the priority queue is empty
 */
template <typename T, typename Compare>
bool MinPriorityQueue<T, Compare>::is_empty() const {
  return heap.empty();
}

/**
 * Returns the number of elements in the priority queue
 */
template <typename T, typename Compare>
size_t MinPriorityQueue<T, Compare>::size() const {
  return heap.size();
}

/**
 * Explicit template instantiation for Node type
 */
template class MinPriorityQueue<Node, CompareNodes>;