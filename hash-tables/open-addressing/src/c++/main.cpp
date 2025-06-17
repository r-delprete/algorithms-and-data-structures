#include "./classes/hash_table.hpp"

using namespace std;

int main(int argc, char** argv) {
  ifstream input_file("input.txt");
  ofstream output_file("output.txt");

  Hash_Table<int, string> ht(10);
  ht.load_from_file(input_file);
  ht.print();
  ht.print_in_file(output_file);

  int search_key = 6;
  string* value = ht.find(search_key);
  value != nullptr ? cout << endl
                          << "Key " << search_key << " has " << *value << " as value" << endl
                   : cout << endl
                          << "Value for key " << search_key << " not found" << endl;

  ht.delete_element(12) ? cout << endl << "Element deleted" << endl : cout << endl << "Element not deleted" << endl;

  ht.print();

  return 0;
}