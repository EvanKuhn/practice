// http://www.geeksforgeeks.org/dynamic-programming-set-3-longest-increasing-subsequence/

// LONGEST INCREASING SUBSEQUENCE
// ------------------------------
// - Consider each element. Either:
//   1) Ignore the current element and find the LCS for the remainder,
//   2) OR, include the current element and find the LCS for the remainder.
// - If we include the current element, the next must be larger than it, so we
//   need to keep track of the minimum allowed value at each step.
// - Return the max of options 1 and 2, above.

#include "common.h"

// Helper function. Takes the array, array length, curr index, and min allowed value.
// Returns the length of the longest increasing subsequence.
int _lis(int* arr, int n, int i, int min)
{
  // We reached the end of the array
  if (i == n)
    return 0;

  // Option 1: skip current element
  int lis1 = _lis(arr, n, i+1, min);

  // Option 2: include current element, if possible
  int lis2 = 0;
  if (arr[i] >= min) {
    min = arr[i] + 1;
    lis2 = 1 + _lis(arr, n, i+1, min);
  }

  // Pick the largest LIS
  return max(lis1, lis2);
}

// Find the length of the longest increasing subsequence of the array
int lis(int* arr, int n)
{
  return _lis(arr, n, 0, 0);
}

int main()
{
  int arr[] = { 10, 22, 9, 33, 21, 50, 41, 60 };
  int n = sizeof(arr)/sizeof(arr[0]);
  print_array(arr, n);
  printf("Length of LIS is %d (expect: 5)\n", lis(arr, n));
  return 0;
}
