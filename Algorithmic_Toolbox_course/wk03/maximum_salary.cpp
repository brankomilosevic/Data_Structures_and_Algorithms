#include <algorithm>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;

/*
Problem Description
Task. Compose the largest number out of a set of integers.
Input Format. The first line of the input contains an integer 𝑛. The second line contains integers
𝑎1, 𝑎2, . . . , 𝑎𝑛.
Constraints. 1 ≤ 𝑛 ≤ 100; 1 ≤ 𝑎𝑖 ≤ 103 for all 1 ≤ 𝑖 ≤ 𝑛.
Output Format. Output the largest number that can be composed out of 𝑎1, 𝑎2, . . . , 𝑎𝑛.
*/

// Branko Milosevic 2020-08-31
// Coursera Algorithms Toolbox wk03-07

bool compare_string(string a, string b)
{
    string tmp_a = std::string(a);
    string tmp_b = std::string(b);

    int pad = a.size() - b.size();

    if (pad > 0) for (int i = 0; i < pad; i++) tmp_b += 'A';
    if (pad < 0) for (int i = 0; i < -pad; i++) tmp_a += 'A';

/*
    std::cout << "====\n";
    std::cout << "A: [" << tmp_a << "]\n";
    std::cout << "B: [" << tmp_b << "]\n";
*/
    return tmp_a > tmp_b;
}

string largest_number(vector<string> a)
{
  //write your code here
  std::stringstream ret;

  sort(a.begin(), a.end(), compare_string);

  for (size_t i = 0; i < a.size(); i++)
    ret << a[i];

  string result;
  ret >> result;
  return result;
}

int main() {
  int n;
  std::cin >> n;
  vector<string> a(n);
  for (size_t i = 0; i < a.size(); i++) {
    std::cin >> a[i];
  }
  std::cout << largest_number(a);
}
