#pragma once

#include <vector>
#include <string>

//==============================================================================
// Base class
//==============================================================================

class SortAlgo {
public:
  SortAlgo(const std::string& name) : m_name(name) { }
  virtual ~SortAlgo() { }
  const std::string& name() const { return m_name; }
  virtual void sort(std::vector<int>& v) = 0;

private:
  std::string m_name;
};

//==============================================================================
// Concrete sort classes
//==============================================================================

class BubbleSort : public SortAlgo {
public:
  BubbleSort() : SortAlgo("Bubble Sort") { }
  virtual void sort(std::vector<int>& v);
};

class InsertionSort : public SortAlgo {
public:
  InsertionSort() : SortAlgo("Insertion Sort") { }
  virtual void sort(std::vector<int>& v);
};

class SelectionSort : public SortAlgo {
public:
  SelectionSort() : SortAlgo("Selection Sort") { }
  virtual void sort(std::vector<int>& v);
};

class MergeSort : public SortAlgo {
public:
  MergeSort() : SortAlgo("Merge Sort") { }
  virtual void sort(std::vector<int>& v);
private:
  void merge_sort(std::vector<int>& v, std::vector<int>& temp,
    size_t begin, size_t end);
  void merge(std::vector<int>& v, std::vector<int>& temp,
    size_t begin, size_t mid, size_t end);
};

class QuickSort : public SortAlgo {
public:
  QuickSort() : SortAlgo("Quicksort") { }
  virtual void sort(std::vector<int>& v);
private:
  size_t partition(std::vector<int>& v, size_t begin, size_t end);
  void quicksort(std::vector<int>& v, size_t begin, size_t end);
};

class HeapSort : public SortAlgo {
public:
  HeapSort() : SortAlgo("Heap Sort") { }
  virtual void sort(std::vector<int>& v);
};
