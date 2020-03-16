import java.util.List;
import java.util.LinkedList;
import java.util.Queue;

public class p841 {
    // Keys and Rooms - Medium

    // There are N rooms and you start in room 0. Each room has a distinct number in
    // 0, 1, 2, ..., N-1, and each room may have some keys to access the next room.

    // Formally, each room i has a list of keys rooms[i], and each key rooms[i][j]
    // is an integer in [0, 1, ..., N-1] where N = rooms.length. A key rooms[i][j] =
    // v opens the room with number v.

    // Initially, all the rooms start locked (except for room 0).

    // You can walk back and forth between rooms freely.

    // Return true if and only if you can enter every room.

    class Solution {
        public boolean canVisitAllRooms(List<List<Integer>> rooms) {
            boolean[] visited = new boolean[rooms.size()];

            Queue<Integer> q = new LinkedList<>();
            q.add(0);

            while (!q.isEmpty()) {
                int u = q.poll();
                visited[u] = true;
                for (int v : rooms.get(u))
                    if (!visited[v])
                        q.add(v);
            }

            for (int i = 0; i < visited.length; i++) {
                if (!visited[i])
                    return false;
            }

            return true;
        }
    }
}