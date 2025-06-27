#include "./include/hash_table.hpp"

using namespace std;

int main(int argc, char** argv) {
  ofstream output("output.txt");

  LoadFromFileInfo* input_exam_info = new LoadFromFileInfo("exam_input_example.txt", ",");
  LoadFromFileInfo* input_info = new LoadFromFileInfo("input.txt", " ", "", "");

  HashTable<int, string> ht_exam(15, input_exam_info);
  HashTable<int, string> ht(20, input_info);

  ht_exam.print("Exam hash table\n");
  ht_exam.print("Exam hash table\n", output);

  ht.print("Hash table\n");
  ht.print("Hash table\n", output);

  ht.search(6);
  ht_exam.search(12);

  cout << endl;
  ht_exam.delete_item(12);
  ht_exam.print("\nAfter delete\n");
  ht_exam.print("After delete\n", output);

  output.close();

  delete input_exam_info;
  delete input_info;

  return 0;
}