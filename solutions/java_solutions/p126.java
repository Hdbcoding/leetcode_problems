import java.util.Arrays;
import java.util.List;
import java.util.ArrayList;
import java.util.Queue;
import java.util.LinkedList;
import java.util.HashMap;
import java.util.Map;

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

    // [hot, dot, dog, lot, log, cog], 
    // expected: 
    //      [[hit, hot, dot, dog, cog], [hit, hot, lot, log, cog]]
    // , but got: 
    //      [[hit, hot, dot, dog, cog], [hit, hot, lot, log, cog], 
    //       [hit, hot, dot, lot, log, cog], [hit, hot, dot, dog, log, cog],
    //       [hit, hot, lot, log, dog, cog], [hit, hot, lot, dot, dog, cog], 
    //       [hit, hot, dot, lot, log, dog, cog], [hit, hot, lot, dot, dog, log, cog]]

    public static void main(String[] args) {
        runTest("hit", "cog", new String[] { "hot", "dot", "dog", "lot", "log", "cog" },
                new String[][] { { "hit", "hot", "dot", "dog", "cog" }, { "hit", "hot", "lot", "log", "cog" } });
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
            if (beginWord == endWord)
                return new ArrayList<>();

            int end = wordList.indexOf(endWord);
            if (end == -1)
                return new ArrayList<>();

            Graph g = generateWithHashMap(beginWord, wordList);
            ArrayList<String> allWords = new ArrayList<String>(wordList);
            allWords.add(beginWord);
            return bfsThenDFS(g.s - 1, end, g, allWords);
            // return bfsAllPaths(g.s - 1, end, g, allWords);
        }

        List<List<String>> bfsThenDFS(int start, int end, Graph g, List<String> wordList) {
            int[] dist = bfsDist(start, g);
            return dfsAllPaths(start, end, g, dist, wordList);
        }

        int[] bfsDist(int start, Graph g) {
            Queue<Integer> q = new LinkedList<>();
            int[] dist = new int[g.s];
            Arrays.fill(dist, -1);
            dist[start] = 1;
            q.add(start);
            while (!q.isEmpty()) {
                int u = q.poll();
                for (int v : g.adj.get(u)) {
                    if (dist[v] == -1) {
                        dist[v] = dist[u] + 1;
                        q.add(v);
                    }
                }
            }
            return dist;
        }
        
        List<List<String>> dfsAllPaths(int start, int end, Graph g, int[] dist, List<String> wordList) {
            List<List<String>> allPaths = new ArrayList<>();
            ArrayList<Integer> currentPath = new ArrayList<Integer>();
            dfsRecurse(start, end, g, dist, currentPath, allPaths, wordList);
            return allPaths;
        }

        void dfsRecurse(int u, int end, Graph g, int[] dist, List<Integer> currentPath, List<List<String>> allPaths, List<String> wordList) {
            currentPath.add(u);

            if (u == end)
                addStringPath(currentPath, allPaths, wordList);
            else {
                for (int v : g.adj.get(u)) {
                    if (dist[v] == dist[u] + 1)
                        dfsRecurse(v, end, g, dist, currentPath, allPaths, wordList);
                }
            }

            currentPath.remove(currentPath.size() - 1);
        }

        List<List<String>> bfsAllPaths(int start, int end, Graph g, List<String> wordList) {
            List<List<String>> paths = new ArrayList<>();

            Queue<ArrayList<Integer>> q = new LinkedList<>();
            ArrayList<Integer> path = new ArrayList<>();
            path.add(start);
            q.add(path);

            while (!q.isEmpty()) {
                path = q.poll();
                int u = path.get(path.size() - 1);

                if (u == end) {
                    boolean pathWasLonger = addStringPath(path, paths, wordList);
                    if (pathWasLonger)
                        return paths;
                }

                for (int v : g.adj.get(u)) {
                    if (!path.contains(v)) {
                        ArrayList<Integer> newPath = new ArrayList<>(path);
                        newPath.add(v);
                        q.add(newPath);
                    }
                }
            }

            return paths;
        }

        boolean addStringPath(List<Integer> path, List<List<String>> paths, List<String> wordList) {
            if (paths.size() > 0 && paths.get(0).size() < path.size())
                return true;

            List<String> pathAsWords = new ArrayList<String>(path.size());
            for (int u : path)
                pathAsWords.add(wordList.get(u));
            paths.add(pathAsWords);
            return false;
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