#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

/*
Task.
You are given a rooted binary tree. Build and output its in-order, pre-order and post-order traversals.

Input Format.
The first line contains the number of vertices n.
The vertices of the tree are numbered from 0 to n−1. Vertex 0 is the root.
The next n lines contain information about vertices 0, 1, ..., n−1 in order.
Each of these lines contains three integers keyi, lefti and righti — keyi is the key of the i-th vertex,
lefti is the index of the left child of the i-th vertex, and righti is the index of the right child of the i-th vertex.
If i doesn’t have left or right child (or both), the corresponding lefti or righti (or both) will be equal to −1.

Constraints.
1 ≤ n ≤ 105; 0 ≤ keyi ≤ 109; −1 ≤ lefti,righti ≤ n−1.
It is guaranteed that the input represents a valid binary tree.
In particular, if lefti ̸= −1 and righti ̸= −1, then lefti ̸= righti. Also, a vertex cannot be a child of two different vertices.
Also, each vertex is a descendant of the root vertex.

Output Format.
The first line should contain the keys of the vertices in the in-order traversal of the tree.
The second line should contain the keys of the vertices in the pre-order traversal of the tree.
The third line should contain the keys of the vertices in the post-order traversal of the tree.
*/

// Branko Milosevic 2020-09-09
// Coursera Data Structures wk06-01

using std::vector;
using std::ios_base;
using std::cin;
using std::cout;
using std::stack;

class TreeOrders {
  int n;
  int root;
  vector <int> key;
  vector <int> left;
  vector <int> right;
  vector <bool> isRoot;

public:
  void read()
  {
    cin >> n;
    key.resize(n);
    left.resize(n);
    right.resize(n);
    isRoot.resize(n);

    for (int i = 0; i < n; i++)
    {
      cin >> key[i] >> left[i] >> right[i];
      if (left[i] != -1)  isRoot[i] = 1;
      if (right[i] != -1) isRoot[i] = 1;
    }

    std::sort(isRoot.begin(), isRoot.end());
    root = isRoot[0];
  }

  void iter_inorder(int root, vector<int> &r)
  {
    stack<int> st;
    int x = root;
    while (1)
    {
      while (x != -1)
      {
        st.push(x);
        x = left[x];
      }

      if (st.empty()) break;

      x = st.top();
      r.push_back(key[x]);
      st.pop();
      x = right[x];
    }
  }
  void recur_inorder(int root, vector<int> &r)
  {
    if (left[root] != -1)
        recur_inorder(left[root], r);
    r.push_back(key[root]);

    if (right[root] != -1)
        recur_inorder(right[root], r);
  }

  void iter_preorder(int root, vector<int> &r)
  {
    stack<int> st;
    int x = root;
    while (1)
    {
      while (x != -1)
      {
        r.push_back(key[x]);
        if (right[x] != -1)
          st.push(right[x]);
        x = left[x];
      }
      if (st.empty()) break;

      x = st.top();
      st.pop();
    }
  }

  void recur_preorder(int root, vector<int> &r)
  {
    r.push_back(key[root]);

    if (left[root] != -1)
      recur_preorder(left[root], r);

    if (right[root] != -1)
      recur_preorder(right[root], r);
  }

  void iter_postorder(int root, vector<int> &r)
  {
    stack<int> st;
    int x = root;
    if (x != -1) st.push(x);

    while (!st.empty())
    {
      if (left[st.top()] != x && right[st.top()] != x)
      {
        while ((x = st.top()) != -1)
        {
          if (left[x] != -1)
          {
            if (right[x] != -1)
              st.push(right[x]);
            st.push(left[x]);
          }
          else
            st.push(right[x]);
        }
        st.pop();
      }
      x = st.top();
      r.push_back(key[x]);
      st.pop();
    }
  }

  void recur_postorder(int root, vector<int> &r)
  {
    if (left[root] != -1)
      recur_postorder(left[root], r);

    if (right[root] != -1)
      recur_postorder(right[root], r);

    r.push_back(key[root]);
  }

  vector <int> in_order() {
    vector<int> result;
    // Finish the implementation
    // You may need to add a new recursive method to do that
    // recur_inorder(root, result);
    iter_inorder(root, result);
    return result;
  }

  vector <int> pre_order() {
    vector<int> result;
    // Finish the implementation
    // You may need to add a new recursive method to do that
     // recur_preorder(root, result);
    iter_preorder(root, result);
    return result;
  }

  vector <int> post_order() {
    vector<int> result;
    // Finish the implementation
    // You may need to add a new recursive method to do that
    iter_postorder(root, result);
    return result;
  }
};

void print(vector <int> a) {
  for (size_t i = 0; i < a.size(); i++) {
    if (i > 0) {
      cout << ' ';
    }
    cout << a[i];
  }
  cout << '\n';
}

int main_with_large_stack_space() {
  ios_base::sync_with_stdio(0);
  TreeOrders t;
  t.read();
  print(t.in_order());
  print(t.pre_order());
  print(t.post_order());
  return 0;
}

int main (int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
  // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0)
  {
      if (rl.rlim_cur < kStackSize)
      {
          rl.rlim_cur = kStackSize;
          result = setrlimit(RLIMIT_STACK, &rl);
          if (result != 0)
          {
              std::cerr << "setrlimit returned result = " << result << std::endl;
          }
      }
  }
#endif

  return main_with_large_stack_space();
}

