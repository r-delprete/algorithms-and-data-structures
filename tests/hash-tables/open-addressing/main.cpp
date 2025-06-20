#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <typename K, typename V>
class Item {
private:
  K key;
  V value;

public:
  Item(K key, V value) : value(value), key(key) {}

  K get_key() { return key; }
  V get_value() { return value; }

  void set_key(K key) { this->key = key; }
  void set_value(V value) { this->value = value; }
};

template <typename K, typename V>
class HashTable {
private:
private:
  vector<Item<K, V>*> data;
  int size;

public:
  HashTable(ifstream& input_file, int size) : size(size) {
    data.resize(size, nullptr);

    K key;
    V value;

    while (input_file >> key >> value) insert(new Item<K, V>(key, value));
  }

  int linear_hashing(K key, int index) { return (key + index) % size; }
  int quadratic_hashing(K key, int index) { return (key + index + index * index) % size; }
  int double_hashing(K key, int index) {
    int hash1 = key % size;
    int hash2 = 1 + (key % (size - 1));

    return (hash1 + index * hash2) % size;
  }

  void insert(Item<K, V>* element) {
    for (int i = 0; i < size; i++) {
      int index = linear_hashing(element->get_key(), i);

      if (data[index] && data[index]->get_key() == element->get_key()) {
        cerr << "Element [Key: " << data[index]->get_key() << " - Value: " << data[index]->get_value()
             << "] already inserted" << endl;
        return;
      }

      if (data[index] == nullptr) {
        data[index] = element;
        return;
      }
    }

    cerr << "overflow" << endl;
    return;
  }

  int* search(K key) {
    for (int i = 0; i < size; i++) {
      int index = linear_hashing(key, i);

      if (data[index] == nullptr) {
        cerr << "Element with key " << key << " not found" << endl;
        return nullptr;
      }

      if (data[index]->get_key() == key) {
        cout << "Element with key " << key << " found at index " << index << endl;
        return new int(index);
      }
    }

    cerr << "Element with key " << key << " not found" << endl;
    return nullptr;
  }

  void delete_element(K key) {
    for (int i = 0; i < size; i++) {
      int index = linear_hashing(key, i);

      if (data[index] == nullptr) {
        cerr << "Element with key " << key << " not found" << endl;
        return;
      }

      if (data[index]->get_key() == key) {
        cout << "Element [Key: " << key << " - Value: " << data[index]->get_value() << "] deleted" << endl;
        data[index] = nullptr;
        return;
      }
    }

    cerr << "Element with key " << key << " not deleted" << endl;
    return;
  }

  void print() {
    for (int i = 0; i < size; i++) {
      data[i] ? cout << "Index: " << i << " - [Key: " << data[i]->get_key() << " - Value: " << data[i]->get_value()
                     << "]" << endl
              : cout << "Index: " << i << " - [empty]" << endl;
    }

    cout << endl;
  }

  void print(ofstream& output_file) {
    for (int i = 0; i < size; i++) {
      data[i] ? output_file << "Index: " << i << " - [Key: " << data[i]->get_key()
                            << " - Value: " << data[i]->get_value() << "]" << endl
              : output_file << "Index: " << i << " - [empty]" << endl;
    }

    output_file << endl;
  }

  Item<K, V>* get_element(int index) { return data[index] ? data[index] : nullptr; }
};

int main(void) {
  ifstream input_file("input.txt");
  ofstream output_file("output.txt");

  HashTable<int, string> ht(input_file, 10);

  ht.print();
  ht.print(output_file);

  ht.search(8);
  ht.delete_element(8);

  input_file.close();
  output_file.close();

  return 0;
}