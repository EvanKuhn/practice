#pragma once

#include <vector>
#include "sort_algos.h"

// The SortAlgoRunner takes pointers to SortAlgo objects on the heap, runs their
// sorting algorithms, and deletes the SortAlgo objects on destruction.
class SortAlgoRunner {
public:
  ~SortAlgoRunner();

  // Add a pointer to a SortAlgo object to be run. The SortAlgoRunner object
  // will take ownership of the SortAlgo and delete it on destruction.
  void add(SortAlgo* algo);

  // Run the sorting algorithms that were added, print arrays before and after
  // sorting, verify results, and collect statistics.
  void run();

  // Statistics
  int num_algos_run() const;
  int num_succeeded() const;
  int num_failed() const;

private:
  // Helper functions
  void _run_algo(SortAlgo& algo);
  void _print_statistics() const;

  // Data members
  std::vector<SortAlgo*> m_algos;
  int m_num_algos_run;
  int m_num_succeeded;
};


/*
TODO: do I want to do a performance-test runner? Eg:

Bubble Sort
- sorting, array size: 10,   status: ok,   time: 145 ms
- sorting, array size: 100,  status: fail, time: 1048 ms
- sorting, array size: 1000, status: ok,   time: 2375 ms
*/
