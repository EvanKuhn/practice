// http://www.geeksforgeeks.org/dynamic-programming-set-6-min-cost-path/

// MIN COST PATH
// -------------
// Given a cost matrix cost[][] and a position (m, n) in cost[][], write a
// function that returns cost of minimum cost path to reach (m, n) from (0, 0).
// Each cell of the matrix represents a cost to traverse through that cell.
// Total cost of a path to reach (m, n) is sum of all the costs on that path
// (including both source and destination). You can only traverse down, right
// and diagonally down-right from a given cell, i.e., from a given cell (i,j),
// cells (i+1,j), (i,j+1) and (i+1,j+1) can be traversed. You may assume that
// all costs are positive integers.

#include "common.h"

#define R 3
#define C 3

int _min_cost(int cost[R][C], int x, int y, int dest_x, int dest_y)
{
  // If we reached the largest X, increment Y and count the costs
  if (x == dest_x) {
    int sum = 0;
    for (int i=y; i<=dest_y; i++) {
      sum += cost[x][i];
    }
    return sum;
  }

  // If we reached the largest Y, increment X and count the costs
  if (y == dest_y) {
    int sum = 0;
    for (int i=x; i<=dest_x; i++) {
      sum += cost[i][y];
    }
    return sum;
  }

  // We can move either right, down, or diagonally. Pick the lowest-cost move.
  // - Note: x moves up/down, y moves left/right.
  int cost_right = cost[x][y] + _min_cost(cost, x,   y+1, dest_x, dest_y);
  int cost_down  = cost[x][y] + _min_cost(cost, x+1, y,   dest_x, dest_y);
  int cost_diag  = cost[x][y] + _min_cost(cost, x+1, y+1, dest_x, dest_y);

  // Return the lowest cost
  if (cost_right < cost_down && cost_right < cost_diag) return cost_right;
  if (cost_down < cost_right && cost_down < cost_diag) return cost_down;
  return cost_diag;
}

int min_cost(int cost[R][C], int dest_x, int dest_y)
{
  return _min_cost(cost, 0, 0, dest_x, dest_y);
}

int main()
{
  int cost[R][C] = {
    {1, 2, 3},
    {4, 8, 2},
    {1, 5, 3}
  };
  printf("min cost is %d (expect 8)\n", min_cost(cost, 2, 2));
  return 0;
}
