#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include <cmath>
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
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
    switch (fn) {
      case HashingFunction::multiply: {
        double prod = ((sqrt(5) - 1) / 2) * key;
        double frac = prod - floor(prod);
        return size * frac;
      }
      default:
        return key % size;
    }
  }

public:
  Hash_Table(int size, std::ifstream& input, bool complex_input = false, HashingFunction fn = divide) : size(size) {
    ht.resize(size);
    set_hashing_function(fn);

    if (complex_input) {
      std::string line;
      while (std::getline(input, line)) {
        size_t open_bracket_pos = line.find("<"), close_bracket_pos = line.find(">");
        std::string formatted = line.substr(open_bracket_pos + 1, close_bracket_pos - open_bracket_pos - 1);
        size_t comma_pos = formatted.find(",");

        std::istringstream stream(formatted.substr(0, comma_pos));
        K key;
        stream >> key;
        stream.clear();

        stream.str(formatted.substr(comma_pos + 1));
        V value;
        getline(stream, value);
        stream.clear();

        insert(new Item<K, V>(key, value));
      }
    } else {
      K key;
      V value;
      while (input >> key >> value) insert(new Item<K, V>(key, value));
    }
  }

  ~Hash_Table() {
    for (auto& list : ht) {
      for (auto& item : list) delete item;
    }
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

  void print(std::string title = "Hash table", std::ostream& out = std::cout) {
    out << title << std::endl;
    for (int i = 0; i < size; i++) {
      out << "Index: " << i;

      if (ht[i].empty())
        out << " -> empty bucket" << std::endl;
      else {
        for (auto& item : ht[i]) {
          out << " -> [key: " << item->get_key() << " - value: " << item->get_value() << "]";
        }
        out << std::endl;
      }
    }
    out << std::endl;
  }
};

#endif  // HASH_TABLE_HPP