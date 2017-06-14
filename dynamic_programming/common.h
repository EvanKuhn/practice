#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int a, int b)
{
  return a > b ? a : b;
}

void print_array(int* arr, int len) {
  for (int i=0; i<len; i++) {
    printf("%d", arr[i]);
    if (i < len-1)
      printf(", ");
  }
  printf("\n");
}
