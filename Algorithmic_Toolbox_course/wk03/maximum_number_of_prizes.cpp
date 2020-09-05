#include <iostream>
#include <vector>

/*
Problem Description
Task. The goal of this problem is to represent a given positive integer 𝑛 as a sum of as many pairwise
distinct positive integers as possible. That is, to find the maximum 𝑘 such that 𝑛 can be written as
𝑎1 + 𝑎2 + · · · + 𝑎𝑘 where 𝑎1, . . . , 𝑎𝑘 are positive integers and 𝑎𝑖 ̸= 𝑎𝑗 for all 1 ≤ 𝑖 < 𝑗 ≤ 𝑘.
Input Format. The input consists of a single integer 𝑛.
Constraints. 1 ≤ 𝑛 ≤ 109.
Output Format. In the first line, output the maximum number 𝑘 such that 𝑛 can be represented as a sum
of 𝑘 pairwise distinct positive integers. In the second line, output 𝑘 pairwise distinct positive integers
that sum up to 𝑛 (if there are many such representations, output any of them).
*/

// Branko Milosevic 2020-08-31
// Coursera Algorithms Toolbox wk03-06

using std::vector;

vector<int> optimal_summands(int n) {
    vector<int> summands;
    //write your code here

    for (int k = n, l = 1; k > 0; l++)
    {
        if (k <= 2 * l)
        {
            summands.push_back(k);
            k -= k;
        }
        else
        {
            summands.push_back(l);
            k -= l;
        }
    }
    return summands;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> summands = optimal_summands(n);
  std::cout << summands.size() << '\n';
  for (size_t i = 0; i < summands.size(); ++i) {
    std::cout << summands[i] << ' ';
  }
}
