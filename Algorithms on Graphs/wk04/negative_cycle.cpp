#include <iostream>
#include <vector>

/*
Task.
Given an directed graph with possibly negative edge weights and with n vertices and m edges,
check whether it contains a cycle of negative weight.

Input Format.
A graph is given in the standard format.

Constraints.
1 ≤ n ≤ 103, 0 ≤ m ≤ 104, edge weights are integers of absolute value at most 103.

Output Format.
Output 1 if the graph contains a cycle of negative weight and 0 otherwise.
*/

// Branko Milosevic 2020-09-28
// Coursera Algorithms on Graphs wk04-02

using std::vector;

int negative_cycle(vector<vector<int> > &adj, vector<vector<int> > &cost) {
  //write your code here
  const int INF = 100000000;
  vector<int> distance(adj.size(), INF);
  distance[0] = 0;

  for (int k = 1; k < adj.size(); k++)
  {
    for (int i = 0; i < adj.size(); i++)
    {
      for (int j = 0; j < adj[i].size(); j++)
      {
        int next = adj[i][j];
        if (distance[i] + cost[i][j] < distance[next])
        distance[next] = distance[i] + cost[i][j];
      }
    }
  }

  for (int i = 0; i < adj.size(); i++)
  {
    for (int j = 0; j < adj[i].size(); j++)
    {
      int next = adj[i][j];
      if (distance[i] + cost[i][j] < distance[next])
        return 1;
    }
  }

  return 0;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  std::cout << negative_cycle(adj, cost);
}
