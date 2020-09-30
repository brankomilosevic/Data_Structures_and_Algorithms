#include <iostream>
#include <limits>
#include <vector>
#include <queue>

/*
Task.
Given an directed graph with possibly negative edge weights and with n vertices and m edges as well as its vertex s,
compute the length of shortest paths from s to all other vertices of the graph.

Input Format.
A graph is given in the standard format.

Constraints.
1 ≤ n ≤ 103, 0 ≤ m ≤ 104, 1 ≤ s ≤ n, edge weights are integers of absolute value at most 109.

Output Format.
For all vertices i from 1 to n output the following on a separate line:
  ∙ “*”, if there is no path from s to u;
  ∙ “-”, if there is a path from s to u, but there is no shortest path from s to u (that is, the distance from s to u is −∞);
  ∙ the length of a shortest path otherwise.
*/

// Branko Milosevic 2020-09-28
// Coursera Algorithms on Graphs wk04-03

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;

void shortest_paths(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, vector<long long> &distance, vector<int> &reachable, vector<int> &shortest) {
  distance[s]=0;
  reachable[s]=1;
  const int INF = std::numeric_limits<long long>::max();

  for(int k = 1; k < adj.size(); k++)
  {
    for(int i = 0; i < adj.size(); i++)
    {
      for(int j = 0; j < adj[i].size(); j++)
      {
        int next = adj[i][j];
        if(distance[i] != INF && distance[i] + cost[i][j] < distance[next])
        {
          distance[next] = distance[i] + cost[i][j];
          reachable[next] = 1;
        }
      }
    }
  }

  queue<int> q;

  for(int i = 0; i < adj.size(); i++)
  {
      for(int j = 0; j < adj[i].size(); j++)
      {
        int next = adj[i][j];
        if(distance[i] != INF && distance[i] + cost[i][j] < distance[next])
        {
          distance[next] = distance[i] + cost[i][j];
          if(shortest[next])
          {
            q.push(next);
            shortest[next]=0;
          }
        }
      }
    }

    while(!q.empty())
    {
      int cur = q.front();
      q.pop();
      for(int i = 0; i < adj[cur].size(); i++)
      {
        int next = adj[cur][i];
        if(shortest[next])
        {
          q.push(next);
          shortest[next]=0;
        }
      }
    }
}

int main() {
  int n, m, s;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  std::cin >> s;
  s--;
  vector<long long> distance(n, std::numeric_limits<long long>::max());
  vector<int> reachable(n, 0);
  vector<int> shortest(n, 1);
  shortest_paths(adj, cost, s, distance, reachable, shortest);
  for (int i = 0; i < n; i++) {
    if (!reachable[i]) {
      std::cout << "*\n";
    } else if (!shortest[i]) {
      std::cout << "-\n";
    } else {
      std::cout << distance[i] << "\n";
    }
  }
}
