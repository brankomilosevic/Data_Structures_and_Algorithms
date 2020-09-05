#include <iostream>
#include <vector>
#include <algorithm>

/*
Problem Description
Task. Given an integer 𝑛, compute the minimum number of operations needed to obtain the number 𝑛
starting from the number 1.
Input Format. The input consists of a single integer 1 ≤ 𝑛 ≤ 106.
Output Format. In the first line, output the minimum number 𝑘 of operations needed to get 𝑛 from 1.
In the second line output a sequence of intermediate numbers. That is, the second line should contain
positive integers 𝑎0, 𝑎2, . . . , 𝑎𝑘−1 such that 𝑎0 = 1, 𝑎𝑘−1 = 𝑛 and for all 0 ≤ 𝑖 < 𝑘 − 1, 𝑎𝑖+1 is equal to
either 𝑎𝑖 + 1, 2𝑎𝑖, or 3𝑎𝑖. If there are many such sequences, output any one of them.
*/

// Branko Milosevic 2020-09-02
// Coursera Algorithic Toolbox wk05-02

using std::vector;
using std::min;

vector<int> naive_sequence(int n) {
  std::vector<int> sequence;
  while (n >= 1)
  {
    sequence.push_back(n);
    if (n % 3 == 0) n /= 3;
    else if (n % 2 == 0) n /= 2;
    else n = n - 1;
  }

  reverse(sequence.begin(), sequence.end());
  return sequence;
}

vector<int> optimal_sequence(int n)
{
    vector<int> sequence;
    vector<int> arr(n+1);

    for(int i = 1; i< arr.size(); i++)
    {
      arr[i] = arr[i-1] + 1;
      if (i%2 == 0) arr[i] = min(1 + arr[i/2], arr[i]);
      if (i%3 == 0) arr[i] = min(1 + arr[i/3], arr[i]);
    }

    int i = n;

    while (i > 1)
    {
      sequence.push_back(i);
      if      (arr[i-1] == arr[i]-1)               i = i - 1;
      else if (i%2 == 0 && (arr[i/2] == arr[i]-1)) i = i / 2;
      else if (i%3 == 0 && (arr[i/3] == arr[i]-1)) i = i / 3;
    }

    sequence.push_back(1);
    reverse(sequence.begin(), sequence.end());
    return sequence;
}

int main() {
  int n;
  std::cin >> n;

  vector<int> sequence = optimal_sequence(n);

  std::cout << sequence.size() - 1 << std::endl;
  for (size_t i = 0; i < sequence.size(); ++i) {
    std::cout << sequence[i] << " ";
  }
}
