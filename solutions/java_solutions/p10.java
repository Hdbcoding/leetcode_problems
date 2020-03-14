public class p10 {
    // Regular Expression Matching - hard
    // Given an input string (s) and a pattern (p), implement regular expression
    // matching with support for '.' and '*'.
    // '.' Matches any single character.
    // '*' Matches zero or more of the preceding element.
    // The matching should cover the entire input string (not partial).

    // Note:

    // s could be empty and contains only lowercase letters a-z.
    // p could be empty and contains only lowercase letters a-z, and characters like
    // . or *.

    public static void main(String[] args) {
        Solution s = new Solution();
        // System.out.println("aa, a: " + s.isMatch("aa", "a"));
        System.out.println("aaaaaaaaaaaaaaa, a*: " + s.isMatch("aa", "a*"));
    }

    static class Solution {
        public boolean isMatch(String s, String p) {
            if (p == null || p.isEmpty())
                return s == null || s.isEmpty();
            char[] sc = s.toCharArray();
            char[] pc = p.toCharArray();

            boolean[][] memo = new boolean[sc.length + 1][pc.length + 1];
            // base case - nothing compared
            memo[sc.length][pc.length] = true;

            for (int i = sc.length; i >= 0; i--) {
                for (int j = pc.length - 1; j >= 0; j--) {
                    boolean repeatedChar = j + 1 < pc.length && pc[j + 1] == '*';

                    // if the current pattern character repeats
                    // and the rest of the pattern matches this part of the string
                    // then continue
                    if (repeatedChar && memo[i][j + 2]) {
                        memo[i][j] = memo[i][j + 2];
                        continue;
                    }

                    // do chars i and j match?
                    boolean charMatched = i < sc.length && (pc[j] == sc[i] || pc[j] == '.');
                    if (!charMatched)
                        continue;

                    // this section of the pattern worked if this char matched
                    // and the rest of the string matched the rest of the pattern
                    // if we have a repeating pattern here, we check if the rest of
                    // the string matched this part of the pattern
                    int nextJ = repeatedChar ? j : j + 1;
                    memo[i][j] = memo[i + 1][nextJ];
                }
            }

            return memo[0][0];
        }
    }
}