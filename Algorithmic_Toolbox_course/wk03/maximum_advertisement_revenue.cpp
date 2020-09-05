#include <algorithm>
#include <iostream>
#include <vector>

/*
Problem Description
Task. Given two sequences 𝑎1, 𝑎2, . . . , 𝑎𝑛 (𝑎𝑖 is the profit per click of the 𝑖-th ad) and 𝑏1, 𝑏2, . . . , 𝑏𝑛 (𝑏𝑖 is
the average number of clicks per day of the 𝑖-th slot), we need to partition them into 𝑛 pairs (𝑎𝑖, 𝑏𝑗)
such that the sum of their products is maximized.
Input Format. The first line contains an integer 𝑛, the second one contains a sequence of integers
𝑎1, 𝑎2, . . . , 𝑎𝑛, the third one contains a sequence of integers 𝑏1, 𝑏2, . . . , 𝑏𝑛.
Constraints. 1 ≤ 𝑛 ≤ 103; −105 ≤ 𝑎𝑖, 𝑏𝑖 ≤ 105 for all 1 ≤ 𝑖 ≤ 𝑛.
Output Format. Output the maximum value of
Σ︀𝑛
𝑖=1
𝑎𝑖𝑐𝑖, where 𝑐1, 𝑐2, . . . , 𝑐𝑛 is a permutation of
𝑏1, 𝑏2, . . . , 𝑏𝑛.
*/

// Branko Milosevic 2020-08-31
// Coursera Algorithms wk03-04

using std::vector;

long long max_dot_product(vector<int> a, vector<int> b) {
  // write your code here
  long long result = 0;

  int n = a.size();
  if (n < 1) return -1;

  vector <int> a_temp (n);
  vector <int> b_temp (n);

  for (int i = 0; i < n; i++)
  {
    a_temp[i] = a[i];
    b_temp[i] = b[i];
  }

  sort(a_temp.begin(), a_temp.end());
  sort(b_temp.begin(), b_temp.end());

  for (int i = 0; i < n; i++)
    result += a_temp[i] * b_temp[i];

  return result;
}

int main() {
  size_t n;
  std::cin >> n;
  vector<int> a(n), b(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> a[i];
  }
  for (size_t i = 0; i < n; i++) {
    std::cin >> b[i];
  }
  std::cout << max_dot_product(a, b) << std::endl;
}
