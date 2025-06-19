
#ifndef MAX_HEAP_HPP
#define MAX_HEAP_HPP

#include <fstream>
#include <iostream>
#include <vector>

class MaxHeap {
private:
  std::vector<int> data;
  int size;

  void build_max_heap() {
    for (int i = size / 2; i >= 0; i--) max_heapify(i);
  }

  void max_heapify(int index) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int max = index;

    if (left < size && data[left] > data[max]) max = left;
    if (right < size && data[right] > data[max]) max = right;

    if (max != index) {
      std::swap(data[max], data[index]);
      max_heapify(max);
    }
  }

  int search(int key) {
    for (int i = 0; i < data.size(); i++) {
      if (data[i] = key) return i;
    }

    return -1;
  }

  void shift_up(int index) {
    while (index > 0 && data[(index - 1) / 2] < data[index]) {
      std::swap(data[(index - 1) / 2], data[index]);
      index = (index - 1) / 2;
    }
  }

public:
  MaxHeap(std::ifstream& input_file) {
    int value;
    while (input_file >> value) data.push_back(value);
    input_file.close();

    size = data.size();

    build_max_heap();
  }

  int* extract_max() {
    if (size == 0) {
      std::cerr << "Heap is empty" << std::endl;
      return nullptr;
    }

    int* max = new int(data[0]);
    std::swap(data[0], data[size - 1]);
    size--;
    data.pop_back();
    max_heapify(0);

    return max;
  }

  void increase_key(int old_key, int new_key) {
    if (new_key < old_key) {
      std::cerr << "New key is less than old key" << std::endl;
      return;
    }

    int index = search(old_key);

    if (index == -1) {
      std::cerr << "Old key not found" << std::endl;
      return;
    }

    data[index] = new_key;
    shift_up(index);
  }

  void heap_sort() {
    build_max_heap();

    for (int i = size - 1; i >= 0; i--) {
      std::swap(data[0], data[i]);
      size--;
      max_heapify(0);
    }
  }

  void print() {
    for (int& value : data) std::cout << value << "\t";
    std::cout << std::endl;
  }

  void print_in_file(std::ofstream& out) {
    for (int& value : data) out << value << "\t";
    out << std::endl;

    out.close();
  }
};

#endif  // MAX_HEAP_HPP