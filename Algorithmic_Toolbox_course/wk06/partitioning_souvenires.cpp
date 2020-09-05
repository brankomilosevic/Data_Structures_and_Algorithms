#include <iostream>
#include <vector>
#include <algorithm>

/*
Problem Description
Input Format. The first line contains an integer 𝑛. The second line contains integers 𝑣1, 𝑣2, . . . , 𝑣𝑛 separated
by spaces.
Constraints. 1 ≤ 𝑛 ≤ 20, 1 ≤ 𝑣𝑖 ≤ 30 for all 𝑖.
Output Format. Output 1, if it possible to partition 𝑣1, 𝑣2, . . . , 𝑣𝑛 into three subsets with equal sums, and
0 otherwise.
*/

// Branko Milosevic 2020-09-03
// Coursera Algorithmic Toolbox wk06-01

using std::vector;

struct bucket
{
    int currentSum = 0;
    bool bucketFull = false;
    vector<int> values;
};

bool compare_f(int a, int b)
{
    return a >= b;
}

int partition3(vector<int> &A) {
  //write your code here

    constexpr int SPLIT = 3;

    int sum = 0;
    for (auto x : A) sum += x;

    if (sum % SPLIT != 0) return 0;

    int bucketSize = sum / SPLIT;
    vector<bucket> buckets(SPLIT);
    sort(A.begin(), A.end(), compare_f);

    for (int i = 0; i < A.size(); i++)
    {
        if (i > A.size() - 1) return 0;

        if (A[i] > bucketSize) return 0;

        for (int j = 0; j < buckets.size(); j++)
        {
            if (A[i] + buckets[j].currentSum == bucketSize)
            {
                buckets[j].values.push_back(A[i]);
                buckets[j].bucketFull = true;
                buckets[j].currentSum = bucketSize;
                break;
            }
            else if (A[i] + buckets[j].currentSum < bucketSize)
            {
                buckets[j].values.push_back(A[i]);
                buckets[j].currentSum += A[i];
                break;
            }
        }
    }

    for (size_t j = 0; j < buckets.size(); j++) if (!buckets[j].bucketFull) return 0;

    return 1;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> A(n);
  for (size_t i = 0; i < A.size(); ++i) {
    std::cin >> A[i];
  }
  std::cout << partition3(A) << '\n';
}
