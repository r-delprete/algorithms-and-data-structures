#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

#include "../../../../cpp-utils/logger.hpp"
#include "item.hpp"

enum Hashing { linear, double_hash, quadratic };

template <typename K, typename V>
class HashTable {
  std::vector<std::unique_ptr<Item<K, V>>> data;
  int size;
  Hashing hashing = Hashing::linear;

  int h(const K& key, int index) {
    switch (hashing) {
      case Hashing::double_hash: {
        int hash1 = key % size;
        int hash2 = 1 + (key % (size - 1));
        return (hash1 + index * hash2) % size;
      }
      case Hashing::quadratic:
        return (key + index + index * index) % size;
      default:
        return (key + index) % size;
    }
  }

public:
  HashTable(int size, Hashing hashing = Hashing::linear) : size(size), hashing(hashing) { data.resize(size); }

  HashTable(int size, std::ifstream& input, Hashing hashing = Hashing::linear) : size(size), hashing(hashing) {
    data.resize(size);
    load(input);
  }

  void load(std::ifstream& input) {
    input.clear();
    input.seekg(0, std::ios::beg);

    std::string line;
    while (std::getline(input, line)) {
      line = line.front() == '<' ? line.substr(1) : line;
      if (line.back() == '>') line.pop_back();
      for (auto& c : line) c = c == ',' ? ' ' : c;

      std::istringstream stream(line);
      K key;
      V value;

      stream >> key >> value;
      insert(std::unique_ptr<Item<K, V>>(new Item<K, V>(key, value)));

      stream.clear();
    }
  }

  void insert(std::unique_ptr<Item<K, V>> item) {
    for (int i = 0; i < size; i++) {
      int index = h(item->get_key(), i);

      if (!data[index]) {
        data[index] = std::move(item);
        return;
      }
    }

    log("overflow", LogLevel::ERROR);
  }

  void print(std::string message = "Hash table", std::ostream& out = std::cout) {
    out << message << std::endl;

    for (int i = 0; i < size; i++) {
      out << "Index " << i << " => ";
      if (!data[i])
        out << "empty";
      else
        data[i]->print(out);
      out << std::endl;
    }

    out << std::endl;
  }

  std::unique_ptr<Item<K, V>> search(const K& key) {
    std::ostringstream oss;

    for (int i = 0; i < size; i++) {
      int index = h(key, i);

      if (!data[index]) {
        oss.clear();
        oss << "Not found item with key " << key << " at index " << index;
        log(oss.str(), LogLevel::ERROR);
        return nullptr;
      }

      if (data[index]->get_key() == key) {
        oss.clear();
        oss << "Found item with key " << key << " at index " << index;
        log(oss.str());

        return std::move(data[index]);
      }
    }

    oss.clear();
    oss << "Item with key " << key << " not found";
    ::log(oss.str(), LogLevel::ERROR);
    return nullptr;
  }

  void delete_item(const K& key) {
    std::ostringstream oss;

    for (int i = 0; i < size; i++) {
      int index = h(key, i);

      if (!data[index]) {
        oss.clear();
        oss << "Not found item with key " << key << " at index " << index;
        log(oss.str(), LogLevel::ERROR);
        return;
      }

      if (data[index]->get_key() == key) {
        oss.clear();
        oss << "Deleting item ";
        data[index]->print(oss);
        oss << "...";
        log(oss.str());

        data[index] = nullptr;
        log("Item deleted successfully");

        return;
      }
    }

    oss.clear();
    oss << "Item with key " << key << " not deleted";
    ::log(oss.str(), LogLevel::ERROR);
  }
};