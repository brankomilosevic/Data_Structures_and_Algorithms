#include <iostream>
#include <vector>

/*
Problem Description
Task. Given 𝑛 gold bars, find the maximum weight of gold that fits into a bag of capacity 𝑊.
Input Format. The first line of the input contains the capacity 𝑊 of a knapsack and the number 𝑛 of bars
of gold. The next line contains 𝑛 integers 𝑤0,𝑤1, . . . ,𝑤𝑛−1 defining the weights of the bars of gold.
Constraints. 1 ≤ 𝑊 ≤ 104; 1 ≤ 𝑛 ≤ 300; 0 ≤ 𝑤0, . . . ,𝑤𝑛−1 ≤ 105.
Output Format. Output the maximum weight of gold that fits into a knapsack of capacity 𝑊.
*/

// Branko Milosevic 2020-09-03
// Coursera Algorithmic Toolbox wk06-01

using std::vector;

int optimal_weight(int W, const vector<int> &w) {
  //write your code here
  vector<vector<int>> value(w.size() + 1, vector<int>(W + 1, 0));

  for (int i = 1; i <= w.size(); i++)
  {
    for (int j = 1; j <= W; j++)
    {
      value[i][j] = value[i - 1][j];
      if (w[i - 1] <= j)
      {
        int val = value[i - 1][j - w[i - 1]] + w[i - 1];
        if (value[i][j] < val)
        {
          value[i][j] = val;
        }
      }
    }
  }
  return value[w.size()][W];
}

int main() {
  int n, W;
  std::cin >> W >> n;
  vector<int> w(n);
  for (int i = 0; i < n; i++) {
    std::cin >> w[i];
  }
  std::cout << optimal_weight(W, w) << '\n';
}
