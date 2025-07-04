#include "./include/hash_table.hpp"

using namespace std;

int main(int argc, char** argv) {
  ifstream input("input.txt");
  ofstream output("output.txt");
  ifstream exam_input("exam_input_example.txt");

  HashTable<int, string> ht(10, input);
  HashTable<int, string> ht_exam(15, exam_input);

  ht.print();
  ht_exam.print("Exam hash table");
  ht.print("Hash table", output);
  ht_exam.print("Exam hash table", output);

  ht.search(6);
  ht.delete_item(12);

  cout << endl;
  ht.print("Base hash table after deleting item 12");

  input.close();
  output.close();
  exam_input.close();

  return 0;
}