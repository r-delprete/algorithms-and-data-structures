#include "./include/hash_table.hpp"

using namespace std;

int main(int argc, char** argv) {
  ifstream input_file("input.txt");
  ofstream output_file("output.txt");

  Hash_Table<int, string> ht(10, input_file);

  ht.print();
  ht.print_in_file(output_file);

  int key_searched = 6;
  Item<int, string>* item = ht.search(6);

  item ? cout << endl
              << "Item with key " << key_searched << " found! Value " << item->get_value() << endl
              << endl
       : cout << endl
              << "Item with key " << key_searched << " not found";

  ht.delete_element(12);
  ht.print();

  return 0;
}