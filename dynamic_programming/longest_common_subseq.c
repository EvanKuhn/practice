// http://www.geeksforgeeks.org/dynamic-programming-set-4-longest-common-subsequence/

// LONGEST COMMON SUBSEQUENCE
// --------------------------
// Given two sequences, find the length of longest subsequence present in both
// of them. A subsequence is a sequence that appears in the same relative order,
// but not necessarily contiguous

#include "common.h"

// Recursive function to find the LCS of two sequences. The function will
// compare sequences starting from the end.
int _lcs(char* a, int ai, char* b, int bi)
{
  // Stop if we consider an entire subsequence
  if (ai < 0 || bi < 0)
    return 0;

  // If last chars match, LCS = 1 + LCS of rest of sequences
  if (a[ai] == b[bi])
    return 1 + _lcs(a, ai-1, b, bi-1);

  // LCS is the max of:
  // - LCS of A[0..ai], B[0..bi-1]
  // - LCS of A[0..ai-1], B[0..bi]
  int lcs_1 = _lcs(a, ai, b, bi-1);
  int lcs_2 = _lcs(a, ai-1, b, bi);
  return max(lcs_1, lcs_2);
}

int longest_common_subseq(char* a, int alen, char* b, int blen)
{
  return _lcs(a, alen-1, b, blen-1);
}

int main(int argc, char** argv)
{
  char a[] = "AGGTAB";
  char b[] = "GXTXAYB";

  int alen = strlen(a);
  int blen = strlen(b);

  printf("s1: %s\n", a);
  printf("s2: %s\n", b);
  printf("Length of LCS is %d (expect: 4)\n", longest_common_subseq(a, alen, b, blen));

  return 0;
}
