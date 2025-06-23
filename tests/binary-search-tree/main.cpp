#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Node {
private:
  int key, frequency;
  char character;
  Node *left, *right, *parent;

public:
  Node(int key = 0, char character = '*', int frequency = 0)
      : key(key), character(character), left(nullptr), right(nullptr), parent(nullptr) {}

  int get_key() { return key; }
  int get_frequency() { return frequency; }
  char get_character() { return character; }
  Node* get_left() { return left; }
  Node* get_parent() { return parent; }
  Node* get_right() { return right; }

  void set_key(int key) { this->key = key; }
  void set_frequency(int frequency) { this->frequency = frequency; }
  void set_character(char character) { this->character = character; }
  void set_left(Node* left) { this->left = left; }
  void set_right(Node* right) { this->right = right; }
  void set_parent(Node* parent) { this->parent = parent; }
};

class BinarySearchTree {
private:
  Node* bst_root;      // BST root
  Node* huffman_root;  // Huffman tree root
  vector<Node*> nodes;
  unordered_map<char, string> huffman_table;

  Node* insert_recursive(Node* start, Node* node) {
    if (!start) return node;

    if (node->get_key() < start->get_key()) {
      Node* left = insert_recursive(start->get_left(), node);
      start->set_left(left);
      left->set_parent(start);
    } else {
      Node* right = insert_recursive(start->get_right(), node);
      start->set_right(right);
      right->set_parent(start);
    }

    return start;
  }

  struct Compare {
    bool operator()(Node* node1, Node* node2) { return node1->get_frequency() > node2->get_frequency(); }
  };

  Node* huffman_tree() {
    priority_queue<Node*, vector<Node*>, Compare> pq;
    for (auto& node : nodes) pq.push(node);

    while (pq.size() > 1) {
      Node* z = new Node();
      z->set_left(pq.top());
      pq.pop();
      z->set_right(pq.top());
      pq.pop();
      z->set_frequency(z->get_left()->get_frequency() + z->get_right()->get_frequency());
      pq.push(z);
    }

    return pq.top();
  }

  void build_huffman_table(Node* node, string path = "") {
    if (!node) return;
    if (!node->get_left() && !node->get_right()) huffman_table[node->get_character()] = path;

    build_huffman_table(node->get_left(), path + "0");
    build_huffman_table(node->get_right(), path + "1");
  }

public:
  BinarySearchTree(ifstream& input_file) {
    int key;
    char character;
    bst_root = nullptr;

    while (input_file >> key >> character) {
      // Insert into BST
      Node* node_bst = new Node(key, character, key);
      bst_root = insert_recursive(bst_root, node_bst);

      // Separate node for Huffman
      Node* node_huffman = new Node(0, character, key);
      node_huffman->set_frequency(key);  // freq = key
      nodes.push_back(node_huffman);
    }

    huffman_root = huffman_tree();
    build_huffman_table(huffman_root, "");
  }

  Node* get_root() { return bst_root; }

  void insert(Node* node) { bst_root = insert_recursive(bst_root, node); }

  void inorder_visit(Node* node) {
    if (!node) return;

    inorder_visit(node->get_left());
    cout << "Node: " << node->get_key() << endl;
    inorder_visit(node->get_right());
  }

  void inorder_visit(Node* node, ofstream& output_file) {
    if (!node) return;

    inorder_visit(node->get_left(), output_file);
    output_file << "Node: " << node->get_key() << endl;
    inorder_visit(node->get_right(), output_file);
  }

  Node* search(Node* node, int key) {
    if (!node || node->get_key() == key) return node;
    if (key < node->get_key())
      return search(node->get_left(), key);
    else
      return search(node->get_right(), key);
  }

  Node* tree_maximum(Node* node) {
    while (node->get_right()) node = node->get_right();
    return node;
  }

  Node* tree_minimum(Node* node) {
    while (node->get_left()) node = node->get_left();
    return node;
  }

  Node* successor(Node* node) {
    if (!node) return nullptr;
    if (node->get_right()) return tree_minimum(node->get_right());
    Node* y = node->get_parent();
    while (y && node == y->get_right()) {
      node = y;
      y = y->get_parent();
    }
    return y;
  }

  Node* predecessor(Node* node) {
    if (!node) return nullptr;
    if (node->get_left()) return tree_maximum(node->get_left());
    Node* y = node->get_parent();
    while (y && node == y->get_left()) {
      node = y;
      y = y->get_parent();
    }
    return y;
  }

  void print_successor(Node* node) {
    if (!node) {
      cerr << "Invalid node" << endl;
      return;
    }
    Node* succ = successor(node);
    succ ? cout << "Successor of node " << node->get_key() << ": " << succ->get_key() << endl
         : cout << "No successor for node: " << node->get_key() << endl;
  }

  void print_successor(Node* node, ofstream& output_file) {
    if (!node) {
      cerr << "Invalid node" << endl;
      return;
    }
    Node* succ = successor(node);
    succ ? output_file << "Successor of node " << node->get_key() << ": " << succ->get_key() << endl
         : output_file << "No successor for node: " << node->get_key() << endl;
  }

  void print_predecessor(Node* node) {
    if (!node) {
      cerr << "Invalid node" << endl;
      return;
    }
    Node* pred = predecessor(node);
    pred ? cout << "Predecessor of node " << node->get_key() << ": " << pred->get_key() << endl
         : cout << "No predecessor for node: " << node->get_key() << endl;
  }

  void print_predecessor(Node* node, ofstream& output_file) {
    if (!node) {
      cerr << "Invalid node" << endl;
      return;
    }
    Node* pred = predecessor(node);
    pred ? output_file << "Predecessor of node " << node->get_key() << ": " << pred->get_key() << endl
         : output_file << "No predecessor for node: " << node->get_key() << endl;
  }

  string encode(string input) {
    string encoded;
    for (auto c : input) {
      if (huffman_table.find(c) != huffman_table.end())
        encoded += " " + huffman_table[c];
      else {
        cerr << "Character -" << c << "- not found in Huffman table";
        return "";
      }
    }
    return encoded;
  }

  string decode(string encoded) {
    string decoded;
    Node* current = huffman_root;

    for (auto bit : encoded) {
      if (bit == '0')
        current = current->get_left();
      else if (bit == '1')
        current = current->get_right();
      if (!current->get_left() && !current->get_right()) {
        decoded += current->get_character();
        current = huffman_root;
      }
    }

    return decoded;
  }

  void print_huffman_table() {
    cout << "Huffman Table:" << endl;
    for (const auto& pair : huffman_table) {
      cout << "'" << pair.first << "' => " << pair.second << endl;
    }
  }
};

int main() {
  ifstream input_file("input.txt");
  ofstream output_file("output.txt");

  BinarySearchTree bst(input_file);
  cout << "Tree root: " << bst.get_root()->get_key() << endl << endl;

  // cout << "Inorder visit" << endl;
  // bst.inorder_visit(bst.get_root());
  output_file << "Inorder visit" << endl;
  bst.inorder_visit(bst.get_root(), output_file);

  Node* node = bst.search(bst.get_root(), 5);

  cout << endl;
  bst.print_predecessor(node);
  bst.print_successor(node);

  cout << endl;
  bst.print_huffman_table();
  string to_encode = "ABDE";
  cout << endl << "String: " << to_encode << " -> Encoding: " << bst.encode(to_encode);

  input_file.close();
  output_file.close();

  return 0;
}