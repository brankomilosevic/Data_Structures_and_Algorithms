#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <stdio.h>

using namespace std;
typedef vector<vector<int>> Graph;

int find_start_vertex(const map<int, int>& opts, vector<int>& last_ones)
{
    while (!last_ones.empty())
    {
        int start = last_ones.back();
        last_ones.pop_back();

        if(opts.find(start) != opts.end())
            return start;
    }

    return 0; // it should not reach this point
}

// EULERIAN PATH - passes all edges and every edge exactly once
void eulerian_path(Graph& graph, vector<int>& path)
{
    int n = graph.size();
    map<int, int> optionalStarts;
    vector<int> last_ones(1, 0);
    vector<int> new_cycle;

    path.push_back(0);
    optionalStarts[0] = 0;

    while (!optionalStarts.empty())
    {
        int start = find_start_vertex(optionalStarts, last_ones);
        int position = optionalStarts[start];

        int next_node, cur_node;
        cur_node = start;
        int pos = position;

        do
        {
            next_node = graph[cur_node].back();
            new_cycle.push_back(next_node);
            graph[cur_node].pop_back();

            if (graph[cur_node].size())
            {
                optionalStarts[cur_node] = pos;
                last_ones.push_back(cur_node);
            }
            else
                optionalStarts.erase(cur_node);

            pos++;
            cur_node = next_node;

        }
        while (cur_node != start);

        path.insert(path.begin() + position + 1, new_cycle.begin(), new_cycle.end());
        new_cycle.clear();
    }
}

Graph read_graph(Graph& balancing, int n, int m)
{
    Graph graph(n, vector<int>());

    for (int i= 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        graph[u-1].push_back(v-1);
        balancing[u-1][0]++;
        balancing[v-1][1]++;
    }
    return graph;
}

void print_path(Graph& graph, vector<int>& path)
{
    for (const auto& v : graph)
    {
        if(v.size() != 0)
        {
            cout<<0<<endl;
            return;
        }
    }
    cout << 1 << endl;

    for (int i = 0; i < path.size()-1; i++)
        cout<<path[i]+1<<" "; cout<<endl;
}

bool is_balancing(const Graph& graph)
{
    for (const auto& v : graph) if (v[0] != v[1]) return false;
    return true;
}

int main(int argc, char** argv)
{
    int n, m;
    cin >> n >> m;
    Graph balancing (n, vector<int>(2));
    Graph graph = read_graph(balancing, n, m);

    if(! is_balancing(balancing))
    {
        cout << 0 << endl;
        return 0;
    }

    vector<int> path;
    eulerian_path(graph, path);

    print_path(graph, path);

    return 0;
}
