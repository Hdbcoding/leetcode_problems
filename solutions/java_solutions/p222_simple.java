public class p222_simple {
    // Count Complete Tree Nodes - Medium

    // Given a complete binary tree, count the number of nodes.
    // Note:
    // Definition of a complete binary tree from Wikipedia:
    // In a complete binary tree every level, except possibly the last, is
    // completely filled, and all nodes in the last level are as far left as
    // possible. It can have between 1 and 2h nodes inclusive at the last level h.
    class Solution {
        public int countNodes(TreeNode root) {
            if (root == null)
                return 0;

            return countNodes(root.left) + countNodes(root.right) + 1;
        }
    }

    class TreeNode {
        int val;
        TreeNode left;
        TreeNode right;

        TreeNode(int x) {
            val = x;
        }
    }
}