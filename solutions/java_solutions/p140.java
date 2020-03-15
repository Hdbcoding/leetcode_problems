import java.util.List;
import java.util.HashSet;
import java.util.HashMap;
import java.util.ArrayList;

public class p140 {
    // Word Beak II- Hard

    // Given a non-empty string s and a dictionary wordDict containing a list of
    // non-empty words, add spaces in s to construct a sentence where each word is a
    // valid dictionary word. Return all such possible sentences.

    // Note:

    // The same word in the dictionary may be reused multiple times in the
    // segmentation.
    // You may assume the dictionary does not contain duplicate words.

    class Solution {
        public List<String> wordBreak(String s, List<String> wordDict) {
            HashSet<String> d = new HashSet<>(wordDict);
            HashMap<Integer, ArrayList<String>> memo = new HashMap<>();
            
            char[] sc = s.toCharArray();
            int max = 0;
            int min = Integer.MAX_VALUE;
            for (String w : d) {
                max = Math.max(w.length(), max);
                min = Math.min(w.length(), min);
            }
            return recursively(sc, 0, min, max, d, memo);
        }
        
        public ArrayList<String> recursively(char[] sc, int start, int min, int max, HashSet<String> dict, HashMap<Integer, ArrayList<String>> memo){
            if (start == sc.length) 
                return null;
            
            if (memo.containsKey(start)) 
                return memo.get(start);
            
            ArrayList<String> sentences = new ArrayList<>();
            memo.put(start, sentences);
            StringBuilder sb = new StringBuilder(max);
            for (int i = start; i < sc.length; i++) {
                sb.append(sc[i]);
                if (sb.length() > max)
                    break;
                if (sb.length() < min)
                    continue;
                String word = sb.toString();
                if (dict.contains(word)){
                    ArrayList<String> otherSentences = recursively(sc, i + 1, min, max, dict, memo);
                    if (otherSentences == null) {
                        sentences.add(word);
                    } else {
                        for (String s : otherSentences) sentences.add(word + " " + s);
                    }
                }
            }
            return memo.get(start);
        }
    }
}