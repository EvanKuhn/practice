//==============================================================================
// Test the Heap class.
//
// g++ -o heap_test -I ../common heap_test.cpp
//==============================================================================
#include <iostream>
#include "heap.h"
#include "utils.h"

using namespace std;

void test_insert_and_extract() {
  cout << "Heap insert and extract:" << endl;

  // Generate random values
  vector<int> inputs;
  Utils::fill_vector_randomly(inputs, 0, 99, 50);

  // Add random values to a heap
  Heap<int> h;
  for(int i=0; i<inputs.size(); i++) {
    h.insert(inputs[i]);
  }

  // Extract the values
  vector<int> outputs;
  while(!h.empty()) {
    outputs.push_back(h.extract());
  }

  // Print em
  const char* status = (Utils::array_is_sorted(outputs) ? "(OK)" : "(FAIL)");
  cout << "- inserted:  " << inputs << endl;
  cout << "- extracted: " << outputs << "  " << status << endl;
}

void test_heapsort() {
  cout << "Heapsort:" << endl;

  // Generate random values
  vector<int> values;
  Utils::fill_vector_randomly(values, 0, 99, 50);
  cout << "- unsorted: " << values << endl;

  // Sort!
  heapsort(values);

  // Print the sorted values
  const char* status = (Utils::array_is_sorted(values) ? "(OK)" : "(FAIL)");
  cout << "- sorted:   " << values << "  " << status << endl;
}

int main(int argc, char** argv) {
  test_insert_and_extract();
  test_heapsort();
}
