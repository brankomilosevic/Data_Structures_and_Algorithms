#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdio>
#include <set>
#include <float.h>
#include <math.h>
using namespace std;

// Branko Milosevic 2020-09-19
// Coursera Advanced Algorithms and Complexity wk02-02

const double EPS = 1e-3;
const int PRECISION = 20;

typedef vector<double> Row;
typedef vector<Row> Matrix;
typedef vector<bool> BoolV;
typedef vector<set<int> > SubSets;
enum {NSOL, SOL, INF} ;
int n, m;

int SelectPivotElement(const Matrix &gm, BoolV &used_rows, int col)
{
    int i = 0;
    while (i < m && (used_rows[i] || gm[i][col] == 0)) i++;
    if (i == m) return -1;
    return i;
}

void SwapLines(Matrix &a, vector <bool> &used_rows, int r, int c)
{
    swap(a[r], a[c]);
    swap(used_rows[r], used_rows[c]);
}

void ProcessPivotElement(Matrix &gm, int pivot)
{
    double A = gm[pivot][pivot];
    int N = gm.size();
    for(int j = 0; j <= N; j++)
        gm[pivot][j] /= A;

    for(int i = 0; i < N; i++)
    {
        if(i != pivot && gm[i][pivot] != 0)
        {
            double val = gm[i][pivot];
            for(int j=0; j<=N; j++)
                gm[i][j] -= gm[pivot][j] * val;
        }
    }
}

int SolveEquation(Matrix& gm)
{
    int N = gm.size();
    BoolV used_rows(N, false);

    for (int j = 0; j < N; ++j)
    {
        int row;
        if ((row = SelectPivotElement(gm, used_rows, j)) == -1)
            return NSOL;
        SwapLines(gm, used_rows, row, j);
        row = j;
        ProcessPivotElement(gm, j);
        used_rows[row] = true;
    }
    return 1;
}

bool verifyConstraints(Matrix& guassMat, Matrix& subguassMat)
{
    for (int i = 0; i < m; i++)
        if (subguassMat[i][m] < 0)
            return false;

    for (int i = m; i <= n+m; i++)
    {
        double constrainVal = 0.0;
        for(int j = 0; j < m; j++)
            constrainVal += guassMat[i][j]*subguassMat[j][m];

        if((constrainVal - EPS) >= guassMat[i][m] )
            return false;
    }

    return true;
}

bool isTheOptimal(Matrix& guassMat, Matrix& subGuassMat, Row& optSol, double& optimum, int& type)
{
    double subOptmal = 0.0;
    for (int i = 0; i < m; i++)
        subOptmal += guassMat[n+m+1][i] * subGuassMat[i][m];

    if ((subOptmal > optimum) || (subOptmal == optimum && type==INF))
    {
        optimum = subOptmal;
        for (int i = 0; i < m; i++)
            optSol[i] = subGuassMat[i][m];

        return true;
    }
    return false;
}

pair<int, vector<double>> solve_diet_problem(Matrix guassMarix, SubSets& subsets)
{
    int type = NSOL;
    double optimum = -DBL_MAX;
    Row optimalsolution(m, -1);
    int setSize = subsets.size();

    for (int s = 0; s < setSize; s++)
    {
        Matrix subGuassMat;
        for (const auto& row : subsets[s])
            subGuassMat.push_back(guassMarix[row]);

        if (SolveEquation(subGuassMat) == 1)
        {
            int nsol = SOL;
            if (subsets[s].find(n+m) != subsets[s].end())
                nsol = INF;

            if (type==NSOL || !(type == INF && nsol == INF))
                if (verifyConstraints(guassMarix, subGuassMat))
                    if (isTheOptimal(guassMarix, subGuassMat, optimalsolution, optimum, type))
                        type = nsol;
        }
    }

    return {type, optimalsolution};
}

void PowerSets(SubSets& subsets, int row=0)
{
    static SubSets tsubsets;
    static int maxRow = n+m;

    if(row > maxRow)
    {
        tsubsets.push_back(set<int>());
        return;
    }
    PowerSets(subsets, row+1);

    int N = tsubsets.size();
    for (int i = 0; i < N; i++)
    {
        set<int> s = tsubsets[i];
        s.insert(row);
        tsubsets.push_back(s);

        if(s.size() == m)
            subsets.push_back(s);
    }
}

Matrix ReadEquation()
{
    cin >> n >> m;
    Matrix gm(n+m+2, Row(m+1, 0));

    for (int i=0; i<m; i++)
        gm[i][i] = 1;

    //get equations
    for (int i=m; i<n+m; i++)
        for(int j=0; j<m; j++)
            cin>>gm[i][j];

    //get b vector
    for (int i=m; i<n+m; i++)
        cin>>gm[i][m];

    //add infinity constrain
    for (int i=0; i<m; i++)
        gm[n+m][i] = 1;
    gm[n+m][m] = pow(10, 9);

    //get c vector
    for(int i=0; i<m; i++)
        cin>>gm[n+m+1][i];

    return gm;
}

int main()
{
    Matrix gm = ReadEquation();
    SubSets subsets;
    PowerSets(subsets);

    pair<int, vector<double>> ans = solve_diet_problem(gm, subsets);

    switch (ans.first)
    {
        case NSOL:
            cout << "No solution\n";
            break;
        case SOL:
            printf("Bounded solution\n");
            for (int i = 0; i < m; i++)
            {
                cout.precision(20);
                cout << ans.second[i] << " \n"[i + 1 == m];
            }
            break;
        case INF:
            cout << "Infinity\n";
            break;
    }

    return 0;
}
