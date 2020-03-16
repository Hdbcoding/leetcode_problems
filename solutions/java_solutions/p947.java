import java.util.HashMap;
import java.util.ArrayList;
import java.util.Queue;
import java.util.LinkedList;

public class p947 {
    // Most Stones Removed with Same Row or Column - Medium

    // On a 2D plane, we place stones at some integer coordinate points. Each
    // coordinate point may have at most one stone.

    // Now, a move consists of removing a stone that shares a column or row with
    // another stone on the grid.

    // What is the largest possible number of moves we can make?

    class Solution {
        public int removeStones(int[][] stones) {
            if (stones.length <= 1)
                return 0;
            Graph g = generateGraph(stones);
            return countRemovableStones(g);
        }

        Graph generateGraph(int[][] stones) {
            HashMap<Integer, ArrayList<Integer>> x = new HashMap<>();
            HashMap<Integer, ArrayList<Integer>> y = new HashMap<>();

            for (int i = 0; i < stones.length; i++) {
                addStoneToMap(x, stones[i][0], i);
                addStoneToMap(y, stones[i][1], i);
            }

            Graph g = new Graph(stones.length);
            addEdges(g, x);
            addEdges(g, y);
            return g;
        }

        void addStoneToMap(HashMap<Integer, ArrayList<Integer>> map, int k, int v) {
            ArrayList<Integer> stones;
            if (map.containsKey(k))
                stones = map.get(k);
            else {
                stones = new ArrayList<Integer>();
                map.put(k, stones);
            }
            stones.add(v);
        }

        void addEdges(Graph g, HashMap<Integer, ArrayList<Integer>> map) {
            for (int key : map.keySet()) {
                ArrayList<Integer> set = map.get(key);
                // not sure if I need to exhaustively add all edges, or if I can get away with
                // being lazy here
                for (int i = 0; i < set.size() - 1; i++) {
                    for (int j = i + 1; j < set.size(); j++) {
                        g.addEdge(set.get(i), set.get(j));
                    }
                }
            }
        }

        int countRemovableStones(Graph g) {
            int stones = 0;
            boolean[] visited = new boolean[g.s];
            for (int i = 0; i < g.s; i++)
                if (!visited[i]) {
                    stones++;
                    markBFS(g, i, visited);
                }
            return stones;
        }

        void markBFS(Graph g, int s, boolean[] visited) {
            Queue<Integer> q = new LinkedList<>();
            q.add(s);

            while (!q.isEmpty()) {
                int u = q.poll();
                visited[u] = true;
                for (int v : g.adj.get(u))
                    if (!visited[v])
                        q.add(v);
            }
        }

        class Graph {
            ArrayList<ArrayList<Integer>> adj;
            int s;

            Graph(int s) {
                this.s = s;

                adj = new ArrayList<>();
                for (int i = 0; i < s; i++) {
                    adj.add(new ArrayList<>());
                }
            }

            void addEdge(int u, int v) {
                adj.get(u).add(v);
                adj.get(v).add(u);
            }
        }
    }
}