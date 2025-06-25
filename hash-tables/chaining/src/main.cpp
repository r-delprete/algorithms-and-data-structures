#include "./include/hash_table.hpp"

using namespace std;

int main(int argc, char** argv) {
  ifstream input_file("input.txt");
  ofstream output_file("output.txt");

  Hash_Table<int, string> ht(10, input_file);

  ht.print();
  ht.print_in_file(output_file);

  ht.search(6);
  ht.delete_element(12);
  ht.print();

  return 0;
}