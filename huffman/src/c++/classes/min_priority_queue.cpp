#include "min_priority_queue.hpp"

MinPriorityQueue::MinPriorityQueue(vector<Node> nodes) {
  for (const Node& node : nodes) {
    heap.push(node);
  }
}

void MinPriorityQueue::insert(const Node& value) { heap.push(value); }

Node* MinPriorityQueue::extract_min() {
  if (heap.empty()) {
    throw runtime_error("Priority queue is empty.");
  }
  Node* min_value = new Node(heap.top());
  heap.pop();
  return min_value;
}

Node MinPriorityQueue::get_min() const {
  if (heap.empty()) {
    throw runtime_error("Priority queue is empty.");
  }
  return heap.top();
}

bool MinPriorityQueue::is_empty() const { return heap.empty(); }

size_t MinPriorityQueue::size() const { return heap.size(); }