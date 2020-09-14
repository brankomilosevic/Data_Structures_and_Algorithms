#include <iostream>

/*
Input Format. The first line contains a string s consisting of small Latin letters. The second line contains the number of queries q. Each of the next q lines specifies a query by three integers a, b, and l.
Output Format. For each query, output “Yes” if sasa+1...sa+l−1 = sbsb+1...sb+l−1 are equal, and “No” otherwise.
*/

// Branko Milosevic 2020-09-10
// Coursera Data Structures wk04-04

using namespace std;

class Solver {
	string s;
public:
	Solver(string s) : s(s) {
		// initialization, precalculation
	}
	bool ask(int a, int b, int l) {
		return s.substr(a, l) == s.substr(b, l);
	}
};

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);

	string s;
	int q;
	cin >> s >> q;
	Solver solver(s);
	for (int i = 0; i < q; i++) {
		int a, b, l;
		cin >> a >> b >> l;
		cout << (solver.ask(a, b, l) ? "Yes\n" : "No\n");
	}
}
