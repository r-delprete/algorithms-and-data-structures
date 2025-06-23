#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

class MinHeap {
private:
  vector<int> data;
  int size;

  void build_min_heap() {
    for (int i = size / 2; i >= 0; i--) heapify(i);
  }

  void heapify(int index) {
    int min = index, left = 2 * index + 1, right = 2 * index + 2;

    if (left < size && data[min] > data[left]) min = left;
    if (right < size && data[min] > data[right]) min = right;

    if (min != index) {
      swap(data[index], data[min]);
      heapify(min);
    }
  }

  void shift_up(int index) {
    while (index > 0 && data[(index - 1) / 2] > data[index]) {
      swap(data[index], data[(index - 1) / 2]);
      index = (index - 1) / 2;
    }
  }

public:
  MinHeap(ifstream& input_file) {
    int value;
    while (input_file >> value) data.push_back(value);
    size = data.size();

    build_min_heap();
  }

  int* extract_min() {
    if (data.empty()) {
      cerr << endl << "Heap is empty" << endl;
      return nullptr;
    }

    int* min = new int(data[0]);
    swap(data[0], data[size - 1]);
    data.pop_back();
    size--;
    heapify(0);

    cout << endl << "Heap minimum element: " << *min << endl;
    return min;
  }

  int* search(int key) {
    for (int i = 0; i < data.size(); i++) {
      if (data[i] == key) {
        cout << endl << "Element with key " << key << " found at index " << i << endl;
        return new int(i);
      }
    }

    cerr << endl << "Element with key " << key << " not found" << endl;
    return nullptr;
  }

  void decrease_key(int old_key, int new_key) {
    if (new_key > old_key) {
      cerr << endl << "Old key is greater than new key" << endl;
      return;
    }

    int* index = search(old_key);

    if (index) {
      data[*index] = new_key;
      shift_up(*index);
      cout << endl << "Decreased key " << old_key << " to " << new_key << endl;
      return;
    }
  }

  void heap_sort() {
    build_min_heap();

    for (int i = size - 1; i >= 0; i--) {
      swap(data[0], data[i]);
      size--;
      heapify(0);
    }
  }

  void print() {
    for (int i = 0; i < data.size(); i++) {
      cout << "Index: " << i << " -> " << " key: " << data[i] << endl;
    }
  }

  void print(ofstream& output_file) {
    for (int i = 0; i < data.size(); i++) {
      output_file << "Index: " << i << " -> " << " key: " << data[i] << endl;
    }
  }
};

int main(void) {
  ifstream input_file("input.txt");
  ofstream output_file("output.txt");

  MinHeap h(input_file);
  h.print();
  h.print(output_file);

  h.extract_min();
  cout << endl << "After minimum extraction" << endl;
  h.print();

  h.decrease_key(25, 10);

  h.heap_sort();
  cout << endl << "After heap sort" << endl;
  h.print();
  output_file << endl << "After heap sort" << endl;
  h.print(output_file);

  input_file.close();
  output_file.close();

  return 0;
}