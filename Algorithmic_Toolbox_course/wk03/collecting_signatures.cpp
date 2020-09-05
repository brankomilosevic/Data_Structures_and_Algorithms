#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>

/*
Problem Description
Task. Given a set of 𝑛 segments {[𝑎0, 𝑏0], [𝑎1, 𝑏1], . . . , [𝑎𝑛−1, 𝑏𝑛−1]} with integer coordinates on a line, find
the minimum number 𝑚 of points such that each segment contains at least one point. That is, find a
set of integers 𝑋 of the minimum size such that for any segment [𝑎𝑖, 𝑏𝑖] there is a point 𝑥 ∈ 𝑋 such
that 𝑎𝑖 ≤ 𝑥 ≤ 𝑏𝑖.
Input Format. The first line of the input contains the number 𝑛 of segments. Each of the following 𝑛 lines
contains two integers 𝑎𝑖 and 𝑏𝑖 (separated by a space) defining the coordinates of endpoints of the 𝑖-th
segment.
Constraints. 1 ≤ 𝑛 ≤ 100; 0 ≤ 𝑎𝑖 ≤ 𝑏𝑖 ≤ 109 for all 0 ≤ 𝑖 < 𝑛.
Output Format. Output the minimum number 𝑚 of points on the first line and the integer coordinates
of 𝑚 points (separated by spaces) on the second line. You can output the points in any order. If there
are many such sets of points, you can output any set. (It is not difficult to see that there always exist
a set of points of the minimum size such that all the coordinates of the points are integers.)
*/

// Branko Milosevi 2020-08-31
// Coursera Algorithms Toolbox wk03-05

using std::vector;

struct Segment {
  int start, end;
};

bool points_arrange (Segment a, Segment b)
{
   return (a.end < b.end);
}

vector<int> optimal_points(vector<Segment> &segments) {
  vector<int> points;
  //write your code here

  int num_segments = segments.size();
  int point;

  sort(segments.begin(), segments.end(), points_arrange);

// for (int i = 0; i < num_segments; i++) std::cout << "(" << segments[i].start << " : " << segments[i].end << ")\n";

    point = segments[0].end;
    points.push_back(point);

    for (int i = 1; i < num_segments; ++i)
    {
        if (point < segments[i].start || point > segments[i].end)
        {
            point = segments[i].end;
            points.push_back(point);
        }
    }

  return points;
}



int main() {
  int n;
  std::cin >> n;
  vector<Segment> segments(n);
  for (size_t i = 0; i < segments.size(); ++i) {
    std::cin >> segments[i].start >> segments[i].end;
  }
  vector<int> points = optimal_points(segments);
  std::cout << points.size() << "\n";
  for (size_t i = 0; i < points.size(); ++i) {
    std::cout << points[i] << " ";
  }
}
