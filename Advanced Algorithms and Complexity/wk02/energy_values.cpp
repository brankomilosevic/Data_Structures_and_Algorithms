
#include <cmath>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <iomanip>
using namespace std;

const double EPS = 1e-6;
const int PRECISION = 20;

typedef vector<double> Row;
typedef vector<Row> Matrix;
typedef vector<bool> BoolV;

// Branko Milosevic 2020-10-19
// Coursera Advanced Algorithms and Complexity wk02-01
// ... "aaaa, with a little help, from my friends"

Matrix ReadEquation()
{
    int N;
    cin >> N;

    Matrix gm(N, Row(N + 1));

    for (int i = 0; i < N; ++i)
        for (int j = 0; j <= N; ++j)
            cin >> gm[i][j];

    return gm;
}

int SelectPivotElement(const Matrix &a, BoolV &used_rows, int col)
{
    int i = 0;
    while (used_rows[i] || a[i][col] == 0) i++;
    return i;
}

void SwapLines(Matrix &a, vector <bool> &used_rows, int i, int j)
{
    swap(a[i], a[j]);
    swap(used_rows[i], used_rows[j]);
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
            for(int j = 0; j <= N; j++)
                gm[i][j] -= gm[pivot][j] * val;
        }

    }
}

void SolveEquation(Matrix& gm)
{
    int sz = gm.size();

    BoolV used_rows(sz, false);
    for (int j = 0; j < sz; ++j)
    {
        int i = SelectPivotElement(gm, used_rows, j);
        SwapLines(gm, used_rows, i, j);
        i = j;
        ProcessPivotElement(gm, j);
        used_rows[i] = true;
    }

}

void PrintColumn(const Matrix &gm)
{
    int N = gm.size();

    std::cout << std::fixed << std::setprecision (PRECISION);

    for (int i = 0; i < N; ++i)
        std::cout << gm[i][N] << '\n';
}

int main()
{
    Matrix gm = ReadEquation();
    SolveEquation(gm);
    PrintColumn(gm);
    return 0;
}

