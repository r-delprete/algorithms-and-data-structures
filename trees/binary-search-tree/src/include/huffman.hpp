#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP

#include <fstream>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "node.hpp"

template <typename T>
class Huffman {
private:
  Node<T>* root = nullptr;
  std::vector<Node<T>*> nodes;
  std::unordered_map<char, std::string> codes;

  struct Compare {
    bool operator()(Node<T>* node1, Node<T>* node2) { return node1->get_frequency() > node2->get_frequency(); }
  };

  void build_tree() {
    std::priority_queue<Node<T>*, std::vector<Node<T>*>, Compare> pq;
    for (auto& node : nodes) pq.push(node);

    while (pq.size() > 1) {
      Node<T>* left = pq.top();
      pq.pop();
      Node<T>* right = pq.top();
      pq.pop();

      Node<T>* node = new Node<T>('*', left->get_frequency() + right->get_frequency(), nullptr, left, right);
      left->set_parent(node);
      right->set_parent(node);

      pq.push(node);
    }

    root = pq.top();
    pq.pop();

    generate_codes(root);
  }

  void generate_codes(Node<T>* node, std::string path = "") {
    if (!node) return;

    if (node->is_leaf()) codes[node->get_character()] = path;
    generate_codes(node->get_left(), path + "0");
    generate_codes(node->get_right(), path + "1");
  }

  void delete_tree(Node<T>* node) {
    if (!node) return;
    delete_tree(node->get_left());
    delete_tree(node->get_right());
    delete node;
  }

public:
  Huffman() {}
  Huffman(std::ifstream& input) {
    load_from_file(input);
    build_tree();
  }

  ~Huffman() { delete_tree(root); }

  Node<T>* get_root() { return root; }

  void set_nodes(std::vector<Node<T>*> nodes) { this->nodes = nodes; }

  void load_from_file(std::ifstream& input) {
    input.clear();
    input.seekg(0, std::ios::beg);

    std::string line;
    while (std::getline(input, line)) {
      std::string formatted = line;
      if (line.front() == '<') formatted = formatted.substr(1);
      if (line.back() == '>') formatted = formatted.substr(0, line.size() - 1);

      std::size_t delim_pos = formatted.find(',');
      std::istringstream stream;
      int frequency;
      std::string character;
      if (delim_pos != std::string::npos) {
        stream.str(formatted.substr(0, delim_pos));

        stream >> frequency;
        stream.clear();

        stream.str(formatted.substr(delim_pos + 1));
        std::getline(stream, character);
      } else {
        stream.str(formatted);
        stream >> frequency >> character;
      }

      nodes.push_back(new Node<T>(character[0], frequency));
      stream.clear();
    }
  }

  std::string encode(std::string input) {
    std::string encoded;

    for (auto c : input) {
      if (codes.find(c) != codes.end())
        encoded += codes[c] + (input.back() == c ? "" : " ");
      else
        return "";
    }

    return encoded;
  }

  std::string decode(std::string encoded) {
    std::string decoded;
    Node<T>* current = root;

    for (auto bit : encoded) {
      if (bit == '0')
        current = current->get_left();
      else if (bit == '1')
        current = current->get_right();

      if (current->is_leaf()) {
        decoded += current->get_character();
        current = root;
      }
    }

    return decoded;
  }

  void print_codes(std::ostream& out = std::cout) {
    out << "Codes:" << std::endl;
    for (const auto& pair : codes) {
      out << "'" << pair.first << "' => " << pair.second << std::endl;
    }
    out << std::endl;
  }

  void print_encode(std::string input, std::ostream& out = std::cout) {
    out << "Encode => " << encode(input) << std::endl;
  }

  void print_decode(std::string encoded, std::ostream& out = std::cout) {
    out << "Decode => " << decode(encoded) << std::endl;
  }
};

#endif