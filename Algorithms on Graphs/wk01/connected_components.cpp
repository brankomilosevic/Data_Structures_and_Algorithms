#include <iostream>
#include <vector>

using std::vector;
using std::pair;

/*
Task.
Given an undirected graph with 𝑛 vertices and 𝑚 edges, compute the number of connected components in it.
Input Format.
A graph is given in the standard format.
Constraints.
1 ≤ 𝑛 ≤ 103, 0 ≤ 𝑚 ≤ 103.
Output Format.
Output the number of connected components.
*/

// Branko Milosevic 2020-09-25
// Coursera Algorithms on graphs wk01-02

vector<bool> visited;

void DFS(int start, vector<vector<int>> &adj) {
  visited[start] = true;
  for (int i = 0; i < adj[start].size(); i++)
  {
    if (!visited[adj[start][i]])
      DFS(adj[start][i], adj);
  }
}

int number_of_components(vector<vector<int> > &adj) {
  int res = 0;
  // write your code here
  for (int i = 0; i < adj.size(); i++)
  {
    if (!visited[i])
    {
      DFS(i, adj);
      res++;
    }
  }
  return res;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  visited.resize(n);
  std::cout << number_of_components(adj);
}
