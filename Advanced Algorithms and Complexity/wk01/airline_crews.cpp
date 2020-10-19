#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <string.h>

/*
Task:
You are given the pairs of flights and associated crews that can work on those flights.
You need to assign crews to as many flights as possible and output all the assignments.

Input format:
The first line of the input contains integers 𝑛 and 𝑚 — the number of flights and the number
of crews respectively. Each of the next 𝑛 lines contains 𝑚 binary integers (0 or 1). If the 𝑗-th integer
in the 𝑖-th line is 1, then the crew number 𝑗 can work on the flight number 𝑖, and if it is 0, then it cannot.

Output Format.
Output 𝑛 integers — for each flight, output the 1-based index of the crew assigned to
this flight. If no crew is assigned to a flight, output −1 as the index of the crew corresponding to it.
All the positive indices in the output must be between 1 and 𝑚, and they must be pairwise different,
but you can output any number of −1’s. If there are several assignments with the maximum possible
number of flights having a crew assigned, output any of them.
*/

// Branko Milosevic 2020-10-13
// Coursera Advanced Algorithms and Complexity wk01-02

using std::vector;
using std::cin;
using std::cout;

#define MAXN 100
int nx,ny;
int adj_matrix[MAXN][MAXN];
int cx[MAXN],cy[MAXN];



int mk[MAXN];


int path(int u,vector<vector<bool> > adj_matrix)
{

    for(int v=0;v<ny;++v)
    {
        if(adj_matrix[u][v] && !mk[v])
        {
            mk[v] = 1;


            if(cy[v] == -1 || path(cy[v], adj_matrix))
            {
                cx[u] = v;
                cy[v] = u;
                return 1;
            }
        }
    }
    return 0;
}

int maxMatch(vector<vector<bool> > adj_matrix)
{

    int res=0;
    memset(cx, -1, sizeof(cx));
    memset(cy, -1, sizeof(cy));
    for(int i = 0; i < nx; ++i)
    {
        if(cx[i] == -1)
        {
            memset(mk, 0, sizeof(mk));
            res += path(i, adj_matrix);
        }
    }
    return res;
}

vector<vector<bool> > ReadData()
{
	int num_left, num_right;
	cin >> num_left >> num_right;
	vector<vector<bool> > adj_matrix(num_left, vector<bool>(num_right));

	for (int i = 0; i < num_left; ++i)
	  for (int j = 0; j < num_right; ++j)
      {
	    int bit;
	    cin >> bit;
	    adj_matrix[i][j] = (bit == 1);
	  }

	return adj_matrix;
}
int main() {


    vector<vector<bool> > adj_matrix = ReadData();
    nx = adj_matrix.size();
    ny = adj_matrix[0].size();
    int num= maxMatch(adj_matrix);
    for(int num=0;num<nx;++num)
    {
    	if (cx[num]+1)  cout<<cx[num]+1<<' ';
        else        	cout<<-1<<' ';
    }

    return 0;
}




/*=====================================================================================================================*/

/*
class MaxMatching {
 public:
  void Solve() {
    vector<vector<bool>> adj_matrix = ReadData();
    vector<int> matching = FindMatching(adj_matrix);
    WriteResponse(matching);
  }

 private:
  vector<vector<bool>> ReadData() {
    int num_left, num_right;
    cin >> num_left >> num_right;
    vector<vector<bool>> adj_matrix(num_left, vector<bool>(num_right));
    for (int i = 0; i < num_left; ++i)
      for (int j = 0; j < num_right; ++j) {
        int bit;
        cin >> bit;
        adj_matrix[i][j] = (bit == 1);
      }
    return adj_matrix;
  }

  void WriteResponse(const vector<int>& matching) {
    for (int i = 0; i < matching.size(); ++i) {
      if (i > 0)
        cout << " ";
      if (matching[i] == -1)
        cout << "-1";
      else
        cout << (matching[i] + 1);
    }
    cout << "\n";
  }

  vector<int> FindMatching(const vector<vector<bool>>& adj_matrix) {
    // Replace this code with an algorithm that finds the maximum
    // matching correctly in all cases.
    int num_left = adj_matrix.size();
    int num_right = adj_matrix[0].size();
    vector<int> matching(num_left, -1);
    vector<bool> busy_right(num_right, false);

    for (int i = 0; i < num_left; ++i)
      for (int j = 0; j < num_right; ++j)
        if (matching[i] == -1 && !busy_right[j] && adj_matrix[i][j]) {
          matching[i] = j;
          busy_right[j] = true;
        }
    return matching;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  MaxMatching max_matching;
  max_matching.Solve();
  return 0;
}

*/
