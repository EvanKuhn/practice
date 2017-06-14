#include "sort_algo_runner.h"
#include "utils.h"
#include <iostream>
#include <cassert>

using namespace std;

SortAlgoRunner::~SortAlgoRunner() {
  for(size_t i = 0; i < m_algos.size(); ++i) {
    delete m_algos[i];
  }
}

void SortAlgoRunner::add(SortAlgo* algo) {
  assert(algo != NULL);
  m_algos.push_back(algo);
}

void SortAlgoRunner::run() {
  for(size_t i = 0; i < m_algos.size(); ++i) {
    _run_algo(*m_algos[i]);
  }
  _print_statistics();
}

int SortAlgoRunner::num_algos_run() const {
  return m_num_algos_run;
}

int SortAlgoRunner::num_succeeded() const {
  return m_num_succeeded;
}

int SortAlgoRunner::num_failed() const {
  return m_num_algos_run - m_num_succeeded;
}

void SortAlgoRunner::_run_algo(SortAlgo& algo) {
  cout << algo.name() << endl;
  m_num_algos_run++;

  // Construct a vector of random values
  vector<int> items;
  Utils::fill_vector_randomly(items, 0, 100, 20);

  // Print the array before sorting
  cout << "- Unsorted: ";
  Utils::print_vector_horizontal(items);
  cout << endl;

  // Sort the array
  algo.sort(items);

  // Verify that sorting was successful
  const bool success = Utils::array_is_sorted(items);
  if(success) m_num_succeeded++;

  // Print the sorted array
  cout << "- Sorted:   ";
  Utils::print_vector_horizontal(items);
  cout << "  " << (success ? "(OK)" : "(FAILED)") << endl;
  cout << endl;
}

void SortAlgoRunner::_print_statistics() const {
  cout << num_algos_run() << " sorting algorithms run, "
       << num_succeeded() << " succeeded, "
       << num_failed()    << " failed"
       << endl;
}
