#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include <cmath>
#include <fstream>
#include <list>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "item.hpp"
#include "logger.hpp"

enum Hashing { multiply, division };

template <typename K, typename V>
class HashTable {
  std::vector<std::list<std::unique_ptr<Item<K, V>>>> data;
  int size;
  Hashing hashing;

  int h(K key) {
    switch (hashing) {
      case Hashing::multiply: {
        double product = ((sqrt(5) - 1) / 2) * key;
        double frac = product - floor(product);
        return frac * size;
      }
      default:
        return key % size;
    }
  }

public:
  HashTable(int size, Hashing hashing = division) : size(size) { data.resize(size); }

  HashTable(int size, std::ifstream& input, Hashing hashing = division) : size(size) {
    data.resize(size);
    load(input);
  }

  void load(std::ifstream& input) {
    std::string line;
    while (std::getline(input, line)) {
      if (line.front() == '<') line = line.substr(1);
      if (line.back() == '>') line.pop_back();
      for (auto& c : line) c = c == ',' ? ' ' : c;

      std::istringstream ss(line);
      K key;
      V value;

      ss >> key >> value;
      insert(std::unique_ptr<Item<K, V>>(new Item<K, V>(key, value)));
      ss.clear();
    }
  }

  void insert(std::unique_ptr<Item<K, V>> item) {
    int index = h(item->get_key());
    data[index].push_back(std::move(item));
  }

  Item<K, V>* search(K key) {
    std::ostringstream oss;

    int index = h(key);
    if (data[index].empty()) {
      log("List " + std::to_string(index) + " is empty", LogLevel::ERROR);
      return nullptr;
    }

    for (auto& item : data[index]) {
      if (item->get_key() == key) {
        oss << "Item ";
        item->print(oss);
        oss << " found in list " << index;
        log(oss.str());

        return item.get();
      }
    }

    oss.clear();
    oss << "Item " << key << " not found in list " << index;
    log(oss.str(), LogLevel::ERROR);
    return nullptr;
  }

  void delete_item(K key) {
    std::ostringstream oss;

    int index = h(key);

    if (data[index].empty()) {
      log("List " + std::to_string(index) + " is empty", LogLevel::ERROR);
      return;
    }

    for (auto it = data[index].begin(); it != data[index].end(); it++) {
      if ((*it)->get_key() == key) {
        oss << "Item ";
        (*it)->print(oss);
        oss << " deleted from list " << index;
        log(oss.str());

        data[index].erase(it);
        return;
      }
    }

    oss.clear();
    oss << "Item " << key << " not found in list " << index;
    log(oss.str(), LogLevel::ERROR);
    return;
  }

  void print(std::string message = "Hash table", std::ostream& out = std::cout) {
    out << message << std::endl;

    for (int i = 0; i < size; i++) {
      out << "List " << i;
      if (data[i].empty())
        out << " => empty list";
      else {
        for (auto& item : data[i]) {
          out << " => ";
          item->print(out);
        };
      }
      out << std::endl;
    }

    out << std::endl;
  }
};

#endif