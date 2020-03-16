public class p124 {
    // Binary Tree Maximum Path Sum - Hard

    // Given a non-empty binary tree, find the maximum path sum.

    // For this problem, a path is defined as any sequence of nodes from some
    // starting node to any node in the tree along the parent-child connections. The
    // path must contain at least one node and does not need to go through the root.

    class Solution {
        int maxSum = Integer.MIN_VALUE;

        public int maxPathSum(TreeNode root) {
            recurse(root);
            return maxSum;
        }

        public int recurse(TreeNode node) {
            if (node == null)
                return 0;

            // get the best straight up path through the left and right children
            int left = Math.max(recurse(node.left), 0);
            int right = Math.max(recurse(node.right), 0);

            // check the best path from the bottom that goes from the left, through this
            // node, and back down the right
            int upDown = left + node.val + right;

            // the biggest path that could be made at any node is the updown path, so see if
            // it's bigger than the max so far
            maxSum = Math.max(maxSum, upDown);

            // return the best path from the bottom that goes through this node
            int max = Math.max(left, right);
            return max + node.val;
        }
    }

    public class TreeNode {
        int val;
        TreeNode left;
        TreeNode right;

        TreeNode(int x) {
            val = x;
        }
    }
}