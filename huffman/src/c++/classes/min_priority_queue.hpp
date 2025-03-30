#ifndef MIN_PRIORITY_QUEUE_HPP
#define MIN_PRIORITY_QUEUE_HPP

#include <algorithm>
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
  MinPriorityQueue(const vector<T>& nodes = {}, Compare comp = Compare());
  void insert(const T& value);
  T* extract_min();
  T get_min() const;
  bool is_empty() const;
  size_t size() const;
};

#endif  // MIN_PRIORITY_QUEUE_HPP
