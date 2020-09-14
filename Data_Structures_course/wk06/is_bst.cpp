#include <algorithm>
#include <iostream>
#include <vector>

#define L_MIN -2147483647
#define L_MAX 2147483647

/*
Task. You are given a binary tree with integers as its keys. You need to test whether it is a correct binary search tree. The definition of the binary search tree is the following: for any node of the tree, if its key is x, then for any node in its left subtree its key must be strictly less than x, and for any node in its right subtree its key must be strictly greater than x
Input Format. The first line contains the number of vertices n. The vertices of the tree are numbered from 0 to n−1. Vertex 0 is the root. The next n lines contain information about vertices 0, 1, ..., n−1 in order. Each of these lines contains three integers keyi, lefti and righti — keyi is the key of the i-th vertex, lefti is the index of the left child of the i-th vertex, and righti is the index of the right child of the i-th vertex. If i doesn’t have left or right child (or both), the corresponding lefti or righti (or both) will be equal to −1.
Output Format. If the given binary tree is a correct binary search tree (see the definition in the problem description), output one word “CORRECT” (without quotes). Otherwise, output one word “INCORRECT” (without quotes).
*/

// Branko Milosevic 2020-09-10
// Coursera Data Structures wk06-02

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Node {
  int key;
  int left;
  int right;
  int branch;

  Node() : key(0), left(-1), right(-1) {}
  Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};


bool isBST_recursive(const vector<Node> &tree, int i, long min, long max)
{
	// empty tree
	if (i == -1) return true;

	// not in min-max constraints
	if (tree[i].key <= min || tree[i].key >= max) return false;

	// check recursively
	return
		isBST_recursive(tree, tree[i].left, min, tree[i].key) && isBST_recursive(tree, tree[i].right, tree[i].key, max);
}

bool IsBinarySearchTree(const vector<Node>& tree)
{
  // Implement correct algorithm here
	long min = L_MIN;
	long max = L_MAX;

	if (tree.size() == 0)
		return true;

	return isBST_recursive(tree, 0, min, max);
}

int main()
{
  int nodes;
  cin >> nodes;
  vector<Node> tree;
  for (int i = 0; i < nodes; ++i)
  {
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
