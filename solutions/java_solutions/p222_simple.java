public class p222_simple {
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