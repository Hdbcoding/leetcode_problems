import java.util.ArrayList;

public class p1267 {
    // Count Servers that Communicate - medium

    // You are given a map of a server center, represented as a m * n integer matrix
    // grid, where 1 means that on that cell there is a server and 0 means that it
    // is no server. Two servers are said to communicate if they are on the same row
    // or on the same column.

    // Return the number of servers that communicate with any other server.

    class Solution {
        public int countServers(int[][] grid) {
            int h = grid.length;
            int w = grid[0].length;
            boolean[] colHasNodes = new boolean[w];
            boolean[] colHasMoreNodes = new boolean[w];
            boolean[] rowHasNodes = new boolean[h];
            boolean[] rowHasMoreNodes = new boolean[h];
            ArrayList<ArrayList<Integer>> uncountedNodes = new ArrayList<>();

            int count = 0;

            for (int r = 0; r < h; r++) {
                for (int c = 0; c < w; c++) {
                    if (grid[r][c] == 1) {
                        if (rowHasNodes[r] || colHasNodes[c]) {
                            count++;

                            if (rowHasNodes[r])
                                rowHasMoreNodes[r] = true;
                            if (colHasNodes[c])
                                colHasMoreNodes[c] = true;
                        } else {
                            ArrayList<Integer> node = new ArrayList<>();
                            node.add(r);
                            node.add(c);
                            uncountedNodes.add(node);
                        }
                        rowHasNodes[r] = true;
                        colHasNodes[c] = true;
                    }
                }
            }

            for (ArrayList<Integer> node : uncountedNodes) {
                if (rowHasMoreNodes[node.get(0)] || colHasMoreNodes[node.get(1)])
                    count++;
            }

            return count;
        }
    }
}