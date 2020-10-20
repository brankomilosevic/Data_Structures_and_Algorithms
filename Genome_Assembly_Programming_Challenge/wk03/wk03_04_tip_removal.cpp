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
#include <math.h>
#define KMER 15
#define READSIZE 100
#define DATASET 1618
using namespace std;

typedef vector<vector<set<int>>> Graph;
typedef vector<vector<int> > Matrix;

class DebruijnGraph
{
public:
    Graph create()
    {
        return de_bruijn_graph();
    }
private:
    void add_edge(Graph& graph, const string& kmer)
    {
        static int k_1 = KMER - 1;
        static int vertex = 0;
        static map<string, int> labels;

        string L_kmer = kmer.substr(0, k_1);
        string R_kmer = kmer.substr(1, k_1);
        int L_label, R_label;

        if (labels.find(L_kmer) != labels.end())
            L_label = labels[L_kmer];
        else
        {
            graph.push_back(vector<set<int>>(2, set<int>()));
            L_label = labels[L_kmer] = vertex++;
        }

        if(labels.find(R_kmer) != labels.end())
            R_label = labels[R_kmer];
        else
        {
            graph.push_back(vector<set<int>>(2, set<int>()));
            R_label = labels[R_kmer] = vertex++;
        }

        graph[L_label][0].insert(R_label);

        graph[R_label][1].insert(L_label);
    }

    Graph de_bruijn_graph()
    {
        Graph graph;
        string read;

            while (cin >> read)
                for (int j = 0; j < READSIZE - KMER + 1; j++)
                    add_edge(graph, read.substr(j, KMER));

        return graph;
    }

};

class TipsRemoval
{
private:
    Graph graph;
    Matrix in_out;
    set<int> out_tips;
    set<int> in_tips;
    int nodes;
    int tips;

public:
    TipsRemoval(Graph g): graph(g)
    {
        nodes = graph.size();
        tips = 0;
        in_out = Matrix(nodes, vector<int>(2, 0));
    }

    int tips_number()
    {
        find_candidates();
        bfs_in_tips();
        bfs_out_tips();
        return tips;
    }

    void find_candidates()
    {
        for (int i = 0; i < nodes; i++)
        {
            in_out[i][0] = graph[i][0].size();
            in_out[i][1] = graph[i][1].size();
        }

        for (int i = 0; i < nodes; i++)
        {
            if(in_out[i][0] == 0) out_tips.insert(i);
            if(in_out[i][1] == 0) in_tips.insert(i);
        }
    }

    void bfs_in_tips()
    {
        while(! in_tips.empty())
        {
            int curtip = *(in_tips.begin());
            in_tips.erase(curtip);

            for(const auto& child : graph[curtip][0])
            {
                graph[curtip][0].erase(child);
                graph[child][1].erase(curtip);
                tips++;
                if (graph[child][1].size() == 0 && out_tips.find(child) == out_tips.end())
                    in_tips.insert(child);
            }
        }
    }

    void bfs_out_tips()
    {
         while (! out_tips.empty())
        {
            int curtip = *(out_tips.begin());
            out_tips.erase(curtip);

            for (const auto& parent : graph[curtip][1])
            {
                graph[curtip][1].erase(parent);
                graph[parent][0].erase(curtip);
                tips++;

                if (graph[parent][0].size() == 0) out_tips.insert(parent);
            }
        }
    }
};

int main(int argc, char** argv)
{
    DebruijnGraph dbGraph;
    Graph graph = dbGraph.create();

    TipsRemoval tr (graph);
    cout<<tr.tips_number()<<endl;

    return 0;
}
