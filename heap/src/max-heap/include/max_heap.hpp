#ifndef MAX_HEAP_HPP
#define MAX_HEAP_HPP

#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../../../../cpp-utils/logger.hpp"

class MaxHeap {
  std::vector<int> data;
  int size;

  void build_heap() {
    for (int i = size / 2; i >= 0; i--) heapify(i, size);
  }

  void heapify(int index, int size) {
    int max = index, left = 2 * index + 1, right = 2 * index + 2;

    if (left < size && data[max] < data[left]) max = left;
    if (right < size && data[max] < data[right]) max = right;

    if (max != index) {
      std::swap(data[max], data[index]);
      heapify(max, size);
    }
  }

  void clear_data() { data.clear(); }

  void shift_up(int index) {
    while (index > 0 && data[(index - 1) / 2] < data[index]) {
      std::swap(data[index], data[(index - 1) / 2]);
      index = (index - 1) / 2;
    }
  }

  int search(int key) {
    std::ostringstream ss;

    if (data.empty()) {
      log("(search) => Heap is empty");
      return -1;
    }

    for (int i = 0; i < data.size(); i++) {
      if (key == data[i]) {
        ss << "(search) => " << key << " found at index " << i;
        log(ss.str());
        return i;
      }
    }

    ss.clear();
    ss.str("");
    ss << "(search) => " << key << " not found";
    log(ss.str(), LogLevel::ERROR);
    return -1;
  }

public:
  MaxHeap(int size) : size(size) {}

  MaxHeap(std::ifstream& input) {
    load(input);
    size = data.size();
    build_heap();
  }

  void load(std::ifstream& input) {
    clear_data();
    input.clear();
    input.seekg(0, std::ios::beg);

    std::string line;
    if (std::getline(input, line)) {
      line = line.front() == '<' ? line.substr(1) : line;
      if (line.back() == '>') line.pop_back();
      for (auto& ch : line) ch = ch == ',' ? ' ' : ch;

      std::istringstream ss(line);
      int value;
      while (ss >> value) insert(value);

      ss.clear();
      ss.str("");
    }
  }

  void insert(int value) {
    data.push_back(value);
    size = data.size();
    shift_up(size - 1);
  }

  void heap_sort() {
    build_heap();
    for (int i = size - 1; i >= 0; i--) {
      std::swap(data[0], data[i]);
      size--;
      heapify(0, i);
    }
  }

  int extract_max() {
    if (data.empty()) {
      log("Heap is empty", LogLevel::ERROR);
      return -1;
    }

    int max = data[0];
    std::swap(data[0], data[size - 1]);
    size--;
    data.pop_back();
    heapify(0, size);

    return max;
  }

  void print(std::string message = "Heap", std::ostream& out = std::cout) {
    out << message << std::endl;

    if (data.empty()) {
      log("Heap is empty", LogLevel::ERROR);
      return;
    }

    for (int i = 0; i < data.size(); i++) out << data[i] << "\t";

    out << std::endl;
  }

  void decrease_key(int old_key, int new_key) {
    std::ostringstream ss;
    ss << "(decrease_key) => trying to decrease " << old_key << " to " << new_key;
    log(ss.str());
    ss.clear();
    ss.str("");

    if (new_key > old_key) {
      log("New key is greater than old key", LogLevel::ERROR);
      return;
    }

    int index = search(old_key);
    if (index != -1) {
      data[index] = new_key;
      heapify(index, size);

      ss << "(decrease_key) => decreased " << old_key << " to " << new_key;
      log(ss.str());
    }
  }

  void increase_key(int old_key, int new_key) {
    std::ostringstream ss;
    ss << "(increase_key) => trying to increase " << old_key << " to " << new_key;
    log(ss.str());
    ss.clear();
    ss.str("");

    if (new_key < old_key) {
      log("New key is less than old key", LogLevel::ERROR);
      return;
    }

    int index = search(old_key);
    if (index != -1) {
      data[index] = new_key;
      shift_up(index);

      ss << "(increase_key) => increase " << old_key << " to " << new_key;
      log(ss.str());
    }
  }
};

#endif