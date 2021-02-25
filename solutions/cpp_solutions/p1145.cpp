
// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// Binary Tree Coloring Game - Medium

// Two players play a turn based game on a binary tree.  
// We are given the root of this binary tree, and the number of nodes n in the tree.  n is odd, and each node has a distinct value from 1 to n.

// Initially, the first player names a value x with 1 <= x <= n, and the second player names a value y with 1 <= y <= n and y != x.  
// The first player colors the node with value x red, and the second player colors the node with value y blue.

// Then, the players take turns starting with the first player.  In each turn, that player chooses a node of their color 
// (red if player 1, blue if player 2) and colors an uncolored neighbor of the chosen node (either the left child, right child, or parent of the chosen node.)

// If (and only if) a player cannot choose such a node in this way, they must pass their turn.  
// If both players pass their turn, the game ends, and the winner is the player that colored more nodes.

// You are the second player.  If it is possible to choose such a y to ensure you win the game, return true.  
// If it is not possible, return false.

class Solution {
public:
    bool btreeGameWinningMove(TreeNode* root, int n, int x) {
        // goal - find where x is in the tree
        // find the size of x's left child, right child, and parent
        // return true if the biggest is larger than the other two combined, + 1
        
        int totalSize = size(root);
        
        TreeNode* xNode = find(root, x);
        
        int xLeft = size(xNode->left);
        int xRight = size(xNode->right);
        int xParent = totalSize - xLeft - xRight - 1;
        
        if (xLeft > xRight + xParent) return true;
        if (xRight > xLeft + xParent) return true;
        if (xParent > xRight + xLeft) return true;
        return false;
    }
    
    int size(TreeNode *root)
    {
        if (root == nullptr) return 0;
        return 1 + size(root->left) + size(root->right);
    }
    
    TreeNode* find(TreeNode *root, int x)
    {
        if (root == nullptr) return nullptr;
        if (root->val == x) return root;
        
        TreeNode* xNode = find(root->left, x);
        if (xNode == nullptr)
            xNode = find(root->right, x);
        return xNode;
    }
};