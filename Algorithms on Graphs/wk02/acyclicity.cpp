#include <iostream>
#include <vector>

using std::vector;
using std::pair;

/*
Task.
Check whether a given directed graph with 𝑛 vertices and 𝑚 edges contains a cycle.
Input Format.
A graph is given in the standard format.
Constraints.
1 ≤ 𝑛 ≤ 103, 0 ≤ 𝑚 ≤ 103.
Output Format.
Output 1 if the graph contains a cycle and 0 otherwise.
*/

// Branko Milosevic 2020-09-25
// Coursera Algorithms on Graphs wk02-01

bool isDAG = true;

void DFS(int start, vector<vector<int> > &adj, vector<int> &visited)
{
  visited[start] = -1;
  for (int i = 0; i < adj[start].size() && isDAG; i++)
  {
    if (visited[adj[start][i]] == 0)
    {
      DFS(adj[start][i], adj, visited);
    }
    else if (visited[adj[start][i]] == -1)
    {
      isDAG = false;
      return;
    }
  }
  visited[start] = 1;
}

int acyclic(vector<vector<int> > &adj) {
  vector<int> visited(adj.size(), 0);

  for (int i = 0; i < adj.size(); i++)
  {
    if (visited[i] == 0) DFS(i, adj, visited);

    if (!isDAG) return 1;
  }
  return 0;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
  }
  std::cout << acyclic(adj);
}
