#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "item.hpp"

enum HashFunction { linear, quadratic, double_hash };

struct LoadFromFileInfo {
  std::ifstream input;
  std::string key_value_delim;
  std::string pre_key_char;
  std::string post_value_char;

  LoadFromFileInfo(std::string input_filename, std::string key_value_delim = " ", std::string pre_key_char = "<",
                   std::string post_value_char = ">")
      : key_value_delim(key_value_delim), pre_key_char(pre_key_char), post_value_char(post_value_char) {
    input = std::ifstream(input_filename);
  }

  ~LoadFromFileInfo() { input.close(); }
};

template <typename K, typename V>
class HashTable {
private:
  std::vector<Item<K, V>*> data;
  int size;
  HashFunction fn;

  int h(K key, int index) {
    switch (fn) {
      case HashFunction::quadratic:
        return (key + index * int(std::pow(index, 2))) % size;
      case HashFunction::double_hash: {
        int hash1 = key % size;
        int hash2 = 1 + (key % (size - 1));
        return (hash1 + index * hash2) % size;
      }
      default:
        return (key + index) % size;
    }
  }

  std::string fn_to_string(HashFunction fn) {
    return fn == HashFunction::double_hash ? "DOUBLE HASHING" : fn == HashFunction::quadratic ? "QUADRATIC" : "LINEAR";
  }

public:
  HashTable(int size, HashFunction fn = HashFunction::linear) : size(size), fn(fn) { data.resize(size, nullptr); }

  HashTable(int size, LoadFromFileInfo* file_info, HashFunction fn = HashFunction::linear) : size(size), fn(fn) {
    data.resize(size, nullptr);
    load_from_file(file_info);
  }

  void load_from_file(LoadFromFileInfo* file_info) {
    std::string line;
    while (getline(file_info->input, line)) {
      std::string formatted = line;

      if (!file_info->pre_key_char.empty()) {
        size_t start = line.find(file_info->pre_key_char);
        if (start != std::string::npos) formatted = line.substr(start + file_info->pre_key_char.length());
      }

      if (!file_info->post_value_char.empty()) {
        size_t end = formatted.find(file_info->post_value_char);
        if (end != std::string::npos) formatted = formatted.substr(0, end);
      }

      std::size_t delim_pos = formatted.find(file_info->key_value_delim);

      std::string key_str = formatted.substr(0, delim_pos);
      std::string value_str = formatted.substr(delim_pos + file_info->key_value_delim.length());

      std::istringstream key_stream(key_str);
      K key;
      key_stream >> key;

      V value;
      std::istringstream value_stream(value_str);
      getline(value_stream, value);

      insert(new Item<K, V>(key, value));
    }
  }

  ~HashTable() {
    for (auto& item : data) delete item;
  }

  void set_hash_function(HashFunction fn) {
    if (this->fn == fn) return;
    std::cout << "Changing hash function from " << fn_to_string(this->fn) << " to " << fn_to_string(fn) << std::endl;
    this->fn = fn;
  }

  void insert(Item<K, V>* item) {
    for (int i = 0; i < size; i++) {
      int index = h(item->get_key(), i);

      if (!data[index]) {
        data[index] = item;
        return;
      }
    }

    std::cerr << "Overflow" << std::endl;
    return;
  }

  Item<K, V>* search(K key) {
    for (int i = 0; i < size; i++) {
      int index = h(key, i);

      if (!data[index]) {
        std::cerr << "Key " << key << " not found at position " << index << std::endl;
        return nullptr;
      }

      if (data[index]->get_key() == key) {
        std::cout << "Found key " << key << " at position " << index << std::endl;
        return data[index];
      }
    }

    std::cerr << "Key " << key << " not found" << std::endl;
    return nullptr;
  }

  void delete_item(K key) {
    for (int i = 0; i < size; i++) {
      int index = h(key, i);

      Item<K, V>* item = search(key);

      if (item && data[index]->get_key() == item->get_key()) {
        data[index] = nullptr;
        std::cout << "Deleted item [Key: " << item->get_key() << " - Value: " << item->get_value() << "]" << std::endl;
        return;
      }
    }

    std::cerr << "Cannot delete item with key " << key << std::endl;
    return;
  }

  void print(std::string message = "Hash table\n", std::ostream& out = std::cout) {
    out << message;
    for (int i = 0; i < size; i++) {
      out << "Index " << i;

      if (data[i])
        out << " => [Key: " << data[i]->get_key() << " - Value: " << data[i]->get_value() << "]" << std::endl;
      else
        out << " => empty" << std::endl;
    }
    out << std::endl;
  }
};