#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

class MaxHeap {
private:
  vector<int> data;
  int size;

  void build_max_heap() {
    for (int i = size / 2; i >= 0; i--) max_heapify(i);
  }

  void max_heapify(int index) {
    int max = index;
    int left = 2 * index + 1, right = 2 * index + 2;

    if (left < size && data[max] < data[left]) max = left;
    if (right < size && data[max] < data[right]) max = right;

    if (max != index) {
      swap(data[max], data[index]);
      max_heapify(max);
    }
  }

  void shift_up(int index) {
    while (index > 0 && data[(index - 1) / 2] < data[index]) {
      swap(data[(index - 1) / 2], data[index]);
      index = (index - 1) / 2;
    }
  }

public:
  MaxHeap(ifstream& input_file) : size(size) {
    int value;

    while (input_file >> value) data.push_back(value);
    size = data.size();

    build_max_heap();
  }

  int* extract_max() {
    if (data.empty()) {
      cerr << "Heap is empty" << endl;
      return nullptr;
    }

    int* max = new int(data[0]);
    swap(data[0], data[size - 1]);
    data.pop_back();
    size--;
    max_heapify(0);

    cout << "Heap maximum element: " << *max << endl;
    return max;
  }

  void heap_sort() {
    build_max_heap();

    for (int i = size - 1; i >= 0; i--) {
      swap(data[i], data[0]);
      size--;
      max_heapify(0);
    }
  }

  int* search(int key) {
    for (int i = 0; i < data.size(); i++) {
      if (data[i] == key) {
        cout << "Element with key " << key << " found at index " << i << endl;
        return new int(i);
      }
    }

    cerr << "Element with key " << key << " not found" << endl;
    return nullptr;
  }

  void increase_key(int old_key, int new_key) {
    if (new_key < old_key) {
      cerr << "New key is less than old key" << endl;
      return;
    }

    int* index = search(old_key);

    if (index) {
      data[*index] = new_key;
      shift_up(*index);
      cout << "Increased key " << old_key << " to " << new_key << endl;
      return;
    }

    cerr << "Cannot increase key " << old_key << " to " << new_key << endl;
    return;
  }

  void print() {
    for (auto& item : data) {
      cout << item << "\t";
    }
    cout << endl;
  }

  void print(ofstream& output_file) {
    for (auto& item : data) {
      output_file << item << "\t";
    }
    output_file << endl;
  }
};

int main(void) {
  ifstream input_file("input.txt");
  ofstream output_file("output.txt");

  MaxHeap h(input_file);
  h.print();
  cout << endl;
  h.print(output_file);

  h.increase_key(10, 30);
  h.extract_max();

  h.heap_sort();
  cout << endl << "After heap sort" << endl;
  output_file << endl << "After heap sort" << endl;
  h.print();
  h.print(output_file);

  input_file.close();
  output_file.close();

  return 0;
}