#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include <cmath>
#include <fstream>
#include <iostream>
#include <list>
#include <vector>

#include "item.hpp"

enum HashingFunction { divide, multiply };

template <typename K, typename V>
class Hash_Table {
private:
  std::vector<std::list<Item<K, V>*>> ht;
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
  Hash_Table(int size, std::ifstream& input_file, HashingFunction fn = divide) : size(size) {
    ht.resize(size);
    set_hashing_function(fn);

    K key;
    V value;
    while (input_file >> key >> value) insert(new Item<K, V>(key, value));
    input_file.close();
  }

  void set_hashing_function(HashingFunction fn) {
    if (this->fn == fn) return;

    std::cout << "Changing hashing function from " << (this->fn == multiply ? "MULTIPLY" : "DIVIDE") << " to "
              << (fn == multiply ? "MULTIPLY" : "DIVIDE") << std::endl;
    this->fn = fn;
  }

  void insert(Item<K, V>* element) {
    int index = h(element->get_key());
    ht[index].push_back(element);
  }

  Item<K, V>* search(K key) {
    int index = h(key);

    for (auto& item : ht[index]) {
      if (item->get_key() == key) {
        std::cout << "Item " << "[Key: " << item->get_key() << " - Value: " << item->get_value() << "] found in list -"
                  << index << "-" << std::endl;
        return item;
      }
    }

    std::cerr << "Item with key -" << key << "- not found in list -" << index << "-" << std::endl;
    return nullptr;
  }

  void delete_element(K key) {
    int index = h(key);

    for (auto it = ht[index].begin(); it != ht[index].end(); it++) {
      if ((*it)->get_key() == key) {
        auto item = (*it);
        ht[index].erase(it);
        std::cout << "Item " << "[Key: " << item->get_key() << " - Value: " << item->get_value() << "] deleted"
                  << std::endl;
        return;
      }
    }

    std::cerr << "Item with key -" << key << "- not found in list -" << index << "-" << std::endl;
    return;
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