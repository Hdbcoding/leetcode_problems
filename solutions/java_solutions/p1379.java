import java.util.ArrayList;
import java.util.Collections;

public class p1379 {
    // Find a Corresponding Node of a Binary Tree in a Clone of That Tree - Medium
    // Given two binary trees original and cloned and given a reference to a node
    // target in the original tree.

    // The cloned tree is a copy of the original tree.

    // Return a reference to the same node in the cloned tree.

    // Note that you are not allowed to change any of the two trees or the target
    // node and the answer must be a reference to a node in the cloned tree.

    // Follow up: Solve the problem if repeated values on the tree are allowed.

    class Solution {
        public final TreeNode getTargetCopy(final TreeNode original, final TreeNode cloned, final TreeNode target) {
            ArrayList<Boolean> steps = new ArrayList<>();

            findTarget(original, target, steps);
            Collections.reverse(steps);

            TreeNode c = cloned;
            for (Boolean goLeft : steps) {
                if (goLeft)
                    c = c.left;
                else
                    c = c.right;
            }

            return c;
        }

        boolean findTarget(TreeNode original, TreeNode target, ArrayList<Boolean> steps) {
            if (original == null)
                return false;
            if (original == target)
                return true;

            if (findTarget(original.left, target, steps)) {
                steps.add(true);
                return true;
            } else if (findTarget(original.right, target, steps)) {
                steps.add(false);
                return true;
            }
            return false;
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