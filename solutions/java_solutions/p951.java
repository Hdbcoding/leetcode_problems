import java.util.List;
import java.util.ArrayList;

public class p951 {
    // Flip Equivalent Binary Trees - Medium

    // For a binary tree T, we can define a flip operation as follows: choose any
    // node, and swap the left and right child subtrees.

    // A binary tree X is flip equivalent to a binary tree Y if and only if we can
    // make X equal to Y after some number of flip operations.

    // Write a function that determines whether two binary trees are flip
    // equivalent. The trees are given by root nodes root1 and root2.

    static class Solution {
        public boolean flipEquiv(TreeNode root1, TreeNode root2) {
            return canonicalTraversal(root1, root2);
        }

        boolean recursive(TreeNode root1, TreeNode root2) {
            if (root1 == null && root2 == null)
                return true;
            if (root1 == null || root2 == null)
                return false;
            if (root1.val != root2.val)
                return false;

            return flipEquiv(root1.left, root2.left) && flipEquiv(root1.right, root2.right)
                    || flipEquiv(root1.right, root2.left) && flipEquiv(root1.left, root2.right);
        }

        boolean canonicalTraversal(TreeNode root1, TreeNode root2) {
            List<Integer> vals = new ArrayList<>();
            populateValues(root1, vals);
            return verifyValues(root2, vals) && idx == vals.size();
        }

        void populateValues(TreeNode n, List<Integer> vals) {
            if (n == null)
                return;

            vals.add(n.val);
            TreeNode left = smaller(n.left, n.right);
            TreeNode right = larger(n.left, n.right);
            populateValues(left, vals);
            populateValues(right, vals);
        }

        int idx = 0;

        boolean verifyValues(TreeNode n, List<Integer> vals) {
            if (n == null)
                return true;
            if (idx == vals.size())
                return false;
            if (vals.get(idx++) != n.val)
                return false;

            TreeNode left = smaller(n.left, n.right);
            TreeNode right = larger(n.left, n.right);
            return verifyValues(left, vals) && verifyValues(right, vals);
        }

        TreeNode smaller(TreeNode a, TreeNode b) {
            if (a == null)
                return b;
            if (b == null)
                return a;
            return a.val > b.val ? b : a;
        }

        TreeNode larger(TreeNode a, TreeNode b) {
            if (a == null)
                return b;
            if (b == null)
                return a;
            return a.val > b.val ? a : b;
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