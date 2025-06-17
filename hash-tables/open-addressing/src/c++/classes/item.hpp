#ifndef ITEM_HPP
#define ITEM_HPP

template <typename K, typename V>
struct Item {
  K key;
  V value;

  Item(K key, V value) : key(key), value(value) {}
};

#endif  // ITEM_HPP