#include <iostream>
#include <vector>

/*
Problem Description
Task. The goal in this problem is to count the number of inversions of a given sequence.
Input Format. The first line contains an integer 𝑛, the next one contains a sequence of integers
𝑎0, 𝑎1, . . . , 𝑎𝑛−1.
Constraints. 1 ≤ 𝑛 ≤ 105, 1 ≤ 𝑎𝑖 ≤ 109 for all 0 ≤ 𝑖 < 𝑛.
Output Format. Output the number of inversions in the sequence.
*/

// Branko Milosevic 2020-09-01
// Coursera Algorithms Toolbox wk04-04

using std::vector;

long long my_merge(vector<int> a, vector<int> b, int left, int mid, int right);

long long get_number_of_inversions(vector<int> &a, vector<int> &b, size_t left, size_t right) {
  long long number_of_inversions = 0;

  if (right <= left + 1) return number_of_inversions;
  size_t ave = left + (right - left) / 2;
  number_of_inversions += get_number_of_inversions(a, b, left, ave);
  number_of_inversions += get_number_of_inversions(a, b, ave, right);
  //write your code here

  number_of_inversions = my_merge(a, b, left, ave + 1, right);

  return number_of_inversions;
}

long long my_merge(vector<int> a, vector<int> b, int left, int mid, int right)
{
    int i = left;
    int j = mid;
    int k = left;

    int inv_count = 0;

    while ((i <= mid - 1) && (j <= right))
    {
        if (a[i] <= a[j])
            b[k++] = a[i++];
        else
        {
            b[k++] = a[j++];
            inv_count = inv_count + (mid - i);
        }
    }

    while (i <= mid - 1)
        b[k++] = a[i++];

    while (j <= right)
        b[k++] = a[j++];

    for (i = left; i <= right; i++)
        a[i] = b[i];

    return inv_count;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); i++) {
    std::cin >> a[i];
  }
  vector<int> b(a.size());
  std::cout << get_number_of_inversions(a, b, 0, a.size()) << '\n';
}
