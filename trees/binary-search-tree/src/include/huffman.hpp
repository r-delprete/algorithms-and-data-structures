#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP

#include <fstream>
#include <queue>
#include <sstream>
#include <unordered_map>
#include <vector>

#include "logger.hpp"
#include "node.hpp"

template <typename T>
class Huffman {
  std::vector<Node<T>*> nodes;
  Node<T>* root;
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

      Node<T>* node = new Node<T>(-1, left->get_frequency() + right->get_frequency(), '*', left, right);
      left->set_parent(node);
      right->set_parent(node);

      pq.push(node);
    }

    root = pq.top();
    pq.pop();
  }

  void delete_tree(Node<T>*& node) {
    if (!node) return;

    delete_tree(node->get_child((Child::left)));
    delete_tree(node->get_child((Child::right)));
    delete node;
  }

  void clear_nodes() {
    if (!nodes.empty()) {
      for (auto& node : nodes) delete node;
    }
    nodes.clear();
  }

public:
  Huffman() : root(nullptr) {}

  Huffman(std::ifstream& input) : root(nullptr) {
    load(input);
    build_tree();
    generate_codes(root);
  }

  ~Huffman() {
    delete_tree(root);
    clear_nodes();
  }

  void load(std::ifstream& input) {
    clear_nodes();
    input.clear();
    input.seekg(0, std::ios::beg);

    std::string line;
    while (std::getline(input, line)) {
      if (line.front() == '<') line = line.substr(1);
      if (line.back() == '>') line.pop_back();
      for (auto& c : line) c = c == ',' ? ' ' : c;

      std::istringstream ss(line);
      int frequency;
      char ch;

      ss >> frequency >> ch;
      nodes.push_back(new Node<T>(-1, frequency, ch));

      ss.clear();
      ss.str("");
    }
  }

  void generate_codes(Node<T>* node, std::string path = "") {
    if (!node) return;

    if (node->is_leaf()) codes[node->get_character()] = path;
    generate_codes(node->get_child(Child::left), path + "0");
    generate_codes(node->get_child(Child::right), path + "1");
  }

  void print_codes(std::ostream& out = std::cout) {
    out << "Huffman codes" << std::endl;
    for (auto& pair : codes) out << pair.first << " => " << pair.second << std::endl;
    out << std::endl;
  }

  std::string encode(std::string input) {
    std::string encoded;

    for (auto& ch : input) {
      if (codes.find(ch) != codes.end())
        encoded += codes[ch] + (ch == input.back() ? "" : " ");
      else {
        std::ostringstream ss;
        ss << "Error in encode Huffman function => " << ch << " not found in codes";
        log(ss.str(), LogLevel::ERROR);
        return "";
      }
    }

    return encoded;
  }

  void print_encode(std::string input, std::ostream& out = std::cout) {
    std::string encoded = encode(input);
    (encoded.empty() ? out << "Encoded string is empty"
                     : out << "Encoded string for input \"" << input << "\" => " << encoded);
    out << std::endl;
  }

  void print_decode(std::string encoded, std::ostream& out = std::cout) {
    std::string decoded = decode(encoded);
    (decoded.empty() ? out << "Decoded string is empty"
                     : out << "Decoded string for encoded string \"" << encoded << "\" => " << decoded);
    out << std::endl;
  }

  std::string decode(std::string encoded) {
    std::string decoded;
    Node<T>* current = root;

    for (auto& bit : encoded) {
      if (bit == '0') current = current->get_child(Child::left);
      if (bit == '1') current = current->get_child(Child::right);
      if (current->is_leaf()) {
        decoded += current->get_character();
        current = root;
      }
    }

    return decoded;
  }
};

#endif