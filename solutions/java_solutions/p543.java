public class p543 {
    // Diameter of Binary Tree - Easy

    // Given a binary tree, you need to compute the length of the diameter of the
    // tree. The diameter of a binary tree is the length of the longest path between
    // any two nodes in a tree. This path may or may not pass through the root.

    // Note: The length of path between two nodes is represented by the number of
    // edges between them.

    class Solution {
        public int diameterOfBinaryTree(TreeNode root) {
            if (root == null)
                return 0;
            return diameter(root).d - 1;
        }

        public Diameter diameter(TreeNode root) {
            Diameter result = new Diameter(0, 0);

            if (root == null)
                return result;

            Diameter dl = diameter(root.left);
            Diameter dr = diameter(root.right);

            result.h = Math.max(dl.h, dr.h) + 1;
            int md = Math.max(dl.d, dr.d);
            result.d = Math.max(dl.h + dr.h + 1, md);
            return result;
        }

        class Diameter {
            int d;
            int h;

            Diameter(int d, int h) {
                this.d = d;
                this.h = h;
            }
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