import java.util.List;
import java.util.HashSet;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;

public class p472 {
    // Concatenated words - Hard
    
    // Given a list of words (without duplicates), please write a program that
    // returns all concatenated words in the given list of words.
    // A concatenated word is defined as a string that is comprised entirely of at
    // least two shorter words in the given array.

    public static void main(String[] args) {
        Solution s = new Solution();
        String[] data = new String[] { "cat", "cats", "catsdogcats", "dog",
                "dogcatsdog", "hippopotamuses", "rat", "ratcatdogcat" };
        List<String> result = s.findAllConcatenatedWordsInADict(data);
        System.out.println(Arrays.toString(result.toArray()));
    }

    static class Solution {
        public List<String> findAllConcatenatedWordsInADict(String[] words) {
            Arrays.sort(words, new LengthComparator());
            int min = words[0].length();
            int max = words[0].length();

            List<String> result = new ArrayList<>();
            HashSet<String> dict = new HashSet<>();
            HashSet<String> memo = new HashSet<>();

            for (String s : words) {
                if (isConcatenated(s, min, max, dict, memo)) {
                    result.add(s);
                }
                dict.add(s);
                max = s.length();
            }

            return new ArrayList<>(result);
        }

        boolean isConcatenated(String s, int min, int max, HashSet<String> dict, HashSet<String> memo) {
            if (dict.contains(s))
                return true;
            if (memo.contains(s))
                return true;

            for (int i = Math.max(1, min); i < Math.min(s.length(), max + 1); i++) {
                String left = s.substring(0, i);
                String right = s.substring(i);
                if (dict.contains(left)) {
                    if (dict.contains(right))
                        return true;
                    if (isConcatenated(right, min, max, dict, memo)) {
                        memo.add(right);
                        return true;
                    }
                }
            }

            return false;
        }

        class LengthComparator implements Comparator<String> {
            @Override
            public int compare(String a, String b) {
                return a.length() - b.length();
            }
        }
    }
}