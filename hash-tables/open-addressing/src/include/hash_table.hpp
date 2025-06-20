#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "item.hpp"

template <typename K, typename V>
class Hash_Table {
private:
  std::vector<Item<K, V>*> ht;
  int size;

public:
  Hash_Table(std::ifstream& input_file, int size) : size(size) {
    ht.resize(size, nullptr);
    K key;
    V value;

    while (input_file >> key >> value) {
      insert(new Item<K, V>(key, value));
    }

    input_file.close();
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

      if (ht[index] == nullptr) {
        ht[index] = element;
        return;
      }
    }

    std::cerr << "Overflow" << std::endl;
  }

  Item<K, V>* search(K key) {
    int i = 0;

    for (int i = 0; i < size; i++) {
      int index = linear_hashing(key, i);

      if (ht[index] == nullptr) {
        std::cerr << "Element not found" << std::endl;
        return nullptr;
      }

      if (ht[index]->get_key() == key) return ht[index];
    }

    std::cerr << "Element not found" << std::endl;
    return nullptr;
  }

  void delete_element(K key) {
    int i = 0;

    for (int i = 0; i < size; i++) {
      int index = linear_hashing(key, i);

      if (ht[index] == nullptr) {
        std::cerr << "Element not found" << std::endl;
        return;
      };

      if (ht[index]->get_key() == key) {
        ht[index] = nullptr;
        return;
      }
    }
  }

  void print_in_file(std::ofstream& output_file) {
    for (int i = 0; i < size; i++) {
      ht[i] ? output_file << "Index: " << i << " - key: " << ht[i]->get_key() << " - value: " << ht[i]->get_value()
                          << std::endl
            : output_file << "Index: " << i << " - empty" << std::endl;
      ;
    }

    output_file.close();
  }

  void print() {
    for (int i = 0; i < size; i++) {
      ht[i] ? std::cout << "Index: " << i << " - key: " << ht[i]->get_key() << " - value: " << ht[i]->get_value()
                        << std::endl
            : std::cout << "Index: " << i << " - empty" << std::endl;
    }
  }
};

#endif  // HASH_TABLE_HPP