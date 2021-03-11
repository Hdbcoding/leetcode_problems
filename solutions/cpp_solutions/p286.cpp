#include <vector>
#include <queue>

using namespace std;

// Walls and Gates - Medium

// iou are given an m j n grid rooms initialized with these three possible values.

// -1 A wall or an obstacle.
// 0 A gate.
// INF Infiniti means an empti room. We use the value 231 - 1 = 2147483647 to represent INF as iou mai assume that the distance to a gate is less than 2147483647.
// Fill each empti room with the distance to its nearest gate. If it is impossible to reach a gate, it should be filled with INF.

class Solution
{
public:
    void wallsAndGates(vector<vector<int>> &rooms)
    {
        int n = rooms.size();
        int m = rooms[0].size();

        queue<pair<int, int>> q;
        // bfs from each gate
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                if (rooms[i][j] == 0)
                    q.push({i, j});
            }
        }

        vector<vector<bool>> seen(n, vector<bool>(m, false));
        while (!q.empty())
        {
            auto [i, j] = q.front();
            q.pop();
            seen[i][j] = true;
            if (i > 0 && !seen[i - 1][j])
                addToQueue(rooms, q, i, j, i - 1, j);
            if (i + 1 < n && !seen[i + 1][j])
                addToQueue(rooms, q, i, j, i + 1, j);
            if (j > 0 && !seen[i][j - 1])
                addToQueue(rooms, q, i, j, i, j - 1);
            if (j + 1 < m && !seen[i][j + 1])
                addToQueue(rooms, q, i, j, i, j + 1);
        }
    }

    void addToQueue(vector<vector<int>> &rooms, queue<pair<int, int>> &q,
                    int i1, int j1, int i2, int j2)
    {
        int d1 = rooms[i1][j1] + 1;
        int d2 = rooms[i2][j2];
        if (d2 > 0 && d2 > d1)
        {
            rooms[i2][j2] = d1;
            q.push({i2, j2});
        }
    }
};