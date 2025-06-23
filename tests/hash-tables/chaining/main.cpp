#include <cmath>
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <vector>

using namespace std;

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
  vector<list<Item<K, V>*>> hash_table;
  int size;

public:
  HashTable(ifstream& input_file, int size) : size(size) {
    hash_table.resize(size);

    K key;
    V value;
    while (input_file >> key >> value) insert(new Item<K, V>(key, value));
  }

  int divide_hashing(K key) { return key % size; }
  int multiply_hashing(K key) {
    int A = (sqrt(5) - 1) / 2;

    return size * (key * A % 1);
  }

  void insert(Item<K, V>* item) {
    int index = divide_hashing(item->get_key());
    hash_table[index].push_back(item);
  }

  Item<K, V>* search(K key) {
    int index = divide_hashing(key);

    for (auto& item : hash_table[index]) {
      if (item->get_key() == key) {
        cout << "Item [key: " << item->get_key() << " - value: " << item->get_value() << "] found in list with index "
             << index << endl;
        return item;
      }
    }

    cerr << "Item with key " << key << " not found in list with index " << index << endl;
    return nullptr;
  }

  void delete_item(K key) {
    int index = divide_hashing(key);

    for (auto it = hash_table[index].begin(); it != hash_table[index].end(); it++) {
      auto item = (*it);
      if (item->get_key() == key) {
        cout << "Item [key: " << item->get_key() << " - value: " << item->get_value() << "] deleted" << endl;
        hash_table[index].erase(it);
        return;
      }
    }

    cerr << "Item with key " << key << "not deleted" << endl;
    return;
  }

  void print() {
    for (int i = 0; i < size; i++) {
      cout << "Index " << i;
      if (hash_table[i].empty()) {
        cout << " -> empty list" << endl;
      } else {
        for (auto& item : hash_table[i]) {
          cout << " -> [key: " << item->get_key() << " - value: " << item->get_value() << "]";
        }
        cout << endl;
      }
    }
    cout << endl;
  }

  void print(ofstream& out) {
    for (int i = 0; i < size; i++) {
      out << "Index " << i;
      if (hash_table[i].empty()) {
        out << " -> empty list" << endl;
      } else {
        for (auto& item : hash_table[i]) {
          out << " -> [key: " << item->get_key() << " - value: " << item->get_value() << "]";
        }
        out << endl;
      }
    }

    out << endl;
  }
};

int main(void) {
  ifstream input_file("input.txt");
  ofstream output_file("output.txt");

  HashTable<int, string> ht(input_file, 10);
  ht.print();
  ht.print(output_file);

  ht.search(8);
  ht.delete_item(8);

  cout << endl << "After delete" << endl;
  output_file << endl << "After delete" << endl;
  ht.print();
  ht.print(output_file);

  input_file.close();
  output_file.close();

  return 0;
}