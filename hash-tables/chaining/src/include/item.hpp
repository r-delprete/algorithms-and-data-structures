#ifndef ITEM_HPP
#define ITEM_HPP

template <typename K, typename V>
class Item {
private:
  K key;
  V value;

public:
  Item(K key, V value) : key(key), value(value) {}

  K get_key() { return key; }
  V get_value() { return value; }

  void set_key(K new_key) { key = new_key; }
  void set_value(V new_value) { value = new_value; }
};

#endif  // ITEM_HPP