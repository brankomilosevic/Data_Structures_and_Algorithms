#include <iostream>
#include <vector>

/*
Problem Description
Task. Given two sequences 𝐴 = (𝑎1, 𝑎2, . . . , 𝑎𝑛) and 𝐵 = (𝑏1, 𝑏2, . . . , 𝑏𝑚), find the length of their longest
common subsequence, i.e., the largest non-negative integer 𝑝 such that there exist indices 1 ≤ 𝑖1 <
𝑖2 < · · · < 𝑖𝑝 ≤ 𝑛 and 1 ≤ 𝑗1 < 𝑗2 < · · · < 𝑗𝑝 ≤ 𝑚, such that 𝑎𝑖1 = 𝑏𝑗1 , . . . , 𝑎𝑖𝑝 = 𝑏𝑗𝑝 .
Input Format. First line: 𝑛. Second line: 𝑎1, 𝑎2, . . . , 𝑎𝑛. Third line: 𝑚. Fourth line: 𝑏1, 𝑏2, . . . , 𝑏𝑚.
Constraints. 1 ≤ 𝑛,𝑚 ≤ 100; −109 < 𝑎𝑖, 𝑏𝑖 < 109.
Output Format. Output 𝑝.
*/

// Branko Milosevic 2020-09-02
// Coursera Algorithic Toolbox wk05-04

using std::vector;

int lcs2(vector<int> &a, vector<int> &b)
{
    int m = a.size();
    int n = b.size();
	vector<vector<int>> lcs(m + 1, vector<int>(n + 1));

	for (int i = 0; i <= m; i++)
    {
        for (int j = 0; j <= n; j++)
        {
			if (i == 0 || j == 0) lcs[i][j] = 0;
			else if (a[i - 1] == b[j - 1]) lcs[i][j] = lcs[i - 1][j - 1] + 1;
            else lcs[i][j] = std::max(lcs[i - 1][j], lcs[i][j - 1]);
		}

	}

	return lcs[m][n];
}

int main() {
  size_t n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  size_t m;
  std::cin >> m;
  vector<int> b(m);
  for (size_t i = 0; i < m; i++) {
    std::cin >> b[i];
  }

  std::cout << lcs2(a, b) << std::endl;
}
