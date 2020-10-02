#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

/*
Task. Reconstruct a string from its Burrows–Wheeler transform.
Input Format. A string Transform with a single “$” sign.
Constraints. 1 ≤ |Transform| ≤ 1 000 000; except for the last symbol, Text contains symbols A, C, G, T
only.
Output Format. The string Text such that BWT(Text) = Transform. (There exists a unique such string.)
*/

// Branko Milosevic 2020-10-02
// Coursera Algorithms on Graphs wk02-02

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

using Symbols = std::vector<int>;

inline int getIndexInSymbols(char s)
{
    switch (s)
    {
    case 'A': return 0;
    case 'C': return 1;
    case 'G': return 2;
    case 'T': return 3;
    default : return 4;
    }
}

inline int getIndexInRrightColumn(Symbols& sm, char s, int cnt)
{
    switch (s)
    {
    case 'A': return cnt;
    case 'C': return sm[0] + cnt;
    case 'G': return sm[1] + sm[0] + cnt;
    case 'T': return sm[2] + sm[1] + sm[0] + cnt;
    default : return 0;
    }
}

string InverseBWT(const string& bwt) {
    if (bwt.size() == 1) return bwt;

    Symbols symbols(5, 0);
    std::vector<int> indexes(bwt.size(), 0);

    auto* iptr = &indexes[0];
    auto* sptr = bwt.c_str();
    while (*sptr)
        *iptr++ = ++symbols[getIndexInSymbols(*sptr++)];

    const auto rsize = bwt.size();
    char r[rsize + 1];
    r[rsize] = '\0';

    char s = bwt[0];
    int j = indexes[0];
    int k = bwt.size() - 1;

    r[k--] = '$';
    r[k--] = s;

    for (int i = 2, iters = bwt.size() - i; iters--; ++i)
    {
        int indexInRrightColumn = getIndexInRrightColumn(symbols, s, j);
        r[k--] = bwt[indexInRrightColumn];
        j = indexes[indexInRrightColumn];
        s = r[k + 1];
    }

    return r;
}

int main() {
  string bwt;
  cin >> bwt;
  cout << InverseBWT(bwt) << endl;
  return 0;
}
