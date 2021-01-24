#include <unordered_map>
using namespace std;
// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


// Maximum Level Sum of a Binary Tree - Medium

// Given the root of a binary tree, the level of its root is 1, the level of its children is 2, and so on.

// Return the smallest level x such that the sum of all the values of nodes at level x is maximal.

class Solution {
    void count(TreeNode* root, int level, unordered_map<int,int> &levelSums)
    {
        if (root == nullptr) return;
        levelSums[level] += root->val;
        auto it = levelSums.find(level);
        count(root->left, level + 1, levelSums);
        count(root->right, level + 1, levelSums);
    }
    
public:
    int maxLevelSum(TreeNode* root) {
        unordered_map<int, int> levelSums;
        
        count(root, 1, levelSums);
        
        int sum = levelSums.begin()->second;
        int level = levelSums.begin()->first;
        for (auto &pair : levelSums)
        {
            if (pair.second > sum)
            {
                sum = pair.second;
                level = pair.first;
            }
            // technically leetcode is happy with a pair.second>= sum, and no equality check
            // but I think they're missing test cases that would result in 
            // an unordered map with increasing levels but flat level sums
            else if (pair.second == sum)
            {
                level = min(level, pair.first);
            }
        }
        
        return level;
    }
};