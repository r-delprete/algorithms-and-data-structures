#ifndef MIN_PRIORITY_QUEUE_HPP
#define MIN_PRIORITY_QUEUE_HPP

#include <algorithm>
#include <stdexcept>
#include <vector>

#include "node.hpp"

using namespace std;

struct CompareNodes {
  bool operator()(const Node& a, const Node& b) const {
    if (a.get_frequency() != b.get_frequency()) {
      return a.get_frequency() > b.get_frequency();  // Invertiamo il segno per il min-heap
    }
    return !a.is_combined() && b.is_combined();
  }
};

/**
 * Class used to define a min priority queue which contains
 * Node objects
 */
class MinPriorityQueue {
private:
  priority_queue<Node, vector<Node>, CompareNodes> heap;

public:
  MinPriorityQueue(vector<Node> nodes = {});
  void insert(const Node& value);
  Node* extract_min();
  Node get_min() const;
  bool is_empty() const;
  size_t size() const;
};

#endif  // MIN_PRIORITY_QUEUE_HPP
