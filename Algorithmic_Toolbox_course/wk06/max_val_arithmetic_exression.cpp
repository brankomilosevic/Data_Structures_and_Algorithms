#include <iostream>
#include <cassert>
#include <string>
#include <vector>

#define L_LONG_MAX 9223372036854775807
#define L_LONG_MIN -9223372036854775807

/*
Problem Description
Task. Find the maximum value of an arithmetic expression by specifying the order of applying its arithmetic
operations using additional parentheses.
Input Format. The only line of the input contains a string 𝑠 of length 2𝑛 + 1 for some 𝑛, with symbols
𝑠0, 𝑠1, . . . , 𝑠2𝑛. Each symbol at an even position of 𝑠 is a digit (that is, an integer from 0 to 9) while
each symbol at an odd position is one of three operations from {+,-,*}.
Constraints. 0 ≤ 𝑛 ≤ 14 (hence the string contains at most 29 symbols).
Output Format. Output the maximum possible value of the given arithmetic expression among different
orders of applying arithmetic operations.
*/

// Branko Milosevic 2020-09-03
// Coursera Algorithmic Toolbox wk06-03

using std::vector;
using std::string;
using std::max;
using std::min;

long long eval(long long a, long long b, char op)
{
  if      (op == '*') return a * b;
  else if (op == '+') return a + b;
  else if (op == '-') return a - b;
  else                assert(0);

}

long long get_maximum_value(const string &exp) {
    int n = (int)exp.size();
    int num_op = (n + 1) / 2;

    long long min_i[num_op][num_op];
    long long max_i[num_op][num_op];

    for (int i = 0; i < num_op; i++) for (int j = 0; j < num_op; j++) { min_i[i][j] = 0; max_i[i][j] = 0;}

    for (int i = 0; i < num_op; i++)
    {
        min_i[i][i] = stoll(exp.substr(2 * i, 1));
        max_i[i][i] = stoll(exp.substr(2 * i, 1));
    }

    for (int s = 0; s < num_op - 1; s++)
    {
        for (int i = 0; i < num_op - s - 1; i++)
        {
            int j = i + s + 1;
            long long min_value = L_LONG_MAX;
            long long max_value = L_LONG_MIN;

            for (int k = i; k < j; k++) {
                long long a = eval(min_i[i][k], min_i[k + 1][j], exp[2 * k + 1]);
                long long b = eval(min_i[i][k], max_i[k + 1][j], exp[2 * k + 1]);
                long long c = eval(max_i[i][k], min_i[k + 1][j], exp[2 * k + 1]);
                long long d = eval(max_i[i][k], max_i[k + 1][j], exp[2 * k + 1]);

                min_value = min(min_value, min(a, min(b, min(c, d))));
                max_value = max(max_value, max(a, max(b, max(c, d))));

            }
            min_i[i][j] = min_value;
            max_i[i][j] = max_value;
        }
    }

    return max_i[0][num_op - 1];
}

int main() {
  string s;
  std::cin >> s;
  std::cout << get_maximum_value(s) << '\n';
}

