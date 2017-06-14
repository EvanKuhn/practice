// http://www.geeksforgeeks.org/dynamic-programming-set-5-edit-distance/

// EDIT DISTANCE
// -------------
// Given two strings str1 and str2 and below operations that can performed on
// str1. Find minimum number of edits (operations) required to convert ‘str1′
// into ‘str2′.
//
//   1. Insert
//   2. Remove
//   3. Replace
//
// All of the above operations are of equal cost.

#include "common.h"

// Compute the edit distance. Takes as params: the strings, their lengths,
// and the indexes of the current characters to match.
// NOTE: we only increment an index if that character has been 'taken care of',
// either by removing it, replacing it, or matching it in the other string.
int _edit_dist(char* s1, char* s2, int len1, int len2, int i1, int i2)
{

  // If we've considered all characters in either string, quit. Return the
  // number of remaining add/remove operations necessary to make the strings
  // match, which equals the number of unconsidered chars in the other string.
  if (i1 == len1)
    return len2 - i2;

  if (i2 == len2)
    return len1 - i1;

  // If current chars are the same, move to the next. No operations needed.
  if (s1[i1] == s2[i2])
    return _edit_dist(s1, s2, len1, len2, i1+1, i2+1);

  // Option 1: insert a char
  int dist1 = 1 + _edit_dist(s1, s2, len1, len2, i1, i2+1);

  // Option 2: remove a char
  int dist2 = 1 + _edit_dist(s1, s2, len1, len2, i1+1, i2);

  // Option 3: replace a char
  int dist3 = 1 + _edit_dist(s1, s2, len1, len2, i1+1, i2+1);

  // Return the smallest distance
  if (dist1 < dist2 && dist1 < dist3) return dist1;
  if (dist2 < dist1 && dist2 < dist3) return dist2;
  return dist3;
}

int edit_dist(char* s1, char* s2, int len1, int len2)
{
  return _edit_dist(s1, s2, len1, len2, 0, 0);
}

int main()
{
  char* str1 = "sunday";
  char* str2 = "saturday";

  int len1 = strlen(str1);
  int len2 = strlen(str2);

  int dist = edit_dist(str1, str2, len1, len2);

  printf("s1: %s\n", str1);
  printf("s2: %s\n", str2);
  printf("Edit distance is %d (expect 3)\n", dist);

  return 0;
}
