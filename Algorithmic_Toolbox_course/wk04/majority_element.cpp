#include <algorithm>
#include <iostream>
#include <vector>
#include <unordered_map>

/*
Problem Description
Task. The goal in this code problem is to check whether an input sequence contains a majority element.
Input Format. The first line contains an integer 𝑛, the next one contains a sequence of 𝑛 non-negative
integers 𝑎0, 𝑎1, . . . , 𝑎𝑛−1.
Constraints. 1 ≤ 𝑛 ≤ 105; 0 ≤ 𝑎𝑖 ≤ 109 for all 0 ≤ 𝑖 < 𝑛.
Output Format. Output 1 if the sequence contains an element that appears strictly more than 𝑛/2 times,
and 0 otherwise.
*/

// Branko Milosevic 2020-09-01
// Coursera Algorithms Toolbox wk04-02

using std::vector;
using std::unordered_map;

int get_majority_element(vector<int> &a, int left, int right) {
  if (left == right) return -1;
  if (left + 1 == right) return a[left];
  //write your code here

    unordered_map<int, int> tmp_map;
    for (int i = 0; i < (right - left); i++)
        tmp_map[a[i]]++;

    for (auto x : tmp_map)
      if (x.second > (right - left) / 2)
          return 1;
    return -1;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cin >> a[i];
  }
  std::cout << (get_majority_element(a, 0, a.size()) != -1) << '\n';
}
