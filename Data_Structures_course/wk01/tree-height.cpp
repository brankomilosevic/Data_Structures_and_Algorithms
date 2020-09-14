#include <algorithm>
#include <iostream>
#include <vector>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

/*
Problem Description Task.
You are given a description of a rooted tree.
Your task is to compute and output its height.
Recall that the height of a (rooted) tree is the maximum depth of a node, or the maximum distance from a leaf to the root.
You are given an arbitrary tree, not necessarily a binary tree.
Input Format.
The first line contains the number of nodes n.
The second line contains n integer numbers from −1 to n−1 — parents of nodes.
If the i-th one of them (0 ≤ i ≤ n−1) is −1, node i is the root, otherwise it’s 0-based index of the parent of i-th node.
It is guaranteed that there is exactly one root. It is guaranteed that the input represents a tree.
*/

// Branko Milosevic 2020-09-04
// Coursera Data Structures wk01-02

std::vector<std::vector<int>> adj (1000);

int dfs(int r){
    if(adj[r].size() == 0) return 1;
    else
    {
        int maxv = 0;
        for(int i = 0;i < adj[r].size(); i++)
        {
            int j = adj[r][i];
            maxv = std::max(maxv, dfs(j));
        }
        return 1 + maxv;
    }
}

int main()
{
	// std::ios::sync_with_stdio(0);
	long long i,j,k,t,q,m,l,n;


    std::cin >> n;

    int tree[n];
    int r;

    for(int i = 0; i < n; i++)
    {
        std::cin >> tree[i];

        if(tree[i] == -1)
            r = i;
        else
            adj[tree[i]].push_back(i);
    }

    std::cout << dfs(r) << '\n';
}

/* === some strange template from Coursera === */
/*

class Node;

class Node {
public:
    int key;
    Node *parent;
    std::vector<Node *> children;

    Node() {
      this->parent = NULL;
    }

    void setParent(Node *theParent) {
      parent = theParent;
      parent->children.push_back(this);
    }
};


int main_with_large_stack_space() {
  std::ios_base::sync_with_stdio(0);
  int n;
  std::cin >> n;

  std::vector<Node> nodes;
  nodes.resize(n);
  for (int child_index = 0; child_index < n; child_index++) {
    int parent_index;
    std::cin >> parent_index;
    if (parent_index >= 0)
      nodes[child_index].setParent(&nodes[parent_index]);
    nodes[child_index].key = child_index;
  }

  // Replace this code with a faster implementation
  int maxHeight = 0;
  for (int leaf_index = 0; leaf_index < n; leaf_index++) {
    int height = 0;
    for (Node *v = &nodes[leaf_index]; v != NULL; v = v->parent)
      height++;
    maxHeight = std::max(maxHeight, height);
  }

  std::cout << maxHeight << std::endl;
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

*/
