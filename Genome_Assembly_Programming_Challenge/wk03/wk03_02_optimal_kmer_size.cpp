#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <limits.h>
#include <vector>
#include <set>
using namespace std;

#define K_MER 12
#define MIN_OVERLAP 1
#define READSIZE 100
#define DATASIZE 400

int overlap_graph(const vector<string>& reads, int n)
{
    int minovlap = INT_MAX;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if(i != j)
                for (int w = 0; w < READSIZE; w++)
                {
                    int k = w;

                    for(int f=0; k < READSIZE; k++, f++)
                        if(reads[i][k] != reads[j][f]) break;

                    if (k == READSIZE)   minovlap = min(minovlap, READSIZE - w);
                }
        }
    }

    return minovlap;
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

    cout<<overlap_graph(reads, reads.size())<<endl;

    return 0;
}
