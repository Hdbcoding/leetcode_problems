
public class p222_fancy {
    // Given a complete binary tree, count the number of nodes.
    // Note:
    // Definition of a complete binary tree from Wikipedia:
    // In a complete binary tree every level, except possibly the last, is
    // completely filled, and all nodes in the last level are as far left as
    // possible. It can have between 1 and 2h nodes inclusive at the last level h.
    class Solution {
        int countNodes(TreeNode root) {
            if (root == null)
                return 0;

            // identify (depth - 1) of the tree
            int d = getDepth(root);
            if (d == 0)
                return 1;

            // identify possible number of nodes in the last layer
            int numNodesAboveLastLevel = (int) Math.pow(2, d) - 1;
            int left = 1;
            int right = numNodesAboveLastLevel;
            int m;
            // binary search across the nodes
            while (left <= right) {
                m = left + (right - left) / 2;
                // if this node exists, search in the right half
                if (exists(m, d, numNodesAboveLastLevel, root))
                    left = m + 1;
                // else, search in the left half
                else
                    right = m - 1;
            }

            return numNodesAboveLastLevel + left;
        }

        int getDepth(TreeNode root) {
            int d = 0;
            while (root.left != null) {
                root = root.left;
                d++;
            }
            return d;
        }

        boolean exists(int m, int d, int right, TreeNode node) {
            int left = 0;
            int p;
            // traverse down to the lowest level of the tree
            for (int i = 0; i < d; i++) {
                p = left + (right - left) / 2;
                // given a desired node m, at each node that we traverse through m will be in
                // the left or right subtree
                if (m <= p) {
                    node = node.left;
                    right = p;
                } else {
                    node = node.right;
                    left = p + 1;
                }
            }
            return node != null;
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
