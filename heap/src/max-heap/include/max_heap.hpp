#ifndef MAX_HEAP_HPP
#define MAX_HEAP_HPP

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

class MaxHeap {
  std::vector<std::unique_ptr<int>> data;
  int size;

  void build_heap() {
    for (int i = size / 2; i >= 0; i--) heapify(i, size);
  }

  void heapify(int index, int size) {
    int max = index, left = 2 * index + 1, right = 2 * index + 2;

    if (left < size && *data[left] > *data[max]) max = left;
    if (right < size && *data[right] > *data[max]) max = right;

    if (max != index) {
      std::swap(data[max], data[index]);
      heapify(max, size);
    }
  }

  int search(int item) {
    for (int i = 0; i < data.size(); i++) {
      if (*data[i] == item) return i;
    }

    std::cerr << "Item " << item << " not found" << std::endl;
    return -1;
  }

  void shift_up(int index) {
    while (index > 0 && *data[(index - 1) / 2] < *data[index]) {
      std::swap(data[index], data[(index - 1) / 2]);
      index = (index - 1) / 2;
    }
  }

public:
  MaxHeap() : size(0) {}

  MaxHeap(std::ifstream& input) : size(0) { load(input); }

  void load(std::ifstream& input) {
    input.clear();
    input.seekg(0, std::ios::beg);

    data.clear();

    std::string line;
    std::getline(input, line);

    line = line.front() == '<' ? line.substr(1) : line;
    if (line.back() == '>') line.pop_back();
    for (auto& c : line) c = (c == ',' ? ' ' : c);

    std::istringstream stream(line);
    int item;
    while (stream >> item) insert(std::unique_ptr<int>(new int(item)));
    stream.clear();

    build_heap();
  }

  void insert(std::unique_ptr<int> item) {
    data.push_back(std::move(item));
    size = data.size();
    shift_up(size - 1);
  }

  std::unique_ptr<int> extract_max() {
    if (data.empty()) {
      std::cerr << "Heap is empty" << std::endl;
      return nullptr;
    }

    std::unique_ptr<int> max = std::move(data[0]);
    std::swap(data[0], data[size - 1]);
    size--;
    data.pop_back();
    heapify(0, size);

    return max;
  }

  void heap_sort() {
    build_heap();
    for (int i = size - 1; i >= 0; i--) {
      std::swap(data[0], data[i]);
      size--;
      heapify(0, i);
    }
  }

  void print(std::string message = "Heap", std::ostream& out = std::cout) {
    out << message << std::endl;
    for (const auto& value : data) out << *value << "\t";
    out << std::endl;
  }

  void increase_key(int new_value, int old_value) {
    if (new_value < old_value) {
      std::cerr << "New value is less than old value" << std::endl;
      return;
    }

    int index = search(old_value);
    if (index != -1) {
      data[index].reset(new int(new_value));
      shift_up(index);
    }
  }
};

#endif
