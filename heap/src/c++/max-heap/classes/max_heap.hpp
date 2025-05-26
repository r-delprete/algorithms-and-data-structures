#ifndef HEAP_HPP
#define HEAP_HPP

#include <iostream>
#include <vector>

using namespace std;

class Max_Heap {
private:
  vector<int> max_heap;
  void max_heapify(int node_index, int heap_size);

public:
  Max_Heap(const vector<int>& data);
  const vector<int> get_max_heap() const;
  int parent(int node_index) const;
  int left(int node_index) const;
  int right(int node_index) const;
  void build_max_heap();
  void print_heap() const;
  void heap_sort();
};

#endif