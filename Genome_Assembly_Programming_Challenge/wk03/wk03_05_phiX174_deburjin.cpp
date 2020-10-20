#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <vector>
#include <set>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

#define K_MER 12
#define MIN_OVERLAP 1
#define READSIZE 100
#define DATASIZE 1618

struct Edge
{
    int read1, read2, overlap, mismat[2];
    Edge(int r1, int r2 = -1, int o = 0) :read1(r1), read2(r2), overlap(o)
    {
       mismat[0] =  mismat[1] = -1;
    }
};

typedef vector<Edge*> Edges;
typedef vector<vector<int> > Matrix;

int find_match_length(const string& read1, const string& read2, int* mismat)
{
    for (int i = 0; i < READSIZE; i++)
    {
        int k = i;
        int max_error = 2;
        int error = 0;
        mismat[0] = mismat[1] = -1;

        for (int j=0; k < READSIZE; k++, j++)
        {
            if (read1[k] != read2[j])
            {
                if(error < 2)
                    mismat[error] = k;
                error++;
            }

            if (error > max_error)
                break;
        }

        if(k == READSIZE)
            return READSIZE - i;
    }
    return -1;
}

Edges overlap_graph(const vector<string>& reads, int n)
{
    Edges edges;
    set<int> visited = {0};
    int curRead = 0;
    int last;
    bool finalEdge = false;

    while (visited.size() != n)
    {
        last = edges.size();
        edges.push_back(new Edge(curRead));

        for (int i = 0; i < n; i++)
        {
            if (visited.find(i) == visited.end())
            {
                int mismat[2] = {-1};
                int ovl = find_match_length(reads[curRead], reads[i], mismat);

                if (ovl > edges[last]->overlap)
                {
                    edges[last]->overlap = ovl;
                    edges[last]->read2 = i;
                    edges[last]->mismat[0] = mismat[0];
                    edges[last]->mismat[1] = mismat[1];
                }
            }
        }

        curRead = edges[last]->read2;
        visited.insert(curRead);

        if(visited.size() == n && !finalEdge)
        {
            visited.erase(0);
            finalEdge = true;
        }
    }
    return edges;
}

void revise_genome(string& genome, const Edges& edges, vector<string>& reads, int n)
{
    int edgesSize = edges.size();

    for (int i=0; i<edgesSize; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            int mis_in_read1 = edges[i]->mismat[j];

            if (mis_in_read1 != -1)
            {
                const Edge* edge1 = edges[i];
                const Edge* edge2 = edges[(i+1) % edgesSize];
                const Edge* edge3 = edges[(i+2) % edgesSize];

                int read1_ovl = READSIZE - edge1->overlap;
                int read2_ovl = READSIZE - edge2->overlap;
                int read3_ovl = READSIZE - edge3->overlap;

                int mis_in_read2 = mis_in_read1 - read1_ovl;
                int mis_in_read3 = mis_in_read2 - read2_ovl;
                int mis_in_read4 = mis_in_read3 - read3_ovl;

                if (mis_in_read3 >= 0)
                {
                    int mis_char1 = edge2->mismat[0] - read2_ovl;
                    int mis_char2 = edge2->mismat[1] - read2_ovl;
                    char correctChar = reads[edge1->read1][mis_in_read1];

                    if(mis_char1 != mis_in_read3 && mis_char2 != mis_in_read3)
                        correctChar = reads[edge2->read2][mis_in_read3];
                    else if(mis_in_read4 >= 0)
                        correctChar = reads[edge3->read2][mis_in_read4];

                    reads[edge1->read1][mis_in_read1] = reads[edge1->read2][mis_in_read2] = correctChar;
                }
            }
        }
    }
}

void build_genome(string& genome, const vector<string>& reads, int n, const Edges& edges)
{
    int edgesSize = edges.size();
    genome = reads[0];

    for (int i = 0; i < edgesSize-1; i++)
        genome += reads[edges[i]->read2].substr(edges[i]->overlap, READSIZE - edges[i]->overlap);

    genome = genome.substr(0, genome.size() - edges[edgesSize-1] -> overlap);
}


int main(int argc, char** argv)
{
    vector<string> reads;
    set<string> reads_unique;
    string read;

    for (int i = 0; i < DATASIZE; i++)
    {
        cin >> read;
        reads_unique.insert(read);
    }

    for(auto r : reads_unique)
        reads.push_back(r);

    string genome;
    int readsSize = reads.size();

    Edges edges = overlap_graph(reads, readsSize);

    revise_genome(genome, edges, reads, readsSize);

    build_genome(genome, reads, readsSize, edges);

    cout << genome << endl;

    return 0;
}
