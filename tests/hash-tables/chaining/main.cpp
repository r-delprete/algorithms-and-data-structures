#include <cmath>
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <vector>

using namespace std;

enum HashingFunction { divide, multiply };

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
  vector<list<Item<K, V>*>> data;
  int size;
  HashingFunction fn = divide;

  int h(K key) {
    int ret = 0;

    switch (fn) {
      case HashingFunction::multiply: {
        double prod = ((sqrt(5) - 1) / 2) * key;
        double frac = prod - floor(prod);
        ret = size * frac;
        break;
      }
      default: {
        ret = key % size;
        break;
      }
    }

    return ret;
  }

public:
  HashTable(int size, ifstream& input_file, HashingFunction fn = divide) : size(size) {
    data.resize(size);

    set_hashing_function(fn);

    K key;
    V value;
    while (input_file >> key >> value) insert(new Item<K, V>(key, value));
  }

  void set_hashing_function(HashingFunction fn) {
    if (this->fn == fn) return;

    cout << "Changing hashing function from " << (this->fn == multiply ? "MULTIPLY" : "DIVIDE") << " to "
         << (fn == multiply ? "MULTIPLY" : "DIVIDE") << endl;
    this->fn = fn;
  }

  void insert(Item<K, V>* item) {
    int index = h(item->get_key());
    data[index].push_back(item);
  }

  Item<K, V>* search(K key) {
    int index = h(key);

    for (auto& item : data[index]) {
      if (item->get_key() == key) {
        cout << "Item " << "[Key: " << item->get_key() << " - Value: " << item->get_value() << "] found in list -"
             << index << "-" << endl;
        return item;
      }
    }

    cerr << "Item with key -" << key << "- not found in list -" << index << "-" << endl;
    return nullptr;
  }

  void delete_item(K key) {
    int index = h(key);

    for (auto it = data[index].begin(); it != data[index].end(); it++) {
      if ((*it)->get_key() == key) {
        auto item = (*it);
        data[index].erase(it);
        cout << "Item " << "[Key: " << item->get_key() << " - Value: " << item->get_value() << "] deleted" << endl;
        return;
      }
    }

    cerr << "Item with key -" << key << "- not found in list -" << index << "-" << endl;
    return;
  }

  void print() {
    for (int i = 0; i < size; i++) {
      cout << "Index " << i;
      if (!data[i].empty()) {
        for (auto& item : data[i])
          cout << " -> " << "[Key: " << item->get_key() << " - Value: " << item->get_value() << "]";
      } else
        cout << " -> [empty list]";
      cout << endl;
    }
  }

  void print(ofstream& output_file) {
    for (int i = 0; i < size; i++) {
      output_file << "Index " << i;
      if (!data[i].empty()) {
        for (auto& item : data[i])
          output_file << " -> " << "[Key: " << item->get_key() << " - Value: " << item->get_value() << "]";
      } else
        output_file << " -> [empty list]";
      output_file << endl;
    }
  }
};

int main() {
  ifstream input_file("input.txt");
  ofstream output_file("output.txt");

  HashTable<int, string> ht(10, input_file);
  ht.print();
  ht.print(output_file);

  ht.search(5);
  ht.delete_item(5);

  cout << endl << "After deleting" << endl;
  output_file << endl << "After deleting" << endl;
  ht.print();
  ht.print(output_file);

  input_file.close();
  output_file.close();

  return 0;
}