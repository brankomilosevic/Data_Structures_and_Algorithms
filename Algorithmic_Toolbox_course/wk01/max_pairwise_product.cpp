#include <iostream>
#include <vector>
#include <algorithm>

// Branko Milosevic
// 2020-08-20
// Algorithmic Toolbox [University of California San Diego] - Coursera
// week 01, assignment 02

long long MaxPairwiseProduct(const std::vector<int>& numbers) {
    int n = (int) numbers.size();

/*
// original - unoptimized
    for (int first = 0; first < n; ++first) {
        for (int second = first + 1; second < n; ++second) {
            max_product = std::max(max_product,
                numbers[first] * numbers[second]);
        }
    }
*/
    int first_max = 0;
    int second_max = 0;
    int first_index = -1;
    for (int i = 0; i < n; ++i) if (first_max < numbers[i])  { first_max = numbers[i]; first_index = i ;}
    for (int i = 0; i < n; ++i) if (second_max < numbers[i]) { if (first_index != i) second_max = numbers[i];}

    return (long long) first_max * second_max;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> numbers(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> numbers[i];
    }

    std::cout << MaxPairwiseProduct(numbers) << "\n";
    return 0;
}
