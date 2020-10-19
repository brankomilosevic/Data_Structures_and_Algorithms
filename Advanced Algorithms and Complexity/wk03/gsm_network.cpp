#include <ios>
#include <iostream>
#include <vector>

using namespace std;

struct Edge {
    int from;
    int to;
};

struct ConvertGSMNetworkProblemToSat {
    int numVertices;
    vector<Edge> edges;
    static constexpr auto K = 3;

    ConvertGSMNetworkProblemToSat(int n, int m) :
        numVertices(n),
        edges(m)
    {  }

    void printEquisatisfiableSatFormula()
    {
        const int C = K * edges.size() + numVertices;
        const int V = numVertices * K;

        printf("%d %d\n", C, V);

        for (int j = 0, cnt = 1; j < numVertices; ++j, cnt += K)
            printf("%d %d %d 0\n", cnt, cnt + 1, cnt + 2);

        for (const Edge& e : edges)
        {
            printf("%d %d 0\n", -((e.from - 1) * K + 1), -((e.to - 1) * K + 1));
            printf("%d %d 0\n", -((e.from - 1) * K + 2), -((e.to - 1) * K + 2));
            printf("%d %d 0\n", -((e.from - 1) * K + 3), -((e.to - 1) * K + 3));
        }
    }
};

int main() {
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    ConvertGSMNetworkProblemToSat converter(n, m);
    for (int i = 0; i < m; ++i) {
        cin >> converter.edges[i].from >> converter.edges[i].to;
    }

    converter.printEquisatisfiableSatFormula();

    return 0;
}
