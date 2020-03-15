import java.util.Arrays;
import java.util.List;
import java.util.ArrayList;


public class p126 {
    // Word Ladder 2 - Hard

    // Given two words (beginWord and endWord), and a dictionary's word list, find
    // all shortest transformation sequence(s) from beginWord to endWord, such that:

    // Only one letter can be changed at a time
    // Each transformed word must exist in the word list. Note that beginWord is not
    // a transformed word.
    // Note:

    // Return an empty list if there is no such transformation sequence.
    // All words have the same length.
    // All words contain only lowercase alphabetic characters.
    // You may assume no duplicates in the word list.
    // You may assume beginWord and endWord are non-empty and are not the same.

    public static void main(String[] args) {
        runTest("hit", "cog", new String[] { "hot", "dot", "dog", "lot", "log", "cog" }, new String[][] {
            {"hit","hot","dot","dog","cog"},
            {"hit","hot","lot","log","cog"}
        });
    }

    static void runTest(String start, String end, String[] words, String[][] expected) {
        List<List<String>> actual = new Solution().findLadders(start, end, Arrays.asList(words));

        String actualString = Arrays.toString(actual.stream().map(s -> Arrays.toString(s.toArray())).toArray());
        String expectedString = Arrays.toString(Arrays.stream(expected).map(s -> Arrays.toString(s)).toArray());
        if (!actualString.equals(expectedString)) {
            System.out.println("Unexpected result mapping " + start + " to " + end + " for map: "
                    + Arrays.toString(words) + ", expected: " + expectedString + ", but got: " + actualString);
        }
    }

    static class Solution {
        public List<List<String>> findLadders(String beginWord, String endWord, List<String> wordList) {
            return new ArrayList<>();
        }
    }
}