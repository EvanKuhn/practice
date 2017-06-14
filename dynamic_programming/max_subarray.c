// http://www.geeksforgeeks.org/largest-sum-contiguous-subarray/

// MAX SUBARRAY
// ------------
// Find the sum of contiguous subarray within a one-dimensional array of
// numbers which has the largest sum.

#include "common.h"

// Find the max subarray sum
int max_subarray_sum(int* arr, unsigned int len)
{
  if (len == 0)
    return 0;

  int cur_sum   = 0;  // Current subarray sum
  int cur_start = 0;  // Current subarray start index
  int cur_end   = 0;  // Current subarray end index

  int max_sum   = 0;  // Max subarray sum
  int max_start = 0;  // Max subarray start index
  int max_end   = 0;  // Max subarray end index

  for (int i=0; i<len; i++) {
    cur_sum += arr[i];
    cur_end = i;

    // If the current sum is negative, reset
    if (cur_sum < 0) {
      cur_sum = 0;
      cur_start = i + 1;
    }
    // Else if the current sum is the largest we've seen, save it
    else if (cur_sum > max_sum) {
      max_sum = cur_sum;
      max_start = cur_start;
      max_end = cur_end;
    }
  }
  return max_sum;
}

int main()
{
  int a[] = {-2, -3, 4, -1, -2, 1, 5, -3};
  int n = sizeof(a)/sizeof(a[0]);
  int max_sum = max_subarray_sum(a, n);
  print_array(a, n);
  printf("Maximum subarray sum is %d (expect: 7)\n", max_sum);
  return 0;
}
