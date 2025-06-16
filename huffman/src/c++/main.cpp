#include "./classes/huffman.hpp"

int main(int argc, const char** argv) {
  string filename = "input.txt";
  ifstream input_file(filename);

  if (!input_file) {
    cerr << "Error opening file '" << filename << "'" << endl;
    return -1;
  }

  string text((istreambuf_iterator<char>(input_file)), istreambuf_iterator<char>());
  input_file.close();

  if (text.empty()) {
    cerr << "File is empty" << endl;
    return -2;
  }

  Node* root = build_huffman_tree(text);

  unordered_map<char, string> huffman_codes;
  generate_codes(root, "", huffman_codes);

  cout << "Huffman codes" << endl;
  for (auto& pair : huffman_codes) {
    cout << pair.first << ": " << pair.second << endl;
  }

  string encoded = encode(text, huffman_codes);
  string decoded = decode(root, encoded);

  cout << endl << "Encoded string: " << encoded << endl;
  cout << "Decoded string: " << decoded << endl;

  return 0;
}