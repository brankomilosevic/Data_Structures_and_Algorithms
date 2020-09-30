#include <iostream>
#include <vector>

using std::vector;
using std::pair;

/*
Task.
Given an undirected graph and two distinct vertices 𝑢 and 𝑣, check if there is a path between 𝑢 and 𝑣.
Input Format.
An undirected graph with 𝑛 vertices and 𝑚 edges. The next line contains two vertices 𝑢 and 𝑣 of the graph.
Constraints.
2 ≤ 𝑛 ≤ 103; 1 ≤ 𝑚 ≤ 103; 1 ≤ 𝑢, 𝑣 ≤ 𝑛; 𝑢 ̸= 𝑣.
Output Format.
Output 1 if there is a path between 𝑢 and 𝑣 and 0 otherwise.
*/

// Branko Milosevic 2020-09-25
// Coursera Algorithms on Graphs wk01-01

vector<bool> visited;

int reach(vector<vector<int> > &adj, int x, int y) {
  // write your code here
  visited[x] = true;

  if (visited[y] == true) return 1;

  for (int i = 0; i < adj[x].size(); i++)
  {
    if (!visited[adj[x][i]]) reach(adj, adj[x][i], y);
    if (visited[y]) return 1;
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
    adj[y - 1].push_back(x - 1);
  }
  int x, y;
  std::cin >> x >> y;
  visited.resize(n);
  std::cout << reach(adj, x - 1, y - 1);
}
