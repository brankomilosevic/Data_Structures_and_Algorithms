#include <iostream>
#include <vector>
#include <queue>

/*
Task.
Given an undirected graph with n vertices and m edges and two vertices u and v,
compute the length of a shortest path between u and v (that is, the minimum number of edges in a path from u to v).

Input Format.
A graph is given in the standard format. The next line contains two vertices u and v.

Constraints.
2 ≤ n ≤ 105, 0 ≤ m ≤ 105, u ̸= v, 1 ≤ u,v ≤ n.

Output Format.
Output the minimum number of edges in a path from u to v, or −1 if there is no path.
*/

// Branko Milosevic 2020-09-28
// Coursera Algorithms on Graphs wk03-01

using std::vector;
using std::queue;

int distance(vector<vector<int> > &adj, int s, int t) {
  //write your code here
  const int INF = -1;
  vector <int> distance(adj.size(), INF);
  distance[s] = 0;
  queue<int> q;
  q.push(s);

  while (!q.empty())
  {
    int cur = q.front();
    q.pop();

    for (int i = 0; i < adj[cur].size(); i++)
    {
      int next = adj[cur][i];
      if (distance[next] == INF)
      {
        q.push(next);
        distance[next] = distance[cur] + 1;
      }
    }
  }
  return distance[t];
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, s, t);
}
