#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

/*
Problem Description
Task. You are given a set of points on a line and a set of segments on a line. The goal is to compute, for
each point, the number of segments that contain this point.
Input Format. The first line contains two non-negative integers 𝑠 and 𝑝 defining the number of segments
and the number of points on a line, respectively. The next 𝑠 lines contain two integers 𝑎𝑖, 𝑏𝑖 defining
the 𝑖-th segment [𝑎𝑖, 𝑏𝑖]. The next line contains 𝑝 integers defining points 𝑥1, 𝑥2, . . . , 𝑥𝑝.
Constraints. 1 ≤ 𝑠, 𝑝 ≤ 50000; −108 ≤ 𝑎𝑖 ≤ 𝑏𝑖 ≤ 108 for all 0 ≤ 𝑖 < 𝑠; −108 ≤ 𝑥𝑗 ≤ 108 for all 0 ≤ 𝑗 < 𝑝.
Output Format. Output 𝑝 non-negative integers 𝑘0, 𝑘1, . . . , 𝑘𝑝−1 where 𝑘𝑖 is the number of segments which
contain 𝑥𝑖. More formally,
𝑘𝑖 = |{𝑗 : 𝑎𝑗 ≤ 𝑥𝑖 ≤ 𝑏𝑗}| .
*/

// Branko Milosevic 2020-09-01
// Coursera Algorithms Toolbox wk04-05

using std::vector;
using std::pair;
using std::make_pair;
using std::map;

bool compare_big_array(pair<int, int> a, pair<int, int> b);

vector<int> fast_count_segments(vector<int> starts, vector<int> ends, vector<int> points)
{
  vector<int> cnt;
  //write your code here

  int N = starts.size();
  int P = points.size();

  constexpr int LEFT = 1;
  constexpr int RIGHT = 3;
  constexpr int POINT = 2;

  vector<pair<int, int>> big_array (N + N + P);

  for (int i = 0; i < N; i++)
    big_array[i] = make_pair(starts[i], LEFT);
  for (int i = N; i < N + N; i++)
   big_array[i]= make_pair(ends[i - N], RIGHT);
  for (int i = N + N ; i < N + N + P; i++)
    big_array[i] = make_pair(points[i - N - N], POINT);

  sort(big_array.begin(), big_array.end(), compare_big_array);
/*
  for (int i = 0; i < big_array.size(); i++)
    std::cout << "\n [" << big_array[i].first << ", " << big_array[i].second << "]";
*/

  map<int, int> m;
  int tmp_count = 0;

  for (int i = 0; i < big_array.size(); i++)
  {
    if (big_array[i].second == LEFT) tmp_count++;
    if (big_array[i].second == RIGHT) tmp_count--;
    if (big_array[i].second == POINT) m[big_array[i].first] = tmp_count;
  }

  for (int i = 0; i < P; i++)
    cnt.push_back(m[points[i]]);

  return cnt;
}

bool compare_big_array(pair<int, int> a, pair<int, int> b)
{
  if (a.first  != b.first)
    return a.first < b.first;
  else
    return a.second < b.second;
}

vector<int> naive_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
  vector<int> cnt(points.size());
  for (size_t i = 0; i < points.size(); i++) {
    for (size_t j = 0; j < starts.size(); j++) {
      cnt[i] += starts[j] <= points[i] && points[i] <= ends[j];
    }
  }
  return cnt;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<int> starts(n), ends(n);
  for (size_t i = 0; i < starts.size(); i++) {
    std::cin >> starts[i] >> ends[i];
  }
  vector<int> points(m);
  for (size_t i = 0; i < points.size(); i++) {
    std::cin >> points[i];
  }
  //use fast_count_segments
  vector<int> cnt = fast_count_segments(starts, ends, points);
  for (size_t i = 0; i < cnt.size(); i++) {
    std::cout << cnt[i] << ' ';
  }
}
