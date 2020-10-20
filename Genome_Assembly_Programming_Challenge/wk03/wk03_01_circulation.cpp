#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
#include <limits.h>

using namespace std;

struct Edge
{
    int from, to, cost;
};

class Circulation
{
private:
    vector<Edge> edges;
    vector<vector<int>> init_flow;
    vector<vector<size_t> > graph;
    vector<int> lower_edges;
    int numVertexes;
    int numEdges;
    int lowerBoundSum;
    int maxFlow;

public:
    void read_data()
    {
        int n;
        cin >> n >> numEdges;
        numVertexes = n + 2;
        lowerBoundSum = 0;

        graph = vector<vector<size_t> >(numVertexes);
        init_flow = vector<vector<int>>(numVertexes+1, vector<int>(2, 0));

        for (int i = 0; i < numEdges; i++)
        {
            int u, v, low_bound,capacity;
            cin >> u >> v >> low_bound >> capacity;

            add_edge(u, v, capacity - low_bound);

            init_flow[u][1] += low_bound;
            init_flow[v][0] += low_bound;
            lowerBoundSum   += low_bound;

            lower_edges.push_back(low_bound);
        }
    }

    void solve()
    {
        add_source_sink();
        update_max_flow();
    }

    void print()
    {
        if (maxFlow == lowerBoundSum)
        {
            cout<< "YES" <<endl;
            for (int i = 0; i < numEdges; i++)
                cout << lower_edges[i] + edges[2*i + 1].cost<<endl;
        }
        else
            cout << "NO" << endl;
    }

    void add_edge(int from, int to, int cost)
    {
        Edge forward_edge = {from, to, cost};
        Edge backward_edge = {to, from, 0};

        graph[from].push_back(edges.size());
        edges.push_back(forward_edge);

        graph[to].push_back(edges.size());
        edges.push_back(backward_edge);
    }

    void update_flow(size_t id, int flow)
    {
        edges[id].cost     -= flow;
        edges[id ^ 1].cost += flow;
    }

    void add_source_sink()
    {
        for (int i = 1; i < numVertexes-1; i++)
        {
            add_edge(0, i, init_flow[i][0]);
            add_edge(i, numVertexes-1, init_flow[i][1]);
        }
    }

    void bfs(vector<vector<int>>& parents)
    {
        set<int> visited = {0};
        queue<int> nodes;
        nodes.push(0);

        while (!nodes.empty())
        {
            int curNod = nodes.front();
            nodes.pop();

            for (const auto& edgeid : graph[curNod])
            {
                const Edge edge= edges[edgeid];
                if (edge.cost > 0 && visited.find(edge.to) == visited.end())
                {
                    nodes.push(edge.to);
                    visited.insert(edge.to);

                    parents[edge.to][0] = curNod;
                    parents[edge.to][1] = edgeid;

                    if (edge.to == numVertexes-1) return;
                }
            }
        }
    }


    int find_ap(vector<vector<int>>& parents)
    {
        bfs(parents);

        int minres = INT_MAX;
        int curnode = numVertexes-1;

        while (parents[curnode][0] != - 1)
        {
            const Edge edge = edges[parents[curnode][1]];
            minres = min(minres, edge.cost);
            curnode = parents[curnode][0];
        }
        return minres;
    }

    void update_max_flow()
    {
        vector<vector<int>> parents(numVertexes, vector<int>(2, -1));
        int mr;
        maxFlow = 0;

        while ((mr = find_ap(parents)) != INT_MAX)
        {
            int curnode = numVertexes - 1;
            while (parents[curnode][0] != - 1)
            {
                const Edge edge = edges[parents[curnode][1]];
                update_flow(parents[curnode][1], mr);
                curnode = parents[curnode][0];
            }

            maxFlow += mr;

            for (int i = 0; i < parents.size(); i++)
                parents[i][0] = parents[i][1] = -1;
        }
    }
};

int main()
{
    std::ios_base::sync_with_stdio(false);
    Circulation circulation;
    circulation.read_data();
    circulation.solve();
    circulation.print();
    return 0;
}
