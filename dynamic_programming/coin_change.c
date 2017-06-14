// http://www.geeksforgeeks.org/dynamic-programming-set-7-coin-change/

// COIN CHANGE
// -----------
// Given a value N, if we want to make change for N cents, and we have infinite
// supply of each of S = { S1, S2, .. , Sm} valued coins, how many ways can we
// make the change? The order of coins doesn’t matter.

#include "common.h"

int count_bottom_up(int* coins, int ncoins, int target)
{
  int table[target+1][ncoins];

  // Set all answers for target=0 to 1
  for (int c=0; c<ncoins; c++)
    table[0][c] = 1;

  // For each target value
  for (int t=1; t<=target; t++) {
    // For each coin
    for (int c=0; c<ncoins; c++) {
      // The number of ways to reach the current target value using the current
      // coin equal the answer for curr_target - curr_coin
      int diff = t - coins[c];
      int ways_with_coin = (diff >= 0 ? table[diff][c] : 0);

      // Calculate the number of ways without the current coin. Look back at the
      // answer for the previous coin.
      int ways_without_coin = (c > 0 ? table[t][c-1] : 0);

      // Save number of ways to reach 't' cents with and without the current coin
      table[t][c] = ways_with_coin + ways_without_coin;
    }
  }
  return table[target][ncoins-1];
}


int count_recursive(int* coins, int ncoins, int target)
{
  // There is no way to reach a negative value
  if (target < 0)
    return 0;

  // There is one way to reach zero cents
  if (target == 0)
    return 1;

  // There's no way to reach a value with no coins
  if (ncoins <= 0)
    return 0;

  // Sum the number of ways WITH and WITHOUT using the last coin
  int coin = coins[ncoins-1];
  int ways_with_coin = count_recursive(coins, ncoins, target-coin);
  int ways_without_coin = count_recursive(coins, ncoins-1, target);
  return ways_with_coin + ways_without_coin;
}


int main()
{
  int coins[] = {2, 5, 3, 6};
  int ncoins = sizeof(coins)/sizeof(coins[0]);
  int target = 10;

  printf("coins: ");
  print_array(coins, ncoins);
  printf("ways to reach %d cents:\n", target);
  printf("- bottom-up answer: %d\n", count_bottom_up(coins, ncoins, target));
  printf("- recursive answer: %d\n", count_recursive(coins, ncoins, target));
  return 0;
}
