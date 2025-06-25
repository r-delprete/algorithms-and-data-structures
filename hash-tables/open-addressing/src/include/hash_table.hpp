#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "item.hpp"

enum HashingFunction { linear, quadratic, double_hash };

template <typename K, typename V>
class Hash_Table {
private:
  std::vector<Item<K, V>*> data;
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
  Hash_Table(std::ifstream& input_file, int size) : size(size) {
    data.resize(size, nullptr);
    K key;
    V value;

    while (input_file >> key >> value) {
      insert(new Item<K, V>(key, value));
    }
  }

  void set_hashing_function(HashingFunction fn) {
    if (this->fn == fn) return;

    std::cout << "Changing hashing function from "
              << (this->fn == HashingFunction::quadratic     ? "QUADRATIC"
                  : this->fn == HashingFunction::double_hash ? "DOUBLE HASHING"
                                                             : "LINEAR")
              << " to "
              << (fn == HashingFunction::quadratic     ? "QUADRATIC"
                  : fn == HashingFunction::double_hash ? "DOUBLE HASHING"
                                                       : "LINEAR")
              << std::endl;
    this->fn = fn;
  }

  void insert(Item<K, V>* item) {
    for (int i = 0; i < size; i++) {
      int index = h(item->get_key(), i);

      if (data[index] && data[index]->get_key() == item->get_key()) {
        std::cerr << "Item [Key: " << item->get_key() << " - Value: " << item->get_value() << "] already inserted"
                  << std::endl;
        return;
      }

      if (data[index] == nullptr) {
        data[index] = item;
        return;
      }
    }

    std::cerr << "Overflow" << std::endl;
    return;
  }

  Item<K, V>* search(K key) {
    int i = 0;

    for (int i = 0; i < size; i++) {
      int index = h(key, i);

      if (data[index] == nullptr) {
        std::cerr << "Item not found in position " << index << std::endl;
        return nullptr;
      }

      if (data[index]->get_key() == key) {
        std::cout << "Item [Key: " << data[index]->get_key() << " - Value: " << data[index]->get_value()
                  << "] found at position " << index << std::endl;
        return data[index];
      }
    }

    std::cerr << "Element not found" << std::endl;
    return nullptr;
  }

  void delete_element(K key) {
    for (int i = 0; i < size; i++) {
      int index = h(key, i);

      if (!data[index]) {
        std::cerr << "Item not found in position " << index << std::endl;
        return;
      }

      if (data[index]->get_key() == key) {
        auto item = data[index];
        data[index] = nullptr;
        std::cout << "Item [Key: " << item->get_key() << " - Value: " << item->get_value() << "] deleted" << std::endl;

        return;
      }
    }

    std::cerr << "Item with key " << key << " not deleted" << std::endl;
    return;
  }

  void print() {
    for (int i = 0; i < size; i++) {
      std::cout << "Index: " << i;
      if (data[i])
        std::cout << " -> [Key: " << data[i]->get_key() << " - Value: " << data[i]->get_value() << "]";
      else
        std::cout << " empty";
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }

  void print(std::ofstream& output_file) {
    for (int i = 0; i < size; i++) {
      output_file << "Index: " << i;
      if (data[i])
        output_file << " -> [Key: " << data[i]->get_key() << " - Value: " << data[i]->get_value() << "]";
      else
        output_file << " empty";
      output_file << std::endl;
    }
    output_file << std::endl;
  }
};

#endif  // HASH_TABLE_HPP