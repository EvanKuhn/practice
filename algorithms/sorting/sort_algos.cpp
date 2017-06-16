#include "sort_algos.h"
#include "heap.h"
#include <iostream>

using namespace std;

//==============================================================================
// BubbleSort
//==============================================================================

void BubbleSort::sort(vector<int>& v) {
  const size_t size = v.size();
  for(size_t end = size - 1; end > 0; --end) {
    for(size_t i = 0; i < end; ++i) {
      if(v[i] > v[i+1]) {
        swap(v[i], v[i+1]);
      }
    }
  }
}

//==============================================================================
// InsertionSort
//==============================================================================

// Insertion sort works by maintaining a sorted and unsorted portion of the
// array. Initially, the unsorted portion is empty, so the first element is
// added. Afterwards, we consider the next element and swap it toward the front
// until it is in the proper place. Continue until all elements are sorted.
void InsertionSort::sort(vector<int>& v) {
  for(size_t i = 1; i < v.size(); ++i) {
    for(size_t s = i; s > 0 && v[s] < v[s-1]; --s) {
      std::swap(v[s], v[s-1]);
    }
  }
}

//==============================================================================
// SelectionSort
//==============================================================================

// Selection sort works by: selecting the smallest value in the unsorted portion
// of the sub-array, swapping it to the end of the sorted portion, and iterating
// until all elements are sorted.
void SelectionSort::sort(vector<int>& v) {
  const size_t size = v.size();
  for (size_t start = 0; start < size; start++) {
    // Find the lowest value in range [start,size)
    size_t lowest = start;
    for (size_t i = start; i < size; i++) {
      if (v[i] < v[lowest]) {
        lowest = i;
      }
    }
    // Swap v[lowest] with v[start]
    if (lowest != start) {
      std::swap(v[start], v[lowest]);
    }
  }
}

//==============================================================================
// MergeSort
//==============================================================================

// Basic mergesort algo: split the array in two, sort both halves, then merge
// the halves back into a sorted whole. Note: merging requires a temp array.
void MergeSort::sort(vector<int>& v) {
  vector<int> temp(v.size());
  merge_sort(v, temp, 0, v.size());
}

void MergeSort::merge_sort(vector<int>& v, vector<int>& temp,
  size_t begin, size_t end)
{
  // If the length of the (sub)array is less than two, return
  const size_t len = end - begin;
  if(len < 2) return;

  // Partition the array in two, sort both halves, and merge
  const size_t mid = begin + (len / 2);
  merge_sort(v, temp, begin, mid);
  merge_sort(v, temp, mid, end);
  merge(v, temp, begin, mid, end);
}

void MergeSort::merge(vector<int>& in, vector<int>& temp, size_t begin,
  size_t mid, size_t end)
{
  size_t i = begin;  // Index into 1st sub-array
  size_t j = mid;    // Index into 2nd sub-array
  size_t t = begin;  // Index into temp array

  // While both iterators are valid
  while(i < mid && j < end) {
    temp[t++] = (in[i] < in[j] ? in[i++] : in[j++]);
  }

  // Copy the rest of i, or j, to temp
  while(i < mid) { temp[t++] = in[i++]; }
  while(j < end) { temp[t++] = in[j++]; }

  // Copy temp back to the original array
  for(i = begin; i < end; i++) {
    in[i] = temp[i];
  }
}

//==============================================================================
// QuickSort
//==============================================================================

void QuickSort::sort(vector<int>& v) {
  quicksort(v, 0, v.size());
}

// Partition works by identifying a pivot and moving all lesser elements to the
// pivot's left, and greater elements to the pivot's right. This function
// returns the index of the pivot.
//
// Elements will be ordered as: [elems <= pivot, pivot, elems > pivot]
size_t QuickSort::partition(vector<int>& v, size_t begin, size_t end) {
  int pivot = v[begin]; // Choose first element as pivot
  size_t i = begin + 1; // Index to first array elem (after pivot)
  size_t j = end - 1;   // Index to last array elem

  // Move the front index forward and rear index backward until we find elements
  // to swap, then swap them.
  while(i < j) {
    if(v[i] <= pivot) {
      ++i;
    }
    else if(v[j] > pivot) {
      --j;
    }
    else {
      std::swap(v[i], v[j]);
    }
  }

  // After swapping, we can assume:
  // - i == j
  // - v[i] could be less, equal, or greater than the pivot
  // - v[i-1] <= pivot
  // Here we figure out which element (at index `p`) to swap with the pivot,
  // swap it, and return `p`:
  size_t p = i;
  if(v[p] > pivot) {
    --p;
  }
  if(p != begin) {
    std::swap(v[begin], v[p]);
  }
  return p;
}

// Recursive quicksort function:
// 1. Partition the array, identifying a pivot and two unsorted sub-arrays.
// 2. Make recursive calls to sort the left and right sides, excluding the pivot.
void QuickSort::quicksort(vector<int>& v, size_t begin, size_t end) {
  // Stop if no elements to sort
  const size_t len = end - begin;
  if(len < 2) return;

  // Do the actual quicksort
  size_t pivot = partition(v, begin, end);
  quicksort(v, begin, pivot);
  quicksort(v, pivot + 1, end);
}

//==============================================================================
// HeapSort
//==============================================================================

void HeapSort::sort(vector<int>& v) {
  heapsort(v); // See heap.h/cpp for the code
}
