#include <iostream>
#include <vector>

// Branko Milosevic
// 2020-08-20
// Algorithmic Toolbox [University of California San Diego] - Coursera
// week 02, assignment 01-05

long long get_fibonacci_huge_naive(long long n, long long m) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
    }

    return current % m;
}

long long get_p_period(long long m)
{
    long long result = 2;
    for (long long fn2 = 1, fn1 = 2 % m, fn = 3 % m; fn1 != 1 || fn != 1; fn2 = fn1, fn1 = fn, fn = (fn1 + fn2) % m)
        result++;

    return result;
}

long long get_fib_mod (long long n, long long m)
{
    long long fn = 0, fn_1 = 1, fn_2 = 1;

    if (n == 0) return 0;

    if (n == 1 || n == 2) return 1;

    for (long long i = 2; i < n; i++)
    {
      fn = ( fn_1 % m + fn_2 % m) % m;
      fn_2 = fn_1;
      fn_1 = fn;
    }

  return fn;
}

long long get_fibonacci_huge_fast(long long n, long long m)
{
    if (m == 1) return 0;
    long long p_period = get_p_period(m);

    return get_fib_mod(n % p_period, m);
}

int main() {
    long long n, m;
    std::cin >> n >> m;
    std::cout << get_fibonacci_huge_fast(n, m) << '\n';
}
