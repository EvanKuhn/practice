#include <iostream>
#include "sort_algos.h"
#include "sort_algo_runner.h"

using namespace std;

int main(int argc, char** argv) {
  SortAlgoRunner runner;
  runner.add(new BubbleSort);
  runner.add(new InsertionSort);
  runner.add(new MergeSort);
  runner.add(new QuickSort);
  runner.add(new HeapSort);
  runner.run();
}
