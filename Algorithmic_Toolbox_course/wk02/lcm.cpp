#include <iostream>
// Branko Milosevic
// 2020-08-20
// Algorithmic Toolbox [University of California San Diego] - Coursera
// week 02, assignment 01-04

long long lcm_naive(int a, int b) {
  for (long l = 1; l <= (long long) a * b; ++l)
    if (l % a == 0 && l % b == 0)
      return l;

  return (long long) a * b;
}

int gcd_fast(int a, int b)
{
    if (b == 0) return a;

    return gcd_fast(b, a % b);
}

long long lcm_fast(int a, int b)
{
    int gcd = gcd_fast(a, b);

    int mult = a / gcd;

    return (long long) mult * b;
}

int main() {
  int a, b;
  std::cin >> a >> b;
  std::cout << lcm_fast(a, b) << std::endl;
  return 0;
}
