#include <iostream>

// Branko Milosevic
// 2020-08-20
// Algorithmic Toolbox [University of California San Diego] - Coursera
// week 02, assignment 01-07

long long get_fibonacci_partial_sum_naive(long long from, long long to) {
    long long sum = 0;

    long long current = 0;
    long long next  = 1;

    for (long long i = 0; i <= to; ++i) {
        if (i >= from) {
            sum += current;
        }

        long long new_current = next;
        next = next + current;
        current = new_current;
    }

    return sum % 10;
}

long long get_fib_fast(long long n)
{
    // The first two Fibonacci numbers
    long long f0 = 0;
    long long f1 = 1;

    // Base case
    if (n < 2) return n;

    // Pisano period for % 10 is 60
    long long rem = n % 60;

    if (rem == 0) return 0;

    for(long long i = 2; i < rem + 3; i++)
    {
       long long f = (f0 + f1) % 60;
       f0 = f1;
       f1 = f;
    }

    long long s = f1 - 1;

    return s;
}

long long get_fibonacci_partial_sum_fast(long long from, long long to)
{
    return ((get_fib_fast(to) - get_fib_fast(from-1)) % 10 + 10) % 10;
}

int main() {
    long long from, to;
    std::cin >> from >> to;
    std::cout << get_fibonacci_partial_sum_fast(from, to) << '\n';
}
