#include "./include/hash_table.hpp"

using namespace std;

int main(int argc, char** argv) {
  ifstream input_file("input.txt");
  ofstream output_file("output.txt");

  Hash_Table<int, string> ht(input_file, 10);

  ht.print();
  ht.print(output_file);

  ht.search(6);
  ht.delete_element(12);
  ht.print();

  input_file.close();
  output_file.close();

  return 0;
}