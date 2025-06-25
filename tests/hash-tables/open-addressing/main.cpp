#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

enum HashingFunction { linear, quadratic, double_hash };

template <typename K, typename V>
class Item {
private:
  K key;
  V value;

public:
  Item(K key, V value) : key(key), value(value) {}

  K get_key() { return key; }
  V get_value() { return value; }

  void set_key(K key) { this->key = key; }
  void set_value(V value) { this->value = value; }
};

template <typename K, typename V>
class HashTable {
private:
  vector<Item<K, V>*> data;
  int size;
  HashingFunction fn = linear;

  int h(K key, int index) {
    switch (fn) {
      case quadratic: {
        return (key + index + index * index) % size;
      }

      case double_hash: {
        int hash1 = key % size;
        int hash2 = 1 + (key % (size - 1));
        return (hash1 + index * hash2) % size;
      }

      default:
        return (key + index) % size;
    }
  }

public:
  HashTable(int size, ifstream& input_file, HashingFunction fn = linear) : size(size) {
    set_hashing_function(fn);
    data.resize(size, nullptr);

    K key;
    V value;
    while (input_file >> key >> value) insert(new Item<K, V>(key, value));
  }

  void set_hashing_function(HashingFunction fn) {
    if (this->fn == fn) return;

    cout << "Changing hashing function from "
         << (this->fn == HashingFunction::quadratic     ? "QUADRATIC"
             : this->fn == HashingFunction::double_hash ? "DOUBLE HASHING"
                                                        : "LINEAR")
         << " to "
         << (fn == HashingFunction::quadratic     ? "QUADRATIC"
             : fn == HashingFunction::double_hash ? "DOUBLE HASHING"
                                                  : "LINEAR")
         << endl;
    this->fn = fn;
  }

  void insert(Item<K, V>* item) {
    for (int i = 0; i < size; i++) {
      int index = h(item->get_key(), i);

      if (data[index] && data[index]->get_key() == item->get_key()) {
        cerr << "Item [Key: " << item->get_key() << " - Value: " << item->get_value() << "] already inserted" << endl;
        return;
      }

      if (!data[index]) {
        data[index] = item;
        return;
      }
    }

    cerr << "Overflow" << endl;
    return;
  }

  Item<K, V>* search(K key) {
    for (int i = 0; i < size; i++) {
      int index = h(key, i);

      if (!data[index]) {
        cerr << "Item not found in position " << index << endl;
        return nullptr;
      }

      if (data[index]->get_key() == key) {
        cout << "Item [Key: " << data[index]->get_key() << " - Value: " << data[index]->get_value()
             << "] found at position " << index << endl;
        return data[index];
      }
    }

    cerr << "Item with key " << key << " not found" << endl;
    return nullptr;
  }

  void delete_item(K key) {
    for (int i = 0; i < size; i++) {
      int index = h(key, i);

      if (!data[index]) {
        cerr << "Item not found in position " << index << endl;
        return;
      }

      if (data[index]->get_key() == key) {
        auto item = data[index];
        data[index] = nullptr;
        cout << "Item [Key: " << item->get_key() << " - Value: " << item->get_value() << "] deleted" << endl;

        return;
      }
    }

    cerr << "Item with key " << key << " not deleted" << endl;
    return;
  }

  void print() {
    for (int i = 0; i < size; i++) {
      cout << "Index: " << i;
      if (data[i])
        cout << " -> [Key: " << data[i]->get_key() << " - Value: " << data[i]->get_value() << "]";
      else
        cout << " empty";
      cout << endl;
    }
    cout << endl;
  }

  void print(ofstream& output_file) {
    for (int i = 0; i < size; i++) {
      output_file << "Index: " << i;
      if (data[i])
        output_file << " -> [Key: " << data[i]->get_key() << " - Value: " << data[i]->get_value() << "]";
      else
        output_file << " empty";
      output_file << endl;
    }
    output_file << endl;
  }
};

int main() {
  ifstream input_file("input.txt");
  ofstream output_file("output.txt");

  HashTable<int, string> ht(10, input_file);
  ht.print();
  ht.print(output_file);

  ht.search(6);
  ht.delete_item(6);

  cout << "After delete" << endl;
  ht.print();

  input_file.close();
  output_file.close();

  return 0;
}