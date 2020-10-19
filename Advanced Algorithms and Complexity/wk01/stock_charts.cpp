#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <queue>
#include <limits>

/*
Task:
Given a list of 𝑛 stocks’ prices at each of 𝑘 time points, determine the minimum number of overlaid
charts you need to show all of the stocks’ prices.

Input format:
The first line of the input contains two integers 𝑛 and 𝑘 — the number of stocks and the
number of points in the year which are common for all of them. Each of the next 𝑛 lines contains 𝑘
integers. The 𝑖-th of those 𝑛 lines contains the prices of the 𝑖-th stock at the corresponding 𝑘 points
in the year.

Output Format.
Output a single integer — the minimum number of overlaid charts to visualize all the
stock price data you have.

*/

// Branko Milosevic 2020-10-13
// Coursera Advanced Algorithms and Complexity wk01-03

using std::vector;
using std::queue;
using std::numeric_limits;
using std::size_t;

class FlowGraph {
public:
    struct Edge {
        int from, to, capacity, flow;
    };

private:
    /* List of all - forward and backward - edges */
    vector<Edge> edges;

    /* These adjacency lists store only indices of edges in the edges list */
    vector<vector<size_t> > graph;

public:
    explicit FlowGraph(size_t n)
        : graph(n)
    {
        edges.reserve(n / 2);
    }

    inline void add_edge(int from, int to, int capacity)
    {
        /* Note that we first append a forward edge and then a backward edge,
       * so all forward edges are stored at even indices (starting from 0),
       * whereas backward edges are stored at odd indices in the list edges */
        Edge forward_edge = { from, to, capacity, 0 };
        Edge backward_edge = { to, from, 0, 0 };
        graph[from].push_back(edges.size());
        edges.push_back(forward_edge);
        graph[to].push_back(edges.size());
        edges.push_back(backward_edge);
    }

    inline size_t size() const
    {
        return graph.size();
    }

    inline const vector<size_t>& get_ids(int from) const
    {
        return graph[from];
    }

    inline const Edge& get_edge(size_t id) const
    {
        return edges[id];
    }

    inline void add_flow(size_t id, int flow)
    {
        /* To get a backward edge for a true forward edge (i.e id is even), we should get id + 1
       * due to the described above scheme. On the other hand, when we have to get a "backward"
       * edge for a backward edge (i.e. get a forward edge for backward - id is odd), id - 1
       * should be taken.
       *
       * It turns out that id ^ 1 works for both cases. Think this through! */
        edges[id].flow += flow;
        edges[id ^ 1].flow -= flow;
    }
};

vector<vector<int> > read_data(size_t num_stocks, size_t num_points)
{
    vector<vector<int> > stock_data(num_stocks, vector<int>(num_points));

    for (int i = 0; i < num_stocks; ++i)
        for (int j = 0; j < num_points; ++j) {
            std::cin >> stock_data[i][j];
        }

    return stock_data;
}

FlowGraph construct_graph(size_t num_stocks, size_t num_points)
{

    vector<vector<int> > stock_data = read_data(num_stocks, num_points);

    FlowGraph graph(num_stocks * 2 + 2);

    for (int i = 0; i < num_stocks; ++i)
        graph.add_edge(0, i + 1, 1);

    for (int i = 0; i < num_stocks; ++i)
    {
        int cur_stock = i;

        for (int j = 0; j < num_stocks; ++j)
        {
            if (j == cur_stock) continue;

            bool each_less{ true };

            for (int k = 0; k < num_points; ++k)
            {
                if (stock_data[i][k] >= stock_data[j][k])
                {
                    each_less = false;
                    break;
                }
            }

            if (each_less)
                graph.add_edge(i + 1, num_stocks + j + 1, 1);
        }
    }

    for (int i = num_stocks + 1; i <= num_stocks * 2; ++i)
        graph.add_edge(i, num_stocks * 2 + 1, 1);

    return graph;
}

void BFS(const FlowGraph& graph, int s, int t, vector<int>& pred)
{
    queue<int> q;
    q.push(s);

    std::fill(pred.begin(), pred.end(), -1);

    while (!q.empty())
    {
        int cur = q.front();
        q.pop();

        for (auto id : graph.get_ids(cur))
        {
            const FlowGraph::Edge& e = graph.get_edge(id);

            if (pred[e.to] == -1 && e.capacity > e.flow && e.to != s)
            {
                pred[e.to] = id;
                q.push(e.to);
            }
        }
    }
}

void max_flow(FlowGraph& graph, int s, int t)
{
    int flow = 0;

    vector<int> pred(graph.size());

    do
    {
        BFS(graph, s, t, pred);

        if (pred[t] != -1)
        {
            int min_flow = numeric_limits<int>::max();

            for (int u = pred[t]; u != -1; u = pred[graph.get_edge(u).from])
                min_flow = std::min(min_flow, graph.get_edge(u).capacity - graph.get_edge(u).flow);

            for (int u = pred[t]; u != -1; u = pred[graph.get_edge(u).from])
                graph.add_flow(u, min_flow);

            flow += min_flow;
        }

    } while (pred[t] != -1);
}

int min_overlaid_charts(const FlowGraph& graph, int num_stocks)
{

    int min_path_cover{ 0 };

    for (int i = 1; i <= num_stocks; ++i)
    {
        for (auto id : graph.get_ids(i))
        {
            const FlowGraph::Edge& e = graph.get_edge(id);
            if (e.flow > 0)
            {
                ++min_path_cover;
                break;
            }
        }
    }

    return (num_stocks - min_path_cover);
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    size_t num_stocks, num_points;
    std::cin >> num_stocks >> num_points;

    FlowGraph graph = construct_graph(num_stocks, num_points);

    max_flow(graph, 0, graph.size() - 1);
    std::cout << min_overlaid_charts(graph, num_stocks) << std::endl;

    return 0;
}

/*==================================================================================================================*/
/*
using std::vector;
using std::cin;
using std::cout;

class StockCharts {
 public:
  void Solve() {
    vector<vector<int>> stock_data = ReadData();
    int result = MinCharts(stock_data);
    WriteResponse(result);
  }

 private:
  vector<vector<int>> ReadData() {
    int num_stocks, num_points;
    cin >> num_stocks >> num_points;
    vector<vector<int>> stock_data(num_stocks, vector<int>(num_points));
    for (int i = 0; i < num_stocks; ++i)
      for (int j = 0; j < num_points; ++j) {
        cin >> stock_data[i][j];
      }
    return stock_data;
  }

  void WriteResponse(int result) {
    cout << result << "\n";
  }

  int MinCharts(const vector<vector<int>>& stock_data) {
    // Replace this incorrect greedy algorithm with an
    // algorithm that correctly finds the minimum number
    // of charts on which we can put all the stock data
    // without intersections of graphs on one chart.

    int num_stocks = stock_data.size();
    // Vector of charts; each chart is a vector of indices of individual stocks.
    vector<vector<int>> charts;
    for (int i = 0; i < stock_data.size(); ++i) {
      bool added = false;
      for (auto& chart : charts) {
        bool can_add = true;
        for (int index : chart)
          if (!compare(stock_data[i], stock_data[index]) &&
              !compare(stock_data[index], stock_data[i])) {
            can_add = false;
            break;
          }
        if (can_add) {
          chart.push_back(i);
          added = true;
          break;
        }
      }
      if (!added) {
        charts.emplace_back(vector<int>{i});
      }
    }
    return charts.size();
  }

  bool compare(const vector<int>& stock1, const vector<int>& stock2) {
    for (int i = 0; i < stock1.size(); ++i)
      if (stock1[i] >= stock2[i])
        return false;
    return true;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  StockCharts stock_charts;
  stock_charts.Solve();
  return 0;
}
*/
