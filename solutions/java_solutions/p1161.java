import java.util.Queue;
import java.util.LinkedList;

public class p1161 {
    // Maximum Level Sum of a Binary Tree - Medium
    
    // Given the root of a binary tree, the level of its root is 1, the level of its
    // children is 2, and so on.

    // Return the smallest level X such that the sum of all the values of nodes at
    // level X is maximal.

    class Solution {
        public int maxLevelSum(TreeNode root) {
            int currentLevel = 1;
            int currentLevelTotalNodes = 1;
            int nextLevelTotalNodes = 0;
            int remaining = 1;
            int sum = 0;
            int maxSum = 0;
            int maxSumLevel = 1;
            Queue<TreeNode> q = new LinkedList<>();
            q.add(root);

            while (!q.isEmpty()) {
                TreeNode next = q.poll();
                sum += next.val;
                if (next.left != null) {
                    q.add(next.left);
                    nextLevelTotalNodes++;
                }
                if (next.right != null) {
                    q.add(next.right);
                    nextLevelTotalNodes++;
                }
                remaining--;

                // commit the result of the current level, advance tracking to the next level
                if (remaining == 0) {
                    if (sum > maxSum) {
                        maxSum = sum;
                        maxSumLevel = currentLevel;
                    }

                    currentLevel++;
                    currentLevelTotalNodes = nextLevelTotalNodes;
                    remaining = currentLevelTotalNodes;
                    nextLevelTotalNodes = 0;
                    sum = 0;
                }
            }

            if (sum > maxSum) {
                maxSum = sum;
                maxSumLevel = currentLevel;
            }

            return maxSumLevel;
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