#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;

/*
Task.
Given an directed graph with positive edge weights and with n vertices and m edges as well as two vertices u and v,
compute the weight of a shortest path between u and v (that is, the minimum total weight of a path from u to v).

Input Format.
A graph is given in the standard format. The next line contains two vertices u and v.

Constraints.
1 ≤ n ≤ 104, 0 ≤ m ≤ 105, u ̸= v, 1 ≤ u,v ≤ n, edge weights are non-negative integers not exceeding 108.

Output Format.
Output the minimum weight of a path from u to v, or −1 if there is no path.
*/

// Branko Milosevic 2020-09-28
// Coursera Algorithms on Graph wk04-01

long long distance(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, int t) {
  //write your code her
	const int INF = 1000000000;
	vector<int> dis(adj.size(), INF);
	vector<bool> visited(adj.size(), 0);
	dis[s] = 0;

	for (int i = 0; i < adj.size(); i++)
    {
		int u = -1;
		int MIN = INF;
		for (int j = 0; j<adj.size(); j++)
		{
			if (!visited[j] && dis[j] < MIN)
			{
				MIN = dis[j];
				u = j;
			}
		}
		if (u == -1) break;

		visited[u] = 1;

		for (int j = 0; j < adj[u].size(); j++)
        {
			int next = adj[u][j];
			if (!visited[next] && dis[u] + cost[u][j]<dis[next])
				dis[next] = dis[u] + cost[u][j];
		}

	}

	if (dis[t] == INF) return -1;
	return dis[t];
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
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, cost, s, t);
}
