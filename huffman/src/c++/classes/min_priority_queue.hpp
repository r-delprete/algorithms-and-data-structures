#ifndef MIN_PRIORITY_QUEUE_HPP
#define MIN_PRIORITY_QUEUE_HPP

#include <algorithm>
#include <stdexcept>
#include <vector>

#include "node.hpp"

using namespace std;

/**
 * Class used to define a min priority queue which contains
 * Node objects
 */
class MinPriorityQueue {
private:
  vector<Node> heap;
  vector<Node> nodes;

  // Function to perform "heapify" upwards to maintain the min-heap property
  void heapify_up(int index);

  // Function to perform "heapify" downwards to maintain the min-heap property
  void heapify_down(int index);

public:
  // Constructor
  MinPriorityQueue(vector<Node> nodes = {});

  // Function to insert an element into the priority queue
  void insert(const Node& value);

  // Function to extract the element with the highest priority (minimum value)
  Node* extract_min();

  // Function to get the element with the highest priority without removing it
  Node get_min() const;

  // Checks if the priority queue is empty
  bool is_empty() const;

  // Returns the size of the priority queue
  size_t size() const;

  // Print the queue
  void print_queue();
};

#endif  // MIN_PRIORITY_QUEUE_HPP
