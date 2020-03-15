import java.util.List;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Arrays;
import java.util.Queue;
import java.util.Map;
import java.util.HashMap;

public class p127 {
    // Word ladder - Medium

    // Given two words (beginWord and endWord), and a dictionary's word list, find
    // the length of shortest transformation sequence from beginWord to endWord,
    // such that:

    // Only one letter can be changed at a time.
    // Each transformed word must exist in the word list. Note that beginWord is not
    // a transformed word.
    // Note:

    // Return 0 if there is no such transformation sequence.
    // All words have the same length.
    // All words contain only lowercase alphabetic characters.
    // You may assume no duplicates in the word list.
    // You may assume beginWord and endWord are non-empty and are not the same.

    public static void main(String[] args) {
        runTest("hit", "cog", new String[] { "hot", "dot", "dog", "lot", "log", "cog" }, 5);
    }

    static void runTest(String start, String end, String[] words, int expected) {
        int actual = new Solution().ladderLength(start, end, Arrays.asList(words));
        if (expected != actual) {
            System.out.println("Unexpected result mapping " + start + " to " + end + " for map: "
                    + Arrays.toString(words) + ", expected: " + expected + ", but got: " + actual);
        }
    }

    static class Solution {
        public int ladderLength(String beginWord, String endWord, List<String> wordList) {
            if (beginWord == endWord)
                return 0;

            int end = wordList.indexOf(endWord);
            if (end == -1)
                return 0;

            return useAdjacencyList(beginWord, end, wordList);
        }

        int useAdjacencyList(String beginWord, int end, List<String> wordList) {
            Graph g = generateWithHashMap(beginWord, wordList);
            return bfs(g.s - 1, end, g);
        }

        Graph generateWithHashMap(String beginWord, List<String> wordList) {
            Map<String, List<Integer>> map = new HashMap<>();
            int l = beginWord.length();
            int s = wordList.size();
            for (int i = 0; i < s; i++) {
                String word = wordList.get(i);
                addWord(word, l, i, map);
            }
            addWord(beginWord, l, s, map);

            Graph g = new Graph(s + 1);
            for (String key : map.keySet()) {
                List<Integer> set = map.get(key);
                for (int i = 0; i < set.size(); i++) {
                    for (int j = i + 1; j < set.size(); j++) {
                        g.addEdge(set.get(i), set.get(j));
                    }
                }
            }

            return g;
        }

        void addWord(String word, int l, int i, Map<String, List<Integer>> map) {
            for (int j = 0; j < l; j++) {
                String key = word.substring(0, j) + "*" + word.substring(j + 1, l);
                List<Integer> set;
                if (map.containsKey(key)) {
                    set = map.get(key);
                } else {
                    set = new ArrayList<>();
                    map.put(key, set);
                }
                set.add(i);
            }
        }

        Graph generateWithPairwiseComparisons(String beginWord, List<String> wordList) {
            int s = wordList.size();
            // graph holds number of transformed words + the beginning word
            Graph g = new Graph(s + 1);
            for (int i = 0; i < s; i++) {
                String word = wordList.get(i);

                // compare this word to all other words
                for (int j = i + 1; j < s; j++) {
                    String otherWord = wordList.get(j);
                    if (closeEnough(word, otherWord))
                        g.addEdge(i, j);
                }

                // compare this word to the begin word
                if (closeEnough(word, beginWord))
                    g.addEdge(i, s);
            }

            return g;
        }

        int bfs(int s, int end, Graph g) {
            // shortest path in unweighted graph is essentially bfs
            Queue<Integer> q = new LinkedList<>();
            int[] dist = new int[g.s];
            Arrays.fill(dist, -1);
            dist[s] = 1;
            q.add(s);
            while (!q.isEmpty()) {
                int u = q.poll();

                for (int v : g.adj.get(u)) {
                    if (dist[v] == -1) {
                        dist[v] = dist[u] + 1;
                        q.add(v);
                        if (v == end)
                            return dist[v];
                    }
                }
            }

            return 0;
        }

        boolean closeEnough(String a, String b) {
            boolean mismatch = false;
            for (int i = 0; i < a.length(); i++) {
                if (a.charAt(i) != b.charAt(i)) {
                    if (mismatch)
                        return false;
                    mismatch = true;
                }
            }
            return true;
        }

        class Graph {
            ArrayList<ArrayList<Integer>> adj;
            int s;

            Graph(int s) {
                this.s = s;
                this.adj = new ArrayList<>(s);
                for (int i = 0; i < s; i++)
                    this.adj.add(new ArrayList<>());
            }

            void addEdge(int u, int v) {
                adj.get(u).add(v);
                adj.get(v).add(u);
            }
        }
    }
}