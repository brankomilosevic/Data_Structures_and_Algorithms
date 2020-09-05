#include <iostream>
#include <vector>
#include <cstdlib>

/*
Problem Description
Task. To force the given implementation of the quick sort algorithm to efficiently process sequences with
few unique elements, your goal is replace a 2-way partition with a 3-way partition. That is, your new
partition procedure should partition the array into three parts: < 𝑥 part, = 𝑥 part, and > 𝑥 part.
Input Format. The first line of the input contains an integer 𝑛. The next line contains a sequence of 𝑛
integers 𝑎0, 𝑎1, . . . , 𝑎𝑛−1.
Constraints. 1 ≤ 𝑛 ≤ 105; 1 ≤ 𝑎𝑖 ≤ 109 for all 0 ≤ 𝑖 < 𝑛.
Output Format. Output this sequence sorted in non-decreasing order.
*/

// Branko Milosevic 2020-09-01
// Coursera Algorithms Toolbox wk04-03

using std::vector;
using std::swap;
using std::pair;

int partition2(vector<int> &a, int l, int r) {
  int x = a[l];
  int j = l;
  for (int i = l + 1; i <= r; i++) {
    if (a[i] <= x) {
      j++;
      swap(a[i], a[j]);
    }
  }
  swap(a[l], a[j]);
  return j;
}


pair<int, int> partition3(vector<int> &a, int l, int r)
{

	int x = a[l], m1;
	int j = l;

	for (int i = l + 1; i <= r; i++)
    {
        if (a[i] <= x)
        {
            j++;
            swap(a[i], a[j]);
        }
	}

	swap(a[l], a[j]);
    m1 = j - 1;

	for (int i = l; i < j && m1 >= l && m1 > i;)
	{
		if (a[j] == a[i])
			swap(a[i], a[m1--]);
		else
			i++;
	}

	m1++;
	return std::make_pair(m1, j);
}

void randomized_quick_sort(vector<int> &a, int l, int r) {
/*  if (l >= r)
    return;

  int k = l + rand() % (r - l + 1);
  swap(a[l], a[k]);
  int m = partition2(a, l, r);

  randomized_quick_sort(a, l, m - 1);
  randomized_quick_sort(a, m + 1, r);
*/
	if (l >= r) return;

	int k = l + rand() % (r - l + 1);
    swap(a[l], a[k]);
    pair<int, int> m = partition3(a, l, r);

	randomized_quick_sort(a, l, m.first - 1);
    randomized_quick_sort(a, m.second + 1, r);
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cin >> a[i];
  }
  randomized_quick_sort(a, 0, a.size() - 1);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cout << a[i] << ' ';
  }
}
