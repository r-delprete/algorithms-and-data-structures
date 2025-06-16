#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP

#include <fstream>
#include <queue>
#include <unordered_map>

#include "./node.hpp"

Node* build_huffman_tree(string& text) {
  unordered_map<char, int> frequencies;
  for (char ch : text) {
    frequencies[ch]++;
  }

  priority_queue<Node, vector<Node>, CompareNodes> pq;

  for (auto& pair : frequencies) {
    pq.push(Node(pair.first, pair.second));
  }

  while (pq.size() > 1) {
    Node* left = new Node(pq.top());
    pq.pop();

    Node* right = new Node(pq.top());
    pq.pop();

    Node* node = new Node('\0', left->get_frequency() + right->get_frequency(), left, right);

    pq.push(*node);
  }

  Node* huffman_tree_root = new Node(pq.top());
  pq.pop();

  return huffman_tree_root;
}

string encode(string& text, unordered_map<char, string>& huffman_codes) {
  string encoded;

  for (char ch : text) {
    encoded += huffman_codes[ch];
  }

  ofstream encoded_file("encoded.txt");
  if (!encoded_file) {
    cerr << "Error writing encode" << endl;
  }
  encoded_file << encoded;

  return encoded;
}

string decode(Node* root, string& encoded) {
  string decoded;
  Node* current = root;

  for (char s : encoded) {
    if (s == '0') {
      current = current->get_left();
    } else {
      current = current->get_right();
    }

    if (current->get_right() == nullptr && current->get_left() == nullptr) {
      decoded += current->get_symbol();
      current = root;
    }
  }

  ofstream decoded_file("decoded.txt");
  if (!decoded_file) {
    cerr << "Error writing decode" << endl;
  }
  decoded_file << decoded;

  return decoded;
}

void generate_codes(Node* root, string code, unordered_map<char, string>& huffman_codes) {
  if (!root) return;

  if (!root->get_left() && !root->get_right()) {
    huffman_codes[root->get_symbol()] = code;
  }

  generate_codes(root->get_left(), code + "0", huffman_codes);
  generate_codes(root->get_right(), code + "1", huffman_codes);
}

#endif  // HUFFMAN_HPP