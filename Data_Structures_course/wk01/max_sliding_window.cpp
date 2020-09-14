#include <iostream>
#include <vector>
#include <deque>

/*
Problem Description
Given a sequence a1,...,an of integers and an integer m ≤ n, find the maximum among{ai,...,ai+m−1}for every 1 ≤ i ≤ n−m + 1

Input Format.
The first line contains an integer n, the second line contains n integers a1,...,an separated by spaces,
the third line contains an integer m.

Constraints.
1 ≤ n ≤ 105, 1 ≤ m ≤ n, 0 ≤ ai ≤ 105 for all 1 ≤ i ≤ n. Output Format.

Output max{ai,...,ai+m−1} for every 1 ≤ i ≤ n−m + 1.
*/

// Branko Milosevic 2020-09-04
// Coursera Data Structures wk01-05

using std::cin;
using std::cout;
using std::vector;
using std::max;
using std::deque;

class Solution
{
  public:
    vector<int> maxSlidingWindow(const vector<int> & nums, int m) {
        vector<int> result;
        deque<int> indx;

        int id = 0;
        indx.push_front(id);
        id++;

        for (; id < m ; id++)
        {
            if (nums[id] >= nums[indx.front()])
                indx.push_front(id);
            else
            {
                while(nums[indx.back()] < nums[id]) indx.pop_back();
                indx.push_back(id);
            }
        }

        result.push_back(nums[indx.front()]);

        while ((size_t)id < nums.size())
        {
            while (id-indx.front() >= 3) indx.pop_front();

            if (nums[id] >= nums[indx.front()])
                indx.push_front(id);
            else
            {
                while(nums[indx.back()] < nums[id]) indx.pop_back();
                indx.push_back(id);
            }
            id++;
            result.push_back(nums[indx.front()]);
        }

        return result;
    }
};

void max_sliding_window(vector<int> &A, int m)
{
    Solution solution;

    for (auto x : solution.maxSlidingWindow(A, m)) std::cout << x << " ";
    std::cout << '\n';
}

int main() {
    int n = 0;
    cin >> n;

    vector<int> A(n);

    for (size_t i = 0; i < n; ++i)
        cin >> A.at(i);

    int m = 0;
    cin >> m;

    // max_sliding_window_naive(A, m);
    max_sliding_window(A, m);

    return 0;
}
