import java.util.List;
import java.util.ArrayList;
import java.util.Arrays;

public class p22 {
    // Generate Parentheses - Medium
    
    // Given n pairs of parentheses, write a function to generate all combinations
    // of well-formed parentheses.

    public static void main(String[] args) {
        Solution s = new Solution();

        printResult(s, 3);
        printResult(s, 4);
    }

    static void printResult(Solution s, int n) {
        List<String> result = s.generateParenthesis(n);
        System.out.println(n + ": " + Arrays.toString(result.toArray()));
        result = s.recursively(n);
        System.out.println(n + ": " + Arrays.toString(result.toArray()));
    }

    static class Solution {
        // using bottom up memoization
        public List<String> generateParenthesis(int n) {
            List<List<String>> memo = new ArrayList<>();
            memo.add(new ArrayList<String>());
            memo.get(0).add("");

            // f0: "",
            // f1: () <-- (f0)f0
            // f2: ()(), (()) <-- (f0)f1, (f1)f0
            // f3: ()()(), ()(()), <-- (f0)f2, (f1)f1, (f2)f0
            // (())(), (()()), ((()))
            // fn: (f0)fn-1, (f1)fn-2, ... (fn-2)f1, (fn-1)f0

            // for each set size, building up to the full size
            for (int i = 1; i <= n; i++) {
                List<String> set = new ArrayList<>();
                memo.add(set);

                // for each smaller function size
                for (int j = 0; j < i; j++) {
                    List<String> fj = memo.get(j);
                    List<String> fnmj = memo.get(i - j - 1);

                    for (String sj : fj)
                        for (String snmj : fnmj)
                            set.add("(" + sj + ")" + snmj);
                }
            }

            return memo.get(memo.size() - 1);
        }

        public List<String> recursively(int n) {
            StringBuilder sb = new StringBuilder();
            List<String> set = new ArrayList<String>();
            recurse(sb, set, 0, 0, n);
            return set;
        }

        void recurse(StringBuilder sb, List<String> set, int open, int opened, int n) {
            if (opened >= n && open <= 0) {
                // current string is complete
                set.add(sb.toString());
                return;
            }

            // can only open
            if (open <= 0 && opened < n) {
                int l = sb.length();
                sb.append('(');
                recurse(sb, set, open + 1, opened + 1, n);
                sb.setLength(l);
                return;
            }

            // can only close
            if (opened >= n && open > 0) {
                int l = sb.length();
                sb.append(')');
                recurse(sb, set, open - 1, opened, n);
                sb.setLength(l);
                return;
            }

            // could open or close
            int l = sb.length();
            sb.append('(');
            recurse(sb, set, open + 1, opened + 1, n);
            sb.setLength(l);

            sb.append(')');
            recurse(sb, set, open - 1, opened, n);
            sb.setLength(l);
        }
    }
}