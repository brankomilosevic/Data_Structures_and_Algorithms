#include <iostream>
#include <vector>
/*

Problem Introduction
You are going to travel to another city that is located 𝑑 miles away from your home city. Your car can travel
at most 𝑚 miles on a full tank and you start with a full tank. Along your way, there are gas stations at
distances stop1, stop2, . . . , stop𝑛 from your home city. What is the minimum number of refills needed?
Problem Description
Input Format. The first line contains an integer 𝑑. The second line contains an integer 𝑚. The third line
specifies an integer 𝑛. Finally, the last line contains integers stop1, stop2, . . . , stop𝑛.
Output Format. Assuming that the distance between the cities is 𝑑 miles, a car can travel at most 𝑚 miles
on a full tank, and there are gas stations at distances stop1, stop2, . . . , stop𝑛 along the way, output the
minimum number of refills needed. Assume that the car starts with a full tank. If it is not possible to
reach the destination, output −1.
Constraints. 1 ≤ 𝑑 ≤ 105. 1 ≤ 𝑚 ≤ 400. 1 ≤ 𝑛 ≤ 300. 0 < stop1 < stop2 < · · · < stop𝑛 < 𝑑.
*/

// Branko Milosevic 2020-08-31
// Coursera Algorithms Toolbox wk03-03

using std::cin;
using std::cout;
using std::vector;
using std::max;

int compute_min_refills(int dist, int tank, vector<int> & stops) {
    // write your code here

    int num_stops = stops.size();
    int travel = tank;
    int last_stop = 0;
    int refils = 0;

    for (int i = 0; (i < num_stops) && (travel < dist); i++)
    {
        int j = 0;
        while (travel > stops[j]) j++;
        last_stop = stops[j-1];
        travel = last_stop + tank;
        refils++;
    }

    if (travel >= dist)
        return refils;
    else
        return -1;
}


int main() {
    int d = 0;
    cin >> d;
    int m = 0;
    cin >> m;
    int n = 0;
    cin >> n;

    vector<int> stops(n);
    for (size_t i = 0; i < n; ++i)
        cin >> stops.at(i);

    cout << compute_min_refills(d, m, stops) << "\n";

    return 0;
}
