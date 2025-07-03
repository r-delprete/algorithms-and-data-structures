#ifndef MIN_HEAP_HPP
#define MIN_HEAP_HPP

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

class MinHeap {
  std::vector<std::unique_ptr<int>> data;
  int size;

  void build_heap() {
    for (int i = size / 2; i >= 0; i--) heapify(i, size);
  }

  void heapify(int index, int size) {
    int min = index, left = 2 * index + 1, right = 2 * index + 2;

    if (left < size && *data[min] > *data[left]) min = left;
    if (right < size && *data[min] > *data[right]) min = right;

    if (min != index) {
      std::swap(data[index], data[min]);
      heapify(min, size);
    }
  }

  int search(int item) {
    for (int i = 0; i < data.size(); i++) {
      if (*data[i] == item) return i;
    }

    std::cerr << "[Search error] => Item " << item << " not found" << std::endl;
    return -1;
  }

  void shift_up(int index) {
    while (index > 0 && *data[(index - 1) / 2] > *data[index]) {
      std::swap(data[index], data[(index - 1) / 2]);
      index = (index - 1) / 2;
    }
  }

public:
  MinHeap() {}

  MinHeap(std::ifstream& input) { load(input); }

  void load(std::ifstream& input) {
    std::string line;
    std::getline(input, line);
    line = line.front() == '<' ? line.substr(1) : line;
    if (line.back() == '>') line.pop_back();
    for (auto& c : line) c = c == ',' ? ' ' : c;

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

  std::unique_ptr<int> extract_min() {
    if (data.empty()) {
      std::cerr << "[extract_min error] => Heap is empty" << std::endl;
      return nullptr;
    }

    std::unique_ptr<int> min = std::move(data[0]);
    std::swap(data[0], data[size - 1]);
    size--;
    data.pop_back();
    heapify(0, size);

    return min;
  }

  void heap_sort() {
    build_heap();

    for (int i = size - 1; i >= 0; i--) {
      std::swap(data[0], data[i]);
      size--;
      heapify(0, i);
    }
  }

  void decrease_key(int old_value, int new_value) {
    if (new_value > old_value) {
      std::cerr << "[decrease_key error] => New value is greater than old value" << std::endl;
      return;
    }

    int index = search(old_value);
    if (index != -1) {
      data[index].reset(new int(new_value));
      shift_up(index);
    }
  }

  void print(std::string message = "Heap", std::ostream& out = std::cout) {
    out << message << std::endl;
    for (const auto& value : data) out << *value << "\t";
    out << std::endl;
  }
};

#endif  // MIN_HEAP_HPP