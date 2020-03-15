import java.util.Queue;
import java.util.List;
import java.util.LinkedList;
import java.util.ArrayList;

public class p207 {
    // Course Schedule - Medium

    // There are a total of numCourses courses you have to take, labeled from 0 to
    // numCourses-1.

    // Some courses may have prerequisites, for example to take course 0 you have to
    // first take course 1, which is expressed as a pair: [0,1]

    // Given the total number of courses and a list of prerequisite pairs, is it
    // possible for you to finish all courses?

    class Solution {
        public boolean canFinish(int numCourses, int[][] prerequisites) {
            Graph g = new Graph(numCourses);
            for (int[] edge : prerequisites) {
                g.addEdge(edge[0], edge[1]);
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

            return sorted.size() == numCourses;
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