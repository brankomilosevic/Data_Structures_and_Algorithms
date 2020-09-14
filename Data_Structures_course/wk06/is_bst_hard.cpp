#include <algorithm>
#include <iostream>
#include <vector>

#define L_MIN -2147483647
#define L_MAX 2147483647

/*
Task. You are given a binary tree with integers as its keys. You need to test whether it is a correct binary search tree.
Input Format. The first line contains the number of vertices n. The vertices of the tree are numbered from 0 to n−1. Vertex 0 is the root. The next n lines contain information about vertices 0, 1, ..., n−1 in order. Each of these lines contains three integers keyi, lefti and righti — keyi is the key of the i-th vertex, lefti is the index of the left child of the i-th vertex, and righti is the index of the right child of the i-th vertex. If i doesn’t have left or right child (or both), the corresponding lefti or righti (or both) will be equal to −1.
Output Format. If the given binary tree is a correct binary search tree (see the definition in the problem description), output one word “CORRECT” (without quotes). Otherwise, output one word “INCORRECT” (without quotes).
*/

// Branko Milosevic 2020-09-10
// Coursera Data Structures wk06-03

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Node {
  int key;
  int left;
  int right;

  Node() : key(0), left(-1), right(-1) {}
  Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

void isBST_recursive(const vector<Node>& tree, int i, bool& flag, long min_key, long max_key)
{
	if (i == -1) 		return;

	if (tree[i].key < min_key || tree[i].key >= max_key)
	{
		flag = false;
		return;
	}

    if (tree[i].left >= 0)
        isBST_recursive(tree, tree[i].left, flag, min_key, tree[i].key);

    if (tree[i].right >= 0)
        isBST_recursive(tree, tree[i].right, flag, tree[i].key, max_key);

    flag = true;
    return;
}

bool IsBinarySearchTree(const vector<Node>& tree) {
  // Implement correct algorithm here
	bool flag = true;
//	long min = L_MIN;
//	long max = L_MAX;

    long min_key = std::numeric_limits<long>::min();
    long max_key = std::numeric_limits<long>::max();

	if (tree.size() < 1) return flag;

	isBST_recursive(tree, 0, flag, min_key, max_key);

	return flag;
}

int main() {
  int nodes;
  cin >> nodes;
  vector<Node> tree;
  for (int i = 0; i < nodes; ++i) {
    int key, left, right;
    cin >> key >> left >> right;
    tree.push_back(Node(key, left, right));
  }
  if (IsBinarySearchTree(tree)) {
    cout << "CORRECT" << endl;
  } else {
    cout << "INCORRECT" << endl;
  }
  return 0;
}
