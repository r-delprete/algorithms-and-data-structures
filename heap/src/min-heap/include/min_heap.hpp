#ifndef MIN_HEAP_HPP
#define MIN_HEAP_HPP

#include <fstream>
#include <iostream>
#include <vector>

class MinHeap {
private:
  std::vector<int> data;
  int size;

  void min_heapify(int index) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int min = index;

    if (left < size && data[left] < data[min]) min = left;
    if (right < size && data[right] < data[min]) min = right;

    if (min != index) {
      std::swap(data[min], data[index]);
      min_heapify(min);
    }
  }

  void build_min_heap() {
    for (int i = size / 2; i >= 0; i--) min_heapify(i);
  }

  void shift_up(int index) {
    while (index > 0 && data[(index - 1) / 2] > data[index]) {
      std::swap(data[index], data[(index - 1) / 2]);
      index = (index - 1) / 2;
    }
  }

  int search(int key) {
    for (int i = 0; i < data.size(); i++) {
      if (data[i] == key) return i;
    }

    return -1;
  }

public:
  MinHeap(std::ifstream& input_file) {
    int value;
    while (input_file >> value) data.push_back(value);
    input_file.close();

    size = data.size();

    build_min_heap();
  }

  void print() {
    for (auto& value : data) std::cout << value << "\t";
    std::cout << std::endl;
  }

  void print_in_file(std::ofstream& output_file) {
    for (auto& value : data) output_file << value << "\t";
    output_file << std::endl;

    output_file.close();
  }

  void decrease_key(int old_key, int new_key) {
    if (new_key > old_key) {
      std::cerr << "New key is greater than old key" << std::endl;
      return;
    }

    int index = search(old_key);

    if (index == -1) return;

    data[index] = new_key;
    shift_up(index);
  }

  void heap_sort() {
    build_min_heap();

    for (int i = size - 1; i >= 0; i--) {
      std::swap(data[0], data[i]);
      size--;
      min_heapify(0);
    }
  }

  int* extract_min() {
    if (size == 0) {
      std::cerr << "Heap is empty" << std::endl;
      return nullptr;
    }

    int* min = new int(data[0]);
    std::swap(data[0], data[size - 1]);
    size--;
    data.pop_back();
    min_heapify(0);

    return min;
  }
};

#endif  // MIN_HEAP_HPP