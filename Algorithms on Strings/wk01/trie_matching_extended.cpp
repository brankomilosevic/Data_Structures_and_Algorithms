#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

/*
Input Format.
The first line of the input contains a string Text, the second line contains an integer 𝑛,
each of the following 𝑛 lines contains a pattern from Patterns = {𝑝1, . . . , 𝑝𝑛}.

Constraints.
1 ≤ |Text| ≤ 10 000; 1 ≤ 𝑛 ≤ 5 000; 1 ≤ |𝑝𝑖| ≤ 100 for all 1 ≤ 𝑖 ≤ 𝑛; all strings contain only
symbols A, C, G, T; it can be the case that 𝑝𝑖 is a prefix of 𝑝𝑗 for some 𝑖, 𝑗.

Output Format. All starting positions in Text where a string from Patterns appears as a substring in
increasing order (assuming that Text is a 0-based array of symbols). If more than one pattern
appears starting at position 𝑖, output 𝑖 once.
*/

// Branko Milosevic 2020-09-30
// Coursera Algorithms on Strings wk01-03

using namespace std;

int const Letters =    4;
int const NA      =   -1;

struct Node
{
	int next [Letters];
	bool patternEnd;

	Node ()
	{
		fill (next, next + Letters, NA);
		patternEnd = false;
	}
};

int letterToIndex (char letter)
{
	switch (letter)
	{
		case 'A': return 0; break;
		case 'C': return 1; break;
		case 'G': return 2; break;
		case 'T': return 3; break;
		default: assert (false); return -1;
	}
}

void build_trie (const vector <string>& patterns, vector<Node> &t)
{
	for (int i = 0; i < patterns.size(); i++)
	{
		int x = 0;
		for (int j = 0; j < patterns[i].size(); j++)
		{
			int index = letterToIndex(patterns[i][j]);
			if (x >= t.size())
			{
				t.resize(x + 1);
			}
			if (t[x].next[index] != -1)
			{
				x = t[x].next[index];
			}
			else
			{
				t[x].next[index] = t.size();
				x = t[x].next[index];
				t.resize(x + 1);
			}
		}
		t[x].patternEnd = true;
	}

}

vector <int> solve (string text, int n, vector <string> patterns)
{
	vector <int> result;

	vector<Node> t;
	build_trie(patterns, t);

	for (int i = 0; i < text.size(); i++)
	{
		int index = letterToIndex(text[i]);
		int x = 0;
		if (t[x].next[index] != -1)
		{
			bool found = true;
			for (int j = i; !t[x].patternEnd ; j++)
			{
				if (j >= text.size())
				{
					found = false;
					break;
				}
				index = letterToIndex(text[j]);
				if (t[x].next[index] != -1)
				{
					x = t[x].next[index];
				}
				else
				{
					found = false;
					break;
				}
			}
			if (found)
			{
				result.push_back(i);
			}
		}
	}

	return result;
}

int main (void)
{
	string text;
	std::cin >> text;

	int n;
	std::cin >> n;

	vector <string> patterns (n);
	for (int i = 0; i < n; i++)
	{
		std::cin >> patterns[i];
	}

	vector <int> ans;
	ans = solve (text, n, patterns);

	for (int i = 0; i < (int) ans.size (); i++)
	{
		std::cout << ans[i];
		if (i + 1 < (int) ans.size ())
		{
			std::cout << " ";
		}
		else
		{
			std::cout << endl;
		}
	}

	return 0;
}
