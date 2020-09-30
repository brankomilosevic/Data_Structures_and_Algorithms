#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cassert>
#include <vector>
#include <cmath>

/*
Task.
Given n points on a plane and an integer k, compute the largest possible value of d such that the given points can be partitioned
into k non-empty subsets in such a way that the distance between any two points from different subsets is at least d.

Input Format.
The first line contains the number n of points. Each of the following n lines defines a point (xi,yi).
The last line contains the number k of clusters.

Constraints.
2 ≤ k ≤ n ≤ 200; −103 ≤ xi,yi ≤ 103 are integers. All points are pairwise different.

Output Format.
Output the largest value of d. The absolute value of the difference between the answer of your program and the optimal value should be at most 10−6.
To ensure this, output your answer with at least seven digits after the decimal point
(otherwise your answer, while being computed correctly, can turn out to be wrong because of rounding issues).
*/

// Branko Milosevic 2020-09-28
// Coursera Algorithms on Graphs wk05-02

using std::vector;
using std::pair;

struct Node
{
  int start, end;
  double dis;
  Node(int x, int y, double d) : start(x), end(y), dis(d){};
  bool operator<(const Node &a) const { return dis < a.dis; }
};

int Find(int x, vector<int> &parent)
{
  if (x != parent[x]) parent[x] = Find(parent[x], parent);
  return parent[x];
}

void Union(int x, int y, vector<int> &parent)
{
  int left = Find(x, parent);
  int right = Find(y, parent);
  if (left != right) parent[right] = left;
}

double clustering(vector<int> x, vector<int> y, int k) {
  //write your code here
  int num = 0;
  vector<int> parent(x.size());
  vector<Node> q;

  for (int i = 0; i < x.size(); i++) parent[i] = i;

  for (int i = 0; i < x.size(); i++)
  {
    for (int j = i + 1; j < x.size(); j++)
    {
      double dis = sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
      q.push_back(Node(i, j, dis));
    }
  }

  std::sort(q.begin(), q.end());

  for (int i = 0; i < q.size(); i++)
  {
    Node v = q[i];
    if (Find(v.start, parent) != Find(v.end, parent))
    {
      if (num == x.size() - k) return v.dis;
      num++;
      Union(v.start, v.end, parent);
    }
  }
}

int main() {
  size_t n;
  int k;
  std::cin >> n;
  vector<int> x(n), y(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> x[i] >> y[i];
  }
  std::cin >> k;
  std::cout << std::setprecision(10) << clustering(x, y, k) << std::endl;
}
