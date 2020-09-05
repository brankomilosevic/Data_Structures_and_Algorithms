#include <iostream>
// The goal is to find minimal number of coins needed to change the input value
// Coins denominations are 1, 5 and 10
//
// Branko Milosevic 2020-082-31
// Coursena Algorithmics Toolbox wk03-01

int get_change(int m) {
  //write your code here

  if ((m < 1) || (m > 1000)) return -1;

  int coins_10 = m / 10;
  int coins_5 = (m - coins_10 * 10) / 5;
  int coins_1 = m - coins_10*10 - coins_5*5;

/*
  std::cout << "10: " << coins_10 << "\n";
  std::cout << "5 : " << coins_5 << "\n";
  std::cout << "1 : " << coins_1 << "\n";
*/

  int n = coins_10 + coins_5 + coins_1;
  return n;
}

int main() {
  int m;
  std::cin >> m;
  std::cout << get_change(m) << '\n';
}
