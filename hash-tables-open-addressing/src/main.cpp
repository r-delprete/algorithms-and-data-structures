#include "./include/hash_table.hpp"

using namespace std;

int main(int argc, char** argv) {
  ifstream input("input.txt");
  ifstream input2("exam_input_example.txt");
  ofstream output("output.txt");

  HashTable<int, string> ht(12, input);
  ht.print();

  ht.search(6);
  ht.delete_element(12);

  input.close();
  input2.close();
  output.close();

  return 0;
}