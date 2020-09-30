#include <iostream>
#include <algorithm>
#include <vector>

using std::vector;
using std::pair;

/*
Task. Compute a topological ordering of a given directed acyclic graph (DAG) with 𝑛 vertices and 𝑚 edges.
Input Format. A graph is given in the standard format.
Constraints. 1 ≤ 𝑛 ≤ 105, 0 ≤ 𝑚 ≤ 105. The given graph is guaranteed to be acyclic.
Output Format. Output any topological ordering of its vertices. (Many DAGs have more than just one
topological ordering. You may output any of them.)
*/

// Branko Milosevic 2020-09-25
// Coursera Algorithms on Graphs wk02-02

void dfs(vector<vector<int> > &adj, vector<int> &used, vector<int> &order, int x) {
  //write your code here
  used[x]=1;
  for(int i = 0; i < adj[x].size(); i++)
  {
    if(!used[adj[x][i]])
    dfs(adj, used, order, adj[x][i]);
  }
  order.push_back(x);
}

vector<int> toposort(vector<vector<int> > adj) {
  vector<int> used(adj.size(), 0);
  vector<int> order;
  //write your code here
  for(int i = 0; i < adj.size(); i++)
  {
    if(!used[i])
    dfs(adj,used,order,i);
  }
  reverse(order.begin(), order.end());
  return order;
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
  vector<int> order = toposort(adj);
  for (size_t i = 0; i < order.size(); i++) {
    std::cout << order[i] + 1 << " ";
  }
}
