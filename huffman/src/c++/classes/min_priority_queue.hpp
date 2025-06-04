#ifndef MIN_PRIORITY_QUEUE_HPP
#define MIN_PRIORITY_QUEUE_HPP

#include <algorithm>
#include <queue>
#include <stdexcept>
#include <vector>

#include "node.hpp"

using namespace std;

/**
 * Generic min priority queue implementation using a heap
 * @tparam T The type of elements in the priority queue
 * @tparam Compare Comparison function object type (defaults to less<T>)
 */
template <typename T, typename Compare = less<T>>
class MinPriorityQueue {
private:
  priority_queue<T, vector<T>, Compare> heap;

public:
  /**
   * Constructor - initializes the heap with given nodes and comparator
   * @param elements Element to insert into minimum priority queue
   * @param comp Compare function to compare minimum priority queue elements
   */
  MinPriorityQueue(const vector<T>& nodes = {}, Compare comp = Compare()) : heap(comp, nodes) {}

  /**
   * Inserts a new element into the priority queue
   */
  void insert(const T& value) { heap.push(value); }

  /**
   * Removes and returns the minimum element from the queue
   * Returns by value to avoid ownership issues
   */
  T* extract_min() {
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
  T get_min() const {
    if (heap.empty()) {
      throw runtime_error("Priority queue is empty.");
    }
    return heap.top();
  }

  /**
   * Checks if the priority queue is empty
   */
  bool is_empty() const { return heap.empty(); }

  /**
   * Returns the number of elements in the priority queue
   */
  size_t size() const { return heap.size(); }
};

template class MinPriorityQueue<Node, CompareNodes>;

#endif  // MIN_PRIORITY_QUEUE_HPP
