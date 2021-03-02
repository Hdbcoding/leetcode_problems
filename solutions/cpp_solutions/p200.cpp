#include <vector>
#include <queue>

using namespace std;

// Number of Islands - Medium

// Given an m x n 2d grid map of '1's (land) and '0's (water), return the number of islands.

// An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

class Solution
{
public:
    int numIslands(vector<vector<char>> &grid)
    {
        int count = 0;
        for (int i = 0; i < grid.size(); ++i)
        {
            for (int j = 0; j < grid[0].size(); ++j)
            {
                if (grid[i][j] == '1')
                {
                    ++count;
                    bfsClear(grid, i, j);
                }
            }
        }
        return count;
    }

    void bfsClear(vector<vector<char>> &grid, int i, int j)
    {
        queue<pair<int, int>> toVisit;
        toVisit.push({i, j});
        while (!toVisit.empty())
        {
            pair<int, int> next = toVisit.front();
            toVisit.pop();
            // skip invalid locations
            if (next.first < 0 || next.second < 0)
                continue;
            if (next.first >= grid.size() || next.second >= grid[0].size())
                continue;
            // skip 0s
            if (grid[next.first][next.second] == '0')
                continue;
            // clear this location so we don't visit it again
            grid[next.first][next.second] = '0';
            toVisit.push({next.first - 1, next.second});
            toVisit.push({next.first + 1, next.second});
            toVisit.push({next.first, next.second - 1});
            toVisit.push({next.first, next.second + 1});
        }
    }
};