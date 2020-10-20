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
#define KMER 10
#define DATASIZE 5396

using namespace std;
typedef vector<vector<int>> Graph;

int find_start_vertex(const map<int, int>& opts, vector<int>& last_ones)
{
    while (!last_ones.empty())
    {
        int start = last_ones.back();
        last_ones.pop_back();

        if (opts.find(start) != opts.end())
            return start;
    }
}

//Eulerian path passes all edges and every edge exactly once
void eulerian_path(Graph& graph, vector<int>& path)
{
    int n = graph.size();
    map<int, int> optionalStarts;
    vector<int> last_ones(1, 0);
    vector<int> new_cycle;

    path.push_back(0);
    optionalStarts[0] = 0;

    while(!optionalStarts.empty())
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
        while(cur_node != start);

        path.insert(path.begin() + position + 1, new_cycle.begin(), new_cycle.end());
        new_cycle.clear();
    }
}

void add_edge(Graph& graph, const string& kmer, vector<string>& k_1_mers)
{
    static int k_1 = kmer.size() - 1;
    static int vertex = 0;
    static map<string, int> labels;

    string L_kmer = kmer.substr(0, k_1);
    string R_kmer = kmer.substr(1, k_1);
    int L_label, R_label;

    if(labels.find(L_kmer) != labels.end()) L_label = labels[L_kmer];
    else { graph.push_back(vector<int>()); L_label = labels[L_kmer] = vertex++; k_1_mers.push_back(L_kmer); }

    if(labels.find(R_kmer) != labels.end()) R_label = labels[R_kmer];
    else { graph.push_back(vector<int>()); R_label = labels[R_kmer] = vertex++;   k_1_mers.push_back(R_kmer); }

    graph[L_label].push_back(R_label);
}

void k_1_compositions(Graph& graph, const string& kmer, vector<string>& k_1_mers, int from=0)
{
    static int k = kmer.size();
    add_edge(graph, kmer, k_1_mers);

    for (int i = from; i < k; i++)
    {
        string newKmer = kmer;
        newKmer[i] = char('0'+(((kmer[i]-'0')+1)%2));
        k_1_compositions(graph, newKmer, k_1_mers, i+1);
    }

}

Graph de_bruijn_graph(vector<string>& k_1_mers)
{
    int k;
    cin >> k;

    Graph graph;
    string first_kmer (k, '0');
    k_1_compositions(graph, first_kmer, k_1_mers);

    return graph;
}

void build_k_universal_string(const vector<string>& k_1_mers, vector<int>& path, string& result)
{
    stringstream universal_string;
    universal_string << k_1_mers[path[1]];
    int k_1 = k_1_mers[0].size();

    for (int i = 2; i < path.size()-1; i++)
        universal_string << k_1_mers[path[i]][k_1 - 1];

    result = universal_string.str();
    int border_zeros = result.find('1') + (result.size() - result.find_last_of('1') - 1);

    result = result.substr(0, result.size() - (border_zeros - (k_1 + 1)));
}


int main(int argc, char** argv)
{
    vector<string> k_1_mers;
    Graph graph = de_bruijn_graph(k_1_mers);

    vector<int> path;
    eulerian_path(graph, path);

    string k_universal_string;
    build_k_universal_string(k_1_mers, path, k_universal_string);
    cout<<k_universal_string<<endl;

    return 0;
}
