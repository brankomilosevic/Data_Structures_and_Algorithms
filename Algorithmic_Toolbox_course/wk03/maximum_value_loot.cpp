#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <math.h>

/*
Problem Description
Task. The goal of this code problem is to implement an algorithm for the fractional knapsack problem.
Input Format. The first line of the input contains the number 𝑛 of items and the capacity 𝑊 of a knapsack.
The next 𝑛 lines define the values and weights of the items. The 𝑖-th line contains integers 𝑣𝑖 and 𝑤𝑖—the
value and the weight of 𝑖-th item, respectively.
Constraints. 1 ≤ 𝑛 ≤ 103, 0 ≤ 𝑊 ≤ 2 · 106; 0 ≤ 𝑣𝑖 ≤ 2 · 106, 0 < 𝑤𝑖 ≤ 2 · 106 for all 1 ≤ 𝑖 ≤ 𝑛. All the
numbers are integers.
Output Format. Output the maximal value of fractions of items that fit into the knapsack. The absolute
value of the difference between the answer of your program and the optimal value should be at most
10−3. To ensure this, output your answer with at least four digits after the decimal point (otherwise
your answer, while being computed correctly, can turn out to be wrong because of rounding issues).
*/

// Branko Milosevic 2020-08-31
// Coursera Algorithms Toolbox wk03-02


using std::vector;
using std::pair;
using std::greater;
using std::min;

double get_optimal_value(int capacity, vector<int> weights, vector<int> values) {
  // write your code here

  double value = 0.0;
  int num_items = weights.size();

  if (num_items < 1) return -1;

  vector<pair<double, int>> values_per_item (num_items);

  for (int i = 0; i < num_items; i++)
  {
      values_per_item[i].first = 1.0 * values[i] / weights[i];
      values_per_item[i].second = i;
  }

  sort(values_per_item.begin(), values_per_item.end(), greater<pair<double, int>>());

/*
  for (int i = 0; i < num_items; i++)
  {
     std::cout << "-----\n";
     std::cout << "Weight        : " << weights[values_per_item[i].second] << "\n";
     std::cout << "Value         : " << values[values_per_item[i].second] << "\n";
     std::cout << "Value per Item: " << values_per_item[i].first << "\t Item index: " << values_per_item[i].second << "\n";
  }
*/

  int remain_capacity = capacity;

  for (int i = 0; i < num_items && remain_capacity > 0; i++)
  {
    int amount = min(weights[values_per_item[i].second], remain_capacity);

    value += amount * values_per_item[i].first;
    remain_capacity -= weights[values_per_item[i].second];

/*
    std::cout << "\n amount to add  : " << amount;
    std::cout << "\n remain_capacity: " << remain_capacity;
    std::cout << "\n\n";
*/
  }

  return value;
}

/*
	int n, SizeOfKnapSack;

	cin >> n >> SizeOfKnapSack;

	vector<pair<int, int>> Value_Wigth(n);

	vector<pair<double,int>> ValuePerUnit(n);

	for (int i = 0; i < n; i++) {

		cin >> Value_Wigth[i].first >> Value_Wigth[i].second;

		ValuePerUnit[i].first = 1.0 * Value_Wigth[i].first / Value_Wigth[i].second;

		ValuePerUnit[i].second = Value_Wigth[i].second;

	}

	sort(ValuePerUnit.begin(), ValuePerUnit.end(),greater<pair<double,int>>());

	double Res = 0;

	for (int i = 0; i < ValuePerUnit.size() && SizeOfKnapSack>0; i++) {

		Res += min(ValuePerUnit[i].second, SizeOfKnapSack)*ValuePerUnit[i].first;

		SizeOfKnapSack -= min(ValuePerUnit[i].second, SizeOfKnapSack);

	}

	cout << fixed << setprecision(4) << Res << endl;
*/

int main() {
  int n;
  int capacity;
  std::cin >> n >> capacity;
  vector<int> values(n);
  vector<int> weights(n);

  for (int i = 0; i < n; i++) {
    std::cin >> values[i] >> weights[i];
  }

  double optimal_value = get_optimal_value(capacity, weights, values);

  std::cout.precision(10);
  std::cout << optimal_value << std::endl;
  return 0;
}
