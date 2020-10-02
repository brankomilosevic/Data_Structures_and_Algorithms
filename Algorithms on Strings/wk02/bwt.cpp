#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

/*
Task. Construct the Burrows–Wheeler transform of a string.
Input Format. A string Text ending with a “$” symbol.
Constraints. 1 ≤ |Text| ≤ 1 000; except for the last symbol, Text contains symbols A, C, G, T only.
Output Format. BWT(Text).
*/

// Branko Milosevic 2020-10-02
// Coursera Algorithms on Strings wk02-01

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

string BWT(const string& text) {

    string result = "";

    vector<string> rotations(text.size());

    for (int i = 0; i < text.size(); ++i)
        rotations[i] = text.substr(text.size() - i, string::npos) + text.substr(0, text.size() - i);

    std::sort(rotations.begin(), rotations.end());

    for (auto& s : rotations)
        result += s.back();

    return result;
}

int main() {
  string text;
  cin >> text;
  cout << BWT(text) << endl;
  return 0;
}
