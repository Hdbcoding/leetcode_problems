public class p904 {
    // In a row of trees, the i-th tree produces fruit with type tree[i].

    // You start at any tree of your choice, then repeatedly perform the following
    // steps:

    // Add one piece of fruit from this tree to your baskets. If you cannot, stop.
    // Move to the next tree to the right of the current tree. If there is no tree
    // to the right, stop.
    // Note that you do not have any choice after the initial choice of starting
    // tree: you must perform step 1, then step 2, then back to step 1, then step 2,
    // and so on until you stop.

    // You have two baskets, and each basket can carry any quantity of fruit, but
    // you want each basket to only carry one type of fruit each.

    // What is the total amount of fruit you can collect with this procedure?

    // Note from me: each basket can only hold one type of fruit total
    // i.e., longest sequence containing only two elements
    // i had a lot of trouble understanding this because I thought it meant
    // that each basket can have only one of each type of fruit
    // i.e., longest sequence containing no element more than twice
    // i think that second problem can also be solved with a sliding window, but 
    //  we need a collection of the locations of each fruit in our set

    class Solution {
        public int totalFruit(int[] tree) {
            int max = 0;
            int startOfGroup = 0;
            int startOfLatest = 0;
            int v1 = tree[0];
            int v2 = -1;

            int t;
            for (int i = 1; i < tree.length; i++) {
                t = tree[i];
                // nothing to do if we haven't found v2 yet
                if (t == v1 && v2 == -1)
                    continue;
                if (t == v1) {
                    // if we found a v1 again, flip the pointers so that v2 is always the latest
                    // variable in the pair
                    v1 = v2;
                    v2 = t;
                    startOfLatest = i;
                    continue;
                }
                // nothing to do here
                if (t == v2)
                    continue;

                // haven't established v2 yet, so do that
                if (v2 == -1) {
                    v2 = t;
                    startOfLatest = i;
                    continue;
                }

                // found a new variable that doesn't match v1 or v2
                // flip v1, v2, and t
                v1 = v2;
                v2 = t;
                max = Math.max(i - startOfGroup, max);
                startOfGroup = startOfLatest;
                startOfLatest = i;
            }
            max = Math.max(tree.length - startOfGroup, max);

            return max;
        }
    }
}