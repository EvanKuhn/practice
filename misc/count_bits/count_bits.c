// Given an array of 10,000 16-bit integers, count the total number of bits
// that are set to 1.
//
// From Quora article: https://goo.gl/CMVcEP
//
// COMPILE WITH:  gcc --std=c99 count_bits.c -o count_bits

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define NUM_16BIT_VALUES 65536 // 2^16
#define NUM_RAND_VALUES 10000

uint8_t  bits_per_number[NUM_16BIT_VALUES] = {0};
uint16_t random_values[NUM_RAND_VALUES] = {0};

// Count the number of bits set to 1 in a 16-bit integer
uint8_t count_bits(uint16_t x) {
  uint8_t count = 0;
  if (x & 0x0001) ++count;
  if (x & 0x0002) ++count;
  if (x & 0x0004) ++count;
  if (x & 0x0008) ++count;
  if (x & 0x0010) ++count;
  if (x & 0x0020) ++count;
  if (x & 0x0040) ++count;
  if (x & 0x0080) ++count;
  if (x & 0x0100) ++count;
  if (x & 0x0200) ++count;
  if (x & 0x0400) ++count;
  if (x & 0x0800) ++count;
  if (x & 0x1000) ++count;
  if (x & 0x2000) ++count;
  if (x & 0x4000) ++count;
  if (x & 0x8000) ++count;
  return count;
}

// Populate the lookup table from 16-bit integer to number of bits set to 1
void populate_lookup_table() {
  for(int i=0; i<NUM_16BIT_VALUES; ++i) {
    bits_per_number[i] = count_bits((uint16_t)i);
  }
}

// Populate an array of 10k random 16-bit values
void populate_random_values() {
  sranddev();
  for (int i=0; i<NUM_RAND_VALUES; ++i) {
    random_values[i] = (uint16_t)(rand() % NUM_16BIT_VALUES);
  }
}

// Count all of the bits set to 1 in the array of 10k random values
void get_total_bit_count() {
  uint64_t count = 0;
  for(int i=0; i<NUM_RAND_VALUES; ++i) {
    count += count_bits(random_values[i]);
  }
  printf("Found %llu bits in %d 16-bit integers\n", count, NUM_RAND_VALUES);
}

int main(int argc, char** argv) {
  printf("populating lookup table\n");
  populate_lookup_table();

  printf("populating 10k random values\n");
  populate_random_values();

  printf("counting bits\n");
  get_total_bit_count();

  return 0;
}
