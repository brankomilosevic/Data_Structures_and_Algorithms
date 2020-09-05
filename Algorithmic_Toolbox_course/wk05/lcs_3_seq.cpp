#include <iostream>
#include <vector>

/*
Problem Description
Task. Given three sequences 𝐴 = (𝑎1, 𝑎2, . . . , 𝑎𝑛), 𝐵 = (𝑏1, 𝑏2, . . . , 𝑏𝑚), and 𝐶 = (𝑐1, 𝑐2, . . . , 𝑐𝑙), find the
length of their longest common subsequence, i.e., the largest non-negative integer 𝑝 such that there
exist indices 1 ≤ 𝑖1 < 𝑖2 < · · · < 𝑖𝑝 ≤ 𝑛, 1 ≤ 𝑗1 < 𝑗2 < · · · < 𝑗𝑝 ≤ 𝑚, 1 ≤ 𝑘1 < 𝑘2 < · · · < 𝑘𝑝 ≤ 𝑙 such
that 𝑎𝑖1 = 𝑏𝑗1 = 𝑐𝑘1 , . . . , 𝑎𝑖𝑝 = 𝑏𝑗𝑝 = 𝑐𝑘𝑝
Input Format. First line: 𝑛. Second line: 𝑎1, 𝑎2, . . . , 𝑎𝑛. Third line: 𝑚. Fourth line: 𝑏1, 𝑏2, . . . , 𝑏𝑚. Fifth line:
𝑙. Sixth line: 𝑐1, 𝑐2, . . . , 𝑐𝑙.
Constraints. 1 ≤ 𝑛, 𝑚, 𝑙 ≤ 100; −109 < 𝑎𝑖, 𝑏𝑖, 𝑐𝑖 < 109.
Output Format. Output 𝑝.
*/

// Branko Milosevic 2020-09-02
// Coursera Algorithmic Toolbox wk05-05

using std::vector;

int lcs3(vector<int> &a, vector<int> &b, vector<int> &c)
{
  //write your code here

    int a_size = a.size();
    int b_size = a.size();
    int c_size = c.size();

	vector<vector<vector<int>>> lcs(a_size + 1, vector<vector<int>>(b_size + 1, vector<int>(c_size + 1)));

    for (int i = 0; i <= a_size; i++)
    {
        for (int j = 0; j <= b_size; j++)
        {
			for (int k = 0; k <= c_size; k++)
			{
				if (i == 0 || j == 0 || k == 0)
                    lcs[i][j][k] = 0;
                else if (a[i - 1] == b[j - 1] && a[i - 1] == c[k - 1])
					lcs[i][j][k] = lcs[i - 1][j - 1][k - 1] + 1;
				else
					lcs[i][j][k] = std::max(std::max(lcs[i - 1][j][k], lcs[i][j - 1][k]), lcs[i][j][k - 1]);
			}
		}

	}

	return lcs[a_size][b_size][c_size];
}

int main() {
  size_t an;
  std::cin >> an;
  vector<int> a(an);
  for (size_t i = 0; i < an; i++) {
    std::cin >> a[i];
  }
  size_t bn;
  std::cin >> bn;
  vector<int> b(bn);
  for (size_t i = 0; i < bn; i++) {
    std::cin >> b[i];
  }
  size_t cn;
  std::cin >> cn;
  vector<int> c(cn);
  for (size_t i = 0; i < cn; i++) {
    std::cin >> c[i];
  }
  std::cout << lcs3(a, b, c) << std::endl;
}
