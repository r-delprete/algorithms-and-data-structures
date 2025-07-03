#ifndef ITEM_HPP
#define ITEM_HPP
#include <string>

template <typename K, typename V>
class Item {
private:
  K key;
  V value;

public:
  Item(K key, V value) : key(key), value(value) {}

  K get_key() { return key; }
  V get_value() { return value; }

  void set_key(K key) { this->key = this->key; }
  void set_value(V value) { this->value = value; }

  void print(std::ostream& out = std::cout) { out << "[Key: " << key << " - Value: " << value << "]"; }
};

#endif  // ITEM_HPP