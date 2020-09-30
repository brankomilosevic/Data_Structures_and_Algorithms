#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

/*
Task.
Given n points on a plane, connect them with segments of minimum total length such that there is a path between any two points.
Recall that the length of a segment with endpoints (x1,y1) and (x2,y2) is equal to√︀(x1 −x2)2 + (y1 −y2)2.

Input Format.
The first line contains the number n of points. Each of the following n lines defines a point (xi,yi).

Constraints.
1 ≤ n ≤ 200; −103 ≤ xi,yi ≤ 103 are integers. All points are pairwise different, no three points lie on the same line.

Output Format.
Output the minimum total length of segments.
The absolute value of the difference between the answer of your program and the optimal value should be at most 10−6.
To ensure this, output your answer with at least seven digits after the decimal point
(otherwise your answer, while being computed correctly, can turn out to be wrong because of rounding issues).
*/

// Branko Milosevic 2020-09-28
// Coursera Algorithms on Graphs wk05-01

using std::vector;

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

double minimum_distance(vector<int> x, vector<int> y) {
  double result = 0.;
  //write your code here
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
      result += v.dis;
      Union(v.start, v.end, parent);
    }
  }
  return result;
}

int main() {
  size_t n;
  std::cin >> n;
  vector<int> x(n), y(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> x[i] >> y[i];
  }
  std::cout << std::setprecision(10) << minimum_distance(x, y) << std::endl;
}
