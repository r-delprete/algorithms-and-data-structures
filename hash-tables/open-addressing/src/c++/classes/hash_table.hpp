#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "./item.hpp"

template <typename K, typename V>
class Hash_Table {
private:
  std::vector<Item<K, V>*> hash_table;
  int size;

public:
  Hash_Table(int size) : size(size) { hash_table.resize(size, nullptr); }

  int linear_hashing(K key, int index) { return (key + index) % size; }
  int quadratic_hashing(K key, int index) { return (key + index + pow(index, 2)) % size; }
  int double_hashing(K key, int index) {
    int hash1 = key % size;
    int hash2 = 1 + (key % (size - 1));

    return (hash1 + index * hash2) % size;
  }

  int get_size() { return size; }

  void insert(Item<K, V>* element) {
    int i = 0;

    while (i < size) {
      int index = linear_hashing(element->key, i);

      if (hash_table[index] == nullptr) {
        hash_table[index] = element;
        return;
      }

      i++;
    }

    std::cerr << "overflow" << std::endl;
  }

  void print() {
    for (int i = 0; i < hash_table.size(); i++) {
      if (hash_table[i] != nullptr) {
        std::cout << "Index: " << i << "\tKey: " << hash_table[i]->key << "\tValue: " << hash_table[i]->value
                  << std::endl;
      }
    }
  }

  void print_in_file(std::ofstream& output_file) {
    for (int i = 0; i < hash_table.size(); i++) {
      if (hash_table[i] != nullptr) {
        output_file << "Index: " << i << "\tKey: " << hash_table[i]->key << "\tValue: " << hash_table[i]->value
                    << std::endl;
      }
    }

    output_file.close();
  }

  void load_from_file(std::ifstream& input_file) {
    K key;
    V value;

    while (input_file >> key >> value) {
      insert(new Item<K, V>(key, value));
    }

    input_file.close();
  }

  V* find(K key) {
    int i = 0;

    while (i < size) {
      int index = linear_hashing(key, i);

      if (hash_table[index] == nullptr) return nullptr;

      if (hash_table[index]->key == key) return &hash_table[index]->value;

      i++;
    }

    return nullptr;
  }

  bool delete_element(K key) {
    int i = 0;

    while (i < size) {
      int index = linear_hashing(key, i);

      if (hash_table[index] == nullptr) return false;

      if (hash_table[index]->key == key) {
        hash_table[index] = nullptr;
        return true;
      }

      i++;
    }

    return false;
  }
};

#endif  // HASH_TABLE_HPP