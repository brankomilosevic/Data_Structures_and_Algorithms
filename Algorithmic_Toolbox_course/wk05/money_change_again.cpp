#include <iostream>

/*
Problem Description
Input Format. Integer money.
Output Format. The minimum number of coins with denominations 1, 3, 4 that changes money.
Constraints. 1 ≤ money ≤ 103.
*/

// Branko Milosevic 2020-09-02
// Coursera Algoritmic Toolbox wk05-01

int coinList[] = {1, 3, 4};

int get_change(int m)
{
  int coins[m + 1];

  if (m == 0) return 0;

  coins[0] = 0;

  for (int i = 1; i <= m; i++) coins[i] = 2147483647;

  for (int i = 1; i <= m; i++)
  {
    for (int j = 0; j < 3; j++)
      if (coinList[j] <= i)
      {
        int tempCoins = coins[i - coinList[j]];
        if ((tempCoins != 2147483647) && (tempCoins + 1 < coins[i]))
          coins[i] = tempCoins + 1;
      }
   }
   return coins[m];
}


int main() {
  int m;
  std::cin >> m;
  std::cout << get_change(m) << '\n';
}
