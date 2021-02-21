#include <vector>

using namespace std;

// All Possible Full Binary Trees - Medium

// A full binary tree is a binary tree where each node has exactly 0 or 2 children.

// Return a list of all possible full binary trees with N nodes. Each element of the answer is the root node of one possible tree.

// Each node of each tree in the answer must have node.val = 0.

// You may return the final list of trees in any order.

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    vector<TreeNode*> allPossibleFBT(int N) {
        if (N % 2 == 0) return {};
        vector<vector<TreeNode*>> dp(N + 1, vector<TreeNode*>());
        dp[0] = {nullptr};
        dp[1] = {new TreeNode()};
        // for each root size
        for (int i = 3; i <= N; i += 2)
        {
            // for each valid child size to this root
            // for 5, this would be:
            // 1,3;3,1
            // for 7, this would be:
            // 1,5;3,3;5,1
            
            for (int j = 1; j < i; j += 2)
            {
                int left = j;
                int right = i - j - 1;
                
                for (TreeNode *l : dp[left])
                {
                    for (TreeNode *r : dp[right])
                    {
                        dp[i].push_back(new TreeNode(0, l, r));
                    }
                }
            }
            
        }
        
        return dp[N];
    }
};