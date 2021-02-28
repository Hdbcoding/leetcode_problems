#include <vector>
#include <unordered_set>

using namespace std;

// Delete Nodes and Return Forest - Medium

// Given the root of a binary tree, each node in the tree has a distinct value.

// After deleting all nodes with a value in to_delete, we are left with a forest (a disjoint union of trees).

// Return the roots of the trees in the remaining forest. You may return the result in any order.

// Definition for a binary tree node.
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution
{
public:
    vector<TreeNode *> delNodes(TreeNode *root, vector<int> &to_delete)
    {
        vector<TreeNode *> result;
        unordered_set<int> deletes(to_delete.begin(), to_delete.end());
        process(root, deletes, result, true);
        return result;
    }

    void process(TreeNode *root, unordered_set<int> &to_delete, vector<TreeNode *> &result, bool isRoot)
    {
        if (root == nullptr)
            return;

        bool deleteMe = contains(to_delete, root);
        if (isRoot && !deleteMe)
            result.push_back(root);

        bool deleteLeft = contains(to_delete, root->left);
        TreeNode *left = root->left;
        if (deleteLeft)
            root->left = nullptr;
        process(left, to_delete, result, deleteMe);

        bool deleteRight = contains(to_delete, root->right);
        TreeNode *right = root->right;
        if (deleteRight)
            root->right = nullptr;
        process(right, to_delete, result, deleteMe);
    }

    bool contains(unordered_set<int> &to_delete, TreeNode *root)
    {
        if (root == nullptr)
            return true;
        return to_delete.find(root->val) != to_delete.end();
    }
};