#include <iostream>

// Branko Milosevic
// 2020-08-20
// Algorithmic Toolbox [University of California San Diego] - Coursera
// week 02, assignment 01-06

int fibonacci_sum_naive(long long n) {
    if (n <= 1)
        return (int) n;

    long long previous = 0;
    long long current  = 1;
    long long sum      = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
        sum += current;
    }

    return sum % 10;
}

int fibonacci_sum_fast(long long n)
{
    // The first two Fibonacci numbers
    long long f0 = 0;
    long long f1 = 1;

    // Base case
    if (n < 2) return (int) n;

    // Pisano period for % 10 is 60
    long long rem = n % 60;

    // trivial
    if (rem == 0) return 0;

    for(long long i = 2; i < rem + 3; i++)
    {
       long long f = (f0 + f1) % 60;
       f0 = f1;
       f1 = f;
    }

    long long s = f1 - 1;

    return s % 10;
}

int main() {
    long long n = 0;
    std::cin >> n;
    std::cout << fibonacci_sum_fast(n);
}
