import java.util.List;
import java.util.HashMap;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Stack;
import java.util.Queue;
import java.util.LinkedList;

public class p399 {
    // Evaluate division - Medium

    // Equations are given in the format A / B = k, where A and B are variables
    // represented as strings, and k is a real number (floating point number). Given
    // some queries, return the answers. If the answer does not exist, return -1.0.

    // The input is always valid. You may assume that evaluating the queries will
    // result in no division by zero and there is no contradiction.

    public static void main(String[] args) {
        runTest(new String[][] { { "a", "b" }, { "b", "c" } }, new double[] { 2.0, 3.0 },
                new String[][] { { "a", "c" }, { "b", "a" }, { "a", "e" }, { "a", "a" }, { "x", "x" } },
                new double[] { 6.0, 0.5, -1.0, 1.0, -1.0 });
    }

    static void runTest(String[][] eqd, double[] values, String[][] qd, double[] expected) {
        List<List<String>> equations = fromArray(eqd);
        List<List<String>> queries = fromArray(qd);
        double[] actual = new Solution().calcEquation(equations, values, queries);
        System.out.println(queries.toString());
        System.out.println(Arrays.toString(expected));
        System.out.println(Arrays.toString(actual));
    }

    static List<List<String>> fromArray(String[][] eqd) {
        List<List<String>> set = new ArrayList<>(eqd.length);
        for (String[] a : eqd) {
            List<String> as = new ArrayList<>(2);
            set.add(as);
            for (String s : a)
                as.add(s);
        }
        return set;
    }

    static class Solution {
        public double[] calcEquation(List<List<String>> equations, double[] values, List<List<String>> queries) {
            Graph g = parseGraph(equations, values);
            return usingBFS(g, queries);
        }

        double[] usingBellmanFord(Graph g, List<List<String>> queries) {
            double[] responses = new double[queries.size()];
            for (int i = 0; i < queries.size(); i++) {
                List<String> query = queries.get(i);
                responses[i] = bellmanFord(query.get(0), query.get(1), g);
            }
            return responses;
        }

        double bellmanFord(String a, String b, Graph g) {
            if (!g.map.containsKey(a))
                return -1;
            if (!g.map.containsKey(b))
                return -1;
            int start = g.map.get(a);
            int end = g.map.get(b);
            Double[] dist = new Double[g.s];
            int[] pred = new int[g.s];
            Arrays.fill(pred, -1);
            Stack<Integer> s = new Stack<>();
            boolean[] visited = new boolean[g.s];
            dist[start] = 0.;

            for (int k = 0; k < g.s; k++) {
                boolean hasChanges = false;
                Arrays.fill(visited, false);
                s.add(start);
                while (!s.isEmpty()) {
                    int u = s.pop();
                    visited[u] = true;
                    List<Integer> adj = g.adj.get(u);
                    List<Double> w = g.w.get(u);
                    for (int i = 0; i < adj.size(); i++) {
                        int v = adj.get(i);
                        double c = w.get(i);
                        hasChanges |= relax(u, v, c, dist, pred);
                        if (!visited[v])
                            s.add(v);
                    }
                }
                if (!hasChanges)
                    break;
            }

            return dist[end] == null ? -1 : Math.exp(dist[end]);
        }

        double[] usingBFS(Graph g, List<List<String>> queries) {
            double[] responses = new double[queries.size()];
            for (int i = 0; i < queries.size(); i++) {
                List<String> query = queries.get(i);
                responses[i] = bfs(query.get(0), query.get(1), g);
            }
            return responses;
        }

        double bfs(String a, String b, Graph g) {
            if (!g.map.containsKey(a))
                return -1;
            if (!g.map.containsKey(b))
                return -1;
            int start = g.map.get(a);
            int end = g.map.get(b);
            Queue<Integer> q = new LinkedList<>();
            Double[] dist = new Double[g.s];
            dist[start] = 0.;
            q.add(start);
            while (!q.isEmpty()) {
                int u = q.poll();
                List<Integer> adj = g.adj.get(u);
                List<Double> weights = g.w.get(u);
                for (int i = 0; i < adj.size(); i++) {
                    int v = adj.get(i);
                    if (dist[v] == null) {
                        dist[v] = dist[u] + weights.get(i);
                        q.add(v);
                    }
                }
            }
            return dist[end] == null ? -1 : Math.exp(dist[end]);
        }

        boolean relax(int u, int v, double w, Double[] dist, int[] pred) {
            if (dist[v] == null || dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pred[v] = u;
                return true;
            }
            return false;
        }

        Graph parseGraph(List<List<String>> equations, double[] values) {
            Graph g = new Graph();
            for (int i = 0; i < equations.size(); i++) {
                List<String> eq = equations.get(i);
                double m = values[i];
                g.addEdge(eq.get(0), eq.get(1), m);
            }
            return g;
        }

        class Graph {
            HashMap<String, Integer> map;
            ArrayList<ArrayList<Integer>> adj;
            ArrayList<ArrayList<Double>> w;

            int s;

            Graph() {
                this.map = new HashMap<>();
                this.adj = new ArrayList<>();
                this.w = new ArrayList<>();
            }

            void addEdge(String a, String b, double m) {
                int u = getOrAdd(a);
                int v = getOrAdd(b);

                double lgm = Math.log(m);

                adj.get(u).add(v);
                w.get(u).add(lgm);

                adj.get(v).add(u);
                w.get(v).add(-lgm);
            }

            int getOrAdd(String a) {
                if (!map.containsKey(a)) {
                    map.put(a, s++);
                    adj.add(new ArrayList<>());
                    w.add(new ArrayList<>());
                }
                return map.get(a);
            }
        }
    }
}