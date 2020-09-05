#include <iostream>
// Branko Milosevic
// 2020-08-20
// Algorithmic Toolbox [University of California San Diego] - Coursera
// week 02, assignment 01-08

int fibonacci_sum_squares_naive(long long n) {
    if (n <= 1)
        return (int) n;

    long long previous = 0;
    long long current  = 1;
    long long sum      = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
        sum += current * current;
    }

    return sum % 10;
}

int getFibonacciLastDigit(long long n)
{
    if (n < 2) return (int) n;

    int prev = 0;
    int curr = 1;

    for (long i = 2; i < n+1; i++)
    {
        int next = (prev + curr) % 10;
        prev = curr;
        curr = next;
    }

    return curr % 10;

}

int fibonacci_sum_squares_fast(long long n)
{
    int vert = getFibonacciLastDigit(n % 60);
    int horiz = getFibonacciLastDigit((n + 1) % 60);
    int squares = vert  * horiz;

    return squares % 10;

}

int main() {
    long long n = 0;
    std::cin >> n;
    std::cout << fibonacci_sum_squares_fast(n);
}
