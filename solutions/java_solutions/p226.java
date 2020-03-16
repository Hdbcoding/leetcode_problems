public class p226 {
    // Invert Binary Tree - Easy

    // Invert a binary tree.
    // Google: 90% of our engineers use the software you wrote (Homebrew), 
    //   but you can’t invert a binary tree on a whiteboard so f*** off.
    // - Max Howell

    class Solution {
        public TreeNode invertTree(TreeNode root) {
            if (root == null)
                return null;

            invertTree(root.left);
            invertTree(root.right);

            TreeNode temp = root.left;
            root.left = root.right;
            root.right = temp;

            return root;
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