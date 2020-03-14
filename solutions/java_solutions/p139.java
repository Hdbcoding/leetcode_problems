import java.util.List;
import java.util.HashSet;
import java.util.Arrays;

public class p139 {
    // Word Break - Medium
    // Given a non-empty string s and a dictionary wordDict containing a list of
    // non-empty words, determine if s can be segmented into a space-separated
    // sequence of one or more dictionary words.

    // Note:

    // The same word in the dictionary may be reused multiple times in the
    // segmentation.
    // You may assume the dictionary does not contain duplicate words.

    public static void main(String[] args) {
        Solution s = new Solution();

        System.out.println(s.wordBreak("leetcode", Arrays.asList("leet", "code")));
    }

    static class Solution {
        public boolean wordBreak(String s, List<String> wordDict) {
            HashSet<String> d = new HashSet<>(wordDict);
            char[] sc = s.toCharArray();
            int max = 0;
            int min = Integer.MAX_VALUE;
            for (String w : d) {
                max = Math.max(w.length(), max);
                min = Math.min(w.length(), min);
            }
            Boolean[] memo = new Boolean[s.length()];
            return recursively(sc, 0, min, max, d, memo);
        }

        public Boolean recursively(char[] sc, int start, int min, int max, HashSet<String> dict, Boolean[] memo) {
            if (start == sc.length)
                return true;

            if (memo[start] != null)
                return memo[start];

            StringBuilder sb = new StringBuilder(max);
            for (int i = start; i < sc.length; i++) {
                sb.append(sc[i]);
                if (sb.length() > max)
                    break;
                if (sb.length() < min)
                    continue;
                if (dict.contains(sb.toString()) && recursively(sc, i + 1, min, max, dict, memo))
                    return memo[start] = true;
            }
            return memo[start] = false;
        }
    }
}