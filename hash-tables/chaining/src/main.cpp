#include "./include/hash_table.hpp"

using namespace std;

int main(int argc, char** argv) {
  ifstream input_file("input.txt");
  ofstream output_file("output.txt");
  ifstream exam_input("exam_input_example.txt");

  Hash_Table<int, string> ht(10, input_file);
  Hash_Table<int, string> ht_exam(15, exam_input, true);

  ht.print();
  ht_exam.print("Exam hash table");
  ht.print("Hash table", output_file);
  ht_exam.print("Exam hash table", output_file);

  ht.search(6);
  ht.delete_element(12);

  cout << endl;
  ht.print("After deleting item 12");

  input_file.close();
  output_file.close();
  exam_input.close();

  return 0;
}