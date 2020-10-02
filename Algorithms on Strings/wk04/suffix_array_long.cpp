#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <utility>

/*
Task. Construct the suffix array of a string.
Input Format. A string Text ending with a “$” symbol.
Constraints. 1 ≤ |Text| ≤ 2 · 105; except for the last symbol, Text contains symbols A, C, G, T only.
Output Format. SuffixArray(Text), that is, the list of starting positions of sorted suffixes separated by
spaces.
*/

// Branko Milosevic 2020-10-02
// Coursera Algorithms on Graphs wk04-02

using std::cin;
using std::cout;
using std::endl;
using std::make_pair;
using std::pair;
using std::string;
using std::vector;

// Build suffix array of the string text and
// return a vector result of the same length as the text
// such that the value result[i] is the index (0-based)
// in text where the i-th lexicographically smallest
// suffix of text starts.

constexpr int ALPHABET_SIZE = 5;

inline int getIndex(char c)
{
    switch (c)
    {
    case 'A': return 1;
    case 'C': return 2;
    case 'G': return 3;
    case 'T': return 4;
    default : return 0;
    }
}

std::vector<int> sortDoubled(const std::string& s, int L, const std::vector<int>& order, const std::vector<int>& cclass)
{
    std::vector<int> count(s.size());
    std::vector<int> newOrder(s.size());

    for (int i = 0; i < s.size(); ++i) ++count[cclass[i]];

    for (int j = 1; j < s.size(); ++j) count[j] += count[j - 1];

    for (int i = s.size() - 1; i >= 0; --i)
    {
        int start = (order[i] - L + s.size()) % s.size();
        int cl = cclass[start];
        newOrder[--count[cl]] = start;
    }

    return newOrder;
}

std::vector<int> computeCharacterClasses(const std::string& s, const std::vector<int>& order)
{
    std::vector<int> cclass(s.size());

    for (int i = 1; i < s.size(); ++i)
    {
        if (s[order[i]] != s[order[i - 1]])
            cclass[order[i]] = cclass[order[i - 1]] + 1;
        else
            cclass[order[i]] = cclass[order[i - 1]];
    }

    return cclass;
}

std::vector<int> countingCharactersSort(const std::string& s)
{
    std::vector<int> order(s.size());
    std::vector<int> count(ALPHABET_SIZE);

    for (auto& c : s) ++count[getIndex(c)];

    for (int j = 1; j < ALPHABET_SIZE; ++j) count[j] += count[j - 1];

    for (int i = s.size() - 1; i >= 0; --i)
    {
        char c = s[i];
        count[getIndex(c)] -= 1;
        order[count[getIndex(c)]] = i;
    }
    return order;
}

std::vector<int> updateClasses(const std::vector<int>& newOrder, const std::vector<int>& cclass, int L)
{
    const int n = newOrder.size();
    std::vector<int> newCclass(n);

    for (int i = 1; i < n; ++i)
    {
        int cur = newOrder[i], prev = newOrder[i - 1];
        int mid = cur + L, midPrev = (prev + L) % n;

        if (cclass[cur] != cclass[prev] || cclass[mid] != cclass[midPrev])
            newCclass[cur] = newCclass[prev] + 1;
        else
            newCclass[cur] = newCclass[prev];
    }
    return std::move(newCclass);
}
vector<int> BuildSuffixArray(const string& text) {
    std::vector<int> order = countingCharactersSort(text);
    std::vector<int> cclass = computeCharacterClasses(text, order);
    int L = 1;

    while (L < text.size())
    {
        order = sortDoubled(text, L, order, cclass);
        cclass = updateClasses(order, cclass, L);
        L *= 2;
    }
    return std::move(order);
}

int main() {
  string text;
  cin >> text;
  vector<int> suffix_array = BuildSuffixArray(text);
  for (int i = 0; i < suffix_array.size(); ++i) {
    cout << suffix_array[i] << ' ';
  }
  cout << endl;
  return 0;
}
