#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

class MinHeap {
private:
  vector<int> data;
  int size;

  void build_min_heap() {
    for (int i = size / 2; i >= 0; i--) min_heapify(i);
  }

  void min_heapify(int index) {
    int min = index;
    int left = 2 * index + 1, right = 2 * index + 2;

    if (left < size && data[left] < data[min]) min = left;
    if (right < size && data[right] < data[min]) min = right;

    if (min != index) {
      swap(data[min], data[index]);
      min_heapify(min);
    }
  }

  int* search(int key) {
    for (int i = 0; i < data.size(); i++) {
      if (data[i] == key) return new int(i);
    }

    cerr << "Key " << key << " not found" << endl;
    return nullptr;
  }

  void shift_up(int index) {
    while (index > 0 && data[(index - 1) / 2] > data[index]) {
      swap(data[(index - 1) / 2], data[index]);
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

  void heap_sort() {
    for (int i = size - 1; i >= 0; i--) {
      swap(data[0], data[i]);
      size--;
      min_heapify(0);
    }
  }

  int* extract_min() {
    if (data.empty()) {
      cerr << "Heap is empty" << endl;
      return nullptr;
    }

    int* min = new int(data[0]);
    swap(data[0], data[size - 1]);
    data.pop_back();
    size--;

    return min;
  }

  void print() {
    for (int i = 0; i < data.size(); i++) {
      cout << "Index: " << i << " - Value: " << data[i] << endl;
    }
    cout << endl;
  }

  void print(ostream& output_file) {
    for (int i = 0; i < data.size(); i++) {
      output_file << "Index: " << i << " - Value: " << data[i] << endl;
    }
    output_file << endl;
  }

  void decrease_key(int old_key, int new_key) {
    if (new_key > old_key) {
      cerr << "New key is greater than old key" << endl;
      return;
    }

    int* index = search(old_key);

    if (!index) {
      cerr << "Old key index " << old_key << " not found";
      return;
    }

    data[*index] = new_key;
    shift_up(*index);

    cout << "Decreased key " << old_key << " to " << new_key << endl;
  }
};

int main(void) {
  ifstream input_file("input.txt");
  ofstream output_file("output.txt");

  MinHeap h(input_file);

  h.print();
  h.print(output_file);

  int* min = h.extract_min();
  min ? cout << "Min value: " << *min << endl : cerr << "Min value not found" << endl;
  min ? output_file << "Min value: " << *min << endl : cerr << "Min value not found" << endl;
  cout << endl;
  output_file << endl;

  int old_key = 15, new_key = 1;
  h.decrease_key(old_key, new_key);
  h.print();
  output_file << "After decreasing " << old_key << " to " << new_key << endl;
  h.print(output_file);

  cout << "After heap sort" << endl;
  output_file << "After heap sort" << endl;
  h.heap_sort();
  h.print();
  h.print(output_file);

  input_file.close();
  output_file.close();

  return 0;
}