#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include <cmath>
#include <fstream>
#include <iostream>
#include <list>
#include <vector>

#include "item.hpp"

template <typename K, typename V>
class Hash_Table {
private:
  std::vector<std::list<Item<K, V>*>> ht;
  int size;

public:
  Hash_Table(int size, std::ifstream& input_file) : size(size) {
    ht.resize(size);

    K key;
    V value;
    while (input_file >> key >> value) insert(new Item<K, V>(key, value));
    input_file.close();
  }

  int divide_hashing(K key) { return key % size; }
  int multiply_hashing(K key) {
    int A = (sqrt(5) - 1) / 2;

    return size * (key * A % 1);
  }

  void insert(Item<K, V>* element) {
    int index = divide_hashing(element->get_key());
    ht[index].push_back(element);
  }

  Item<K, V>* search(K key) {
    int index = divide_hashing(key);

    for (auto& item : ht[index]) {
      if (item->get_key() == key) return item;
    }

    std::cerr << "Element not found" << std::endl;
    return nullptr;
  }

  void delete_element(K key) {
    int index = divide_hashing(key);

    for (auto it = ht[index].begin(); it != ht[index].end(); it++) {
      if ((*it)->get_key() == key) {
        ht[index].erase(it);
        return;
      }
    }

    std::cerr << "Element not found" << std::endl;
  }

  void print_in_file(std::ofstream& output_file) {
    for (int i = 0; i < size; i++) {
      output_file << "Index: " << i;

      if (ht[i].empty())
        output_file << " -> empty bucket" << std::endl;
      else {
        for (auto& item : ht[i]) {
          output_file << " -> [key: " << item->get_key() << " - value: " << item->get_value() << "]";
        }

        output_file << std::endl;
      }
    }

    output_file.close();
  }

  void print() {
    for (int i = 0; i < size; i++) {
      std::cout << "Index: " << i;

      if (ht[i].empty())
        std::cout << " -> empty bucket" << std::endl;
      else {
        for (auto& item : ht[i]) {
          std::cout << " -> [key: " << item->get_key() << " - value: " << item->get_value() << "]";
        }

        std::cout << std::endl;
      }
    }
  }
};

#endif  // HASH_TABLE_HPP