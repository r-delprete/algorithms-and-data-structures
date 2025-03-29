#include "huffman.hpp"

Node huffman(vector<Node>& nodes) {
  MinPriorityQueue queue(nodes);

  cout << "Queue is empty = " << queue.is_empty() << endl << endl;
  cout << "Queue" << endl;
  queue.print_queue();
  cout << endl;

  while (!queue.is_empty()) {
    Node node;

    node.set_left_child(queue.extract_min());
    node.set_right_child(queue.extract_min());

    node.set_frequency(node.get_left_child()->get_frequency() + node.get_right_child()->get_frequency());

    cout << "Node: " << node.get_node() << endl << endl;

    queue.insert(node);
  }

  return *(queue.extract_min());
}