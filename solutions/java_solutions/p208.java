import java.util.Queue;
import java.util.List;
import java.util.LinkedList;
import java.util.ArrayList;

public class p208 {
    // Course Schedule II - medium

    // There are a total of n courses you have to take, labeled from 0 to n-1.

    // Some courses may have prerequisites, for example to take course 0 you have to
    // first take course 1, which is expressed as a pair: [0,1]

    // Given the total number of courses and a list of prerequisite pairs, return
    // the ordering of courses you should take to finish all courses.

    // There may be multiple correct orders, you just need to return one of them. If
    // it is impossible to finish all courses, return an empty array.

    class Solution {
        public int[] findOrder(int numCourses, int[][] prerequisites) {
            Graph g = new Graph(numCourses);
            for (int[] edge : prerequisites) {
                g.addEdge(edge[1], edge[0]);
            }

            // establish courses with no prerequisites
            Queue<Integer> q = new LinkedList<>();
            for (int i = 0; i < numCourses; i++)
                if (g.in[i] == 0)
                    q.add(i);

            List<Integer> sorted = new ArrayList<>();
            while (!q.isEmpty()) {
                int u = q.poll();
                sorted.add(u);
                for (int v : g.adj.get(u))
                    if (--g.in[v] == 0)
                        q.add(v);
            }

            if (sorted.size() == numCourses) {
                int[] result = new int[numCourses];
                for (int i = 0; i < numCourses; i++)
                    result[i] = sorted.get(i);
                return result;
            }
            return new int[0];
        }

        class Graph {
            ArrayList<ArrayList<Integer>> adj;
            int[] in;
            int s;

            Graph(int s) {
                this.s = s;
                this.in = new int[s];
                this.adj = new ArrayList<>(s);
                for (int i = 0; i < s; i++) {
                    this.adj.add(new ArrayList<>());
                }
            }

            void addEdge(int u, int v) {
                this.adj.get(u).add(v);
                this.in[v]++;
            }

        }
    }
}