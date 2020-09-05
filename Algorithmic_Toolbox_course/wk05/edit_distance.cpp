#include <iostream>
#include <string>
#include <vector>

/*
Problem Description
Task. The goal of this problem is to implement the algorithm for computing the edit distance between two
strings.
Input Format. Each of the two lines of the input contains a string consisting of lower case latin letters.
Constraints. The length of both strings is at least 1 and at most 100.
Output Format. Output the edit distance between the given two strings.
*/

//Branko Milosevic 2020-09-02
// Coursera Algorithmic Toolbox wk05-03

using std::string;
using std::vector;

int edit_distance(const string &str1, const string &str2)
{
  //write your code here
    int str1_size = str1.size();
    int str2_size = str2.size();

	vector<vector<int>> disp(str1_size + 1, vector<int>(str2_size + 1, 0));

	for(int y = 0; y <= str1_size; ++y) disp[y][0] = y;
    for(int z = 0; z <= str2_size; ++z) disp[0][z] = z;

	int cal_cost = 0;

	for(int i = 1; i <= str1_size; ++i)
    {
		for(int j = 1; j <= str2_size; ++j)
        {
			if(str1[i-1] == str2[j-1]) cal_cost = 0;
            else cal_cost = 1;

			disp[i][j] = std::min(std::min(disp[i-1][j],disp[i][j-1]) + 1, disp[i-1][j-1] + cal_cost);
		}

	}

	return disp[str1_size][str2_size];
}

int main() {
  string str1;
  string str2;
  std::cin >> str1 >> str2;
  std::cout << edit_distance(str1, str2) << std::endl;
  return 0;
}
