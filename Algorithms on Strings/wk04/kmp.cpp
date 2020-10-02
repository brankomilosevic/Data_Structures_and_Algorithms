#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

/*
Task. Find all occurrences of a pattern in a string.
Input Format. Strings Pattern and Genome.
Constraints. 1 ≤ |Pattern| ≤ 106; 1 ≤ |Genome| ≤ 106; both strings are over A, C, G, T.
Output Format. All starting positions in Genome where Pattern appears as a substring (using 0-based
indexing as usual).
*/

// Branko Milosevic 2020-09-02
// Coursera Algorithms on Graphs wk04-01

using std::cin;
using std::string;
using std::vector;

// Find all occurrences of the pattern in the text and return a
// vector with all positions in the text (starting from 0) where
// the pattern starts in the text.

vector<int> findPrefix(const string& p)
{
    vector<int> s(p.size());

    for (int j = 1, border = 0, n = p.size(); j < n; ++j)
    {
        while (border && p[j] != p[border]) border = s[border - 1];

        border = (p[j] == p[border]) ? ++border : 0;
        s[j] = border;
    }

    return s;
}

vector<int> find_pattern(const string& pattern, const string& text) {
    vector<int> result;

    string S = pattern + '$' + text;
    vector<int> s = findPrefix(S);
    for (int i = pattern.size() + 1; i < S.size(); ++i)
    {
        if (s[i] == pattern.size())
            result.push_back(i - 2 * pattern.size());
    }

    return result;
}

int main() {
  string pattern, text;
  cin >> pattern;
  cin >> text;
  vector<int> result = find_pattern(pattern, text);
  for (int i = 0; i < result.size(); ++i) {
    printf("%d ", result[i]);
  }
  printf("\n");
  return 0;
}
