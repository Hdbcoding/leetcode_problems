#include <vector>

using namespace std;

// Cherry Pickup 2 - Hard

// Given a rows x cols matrix grid representing a field of cherries. Each cell in grid represents the number of cherries that you can collect.

// You have two robots that can collect cherries for you, Robot #1 is located at the top-left corner (0,0) , and Robot #2 is located at the top-right corner (0, cols-1) of the grid.

// Return the maximum number of cherries collection using both robots  by following the rules below:

// From a cell (i,j), robots can move to cell (i+1, j-1) , (i+1, j) or (i+1, j+1).
// When any robot is passing through a cell, It picks it up all cherries, and the cell becomes an empty cell (0).
// When both robots stay on the same cell, only one of them takes the cherries.
// Both robots cannot move outside of the grid at any moment.
// Both robots should reach the bottom row in the grid.

class Solution
{
public:
    int cherryPickup(vector<vector<int>> &grid)
    {
        return bottomup(grid);
    }

    int memoization(vector<vector<int>> &grid, int i, int r1, int r2, vector<vector<vector<int>>> &memo)
    {
        if (i == grid.size())
            return 0;
        if (r1 < 0 || r2 < 0 || r1 == grid[0].size() || r2 == grid[0].size())
            return 0;

        if (memo[i][r1][r2] == -1)
        {
            int gains = grid[i][r1];
            if (r1 != r2)
                gains += grid[i][r2];

            int ll = memoization(grid, i + 1, r1 - 1, r2 - 1, memo);
            int l_ = memoization(grid, i + 1, r1 - 1, r2, memo);
            int lr = memoization(grid, i + 1, r1 - 1, r2 + 1, memo);
            int _l = memoization(grid, i + 1, r1, r2 - 1, memo);
            int oo = memoization(grid, i + 1, r1, r2, memo);
            int _r = memoization(grid, i + 1, r1, r2 + 1, memo);
            int rl = memoization(grid, i + 1, r1 + 1, r2 - 1, memo);
            int r_ = memoization(grid, i + 1, r1 + 1, r2, memo);
            int rr = memoization(grid, i + 1, r1 + 1, r2 + 1, memo);

            int bestl = max(ll, max(l_, lr));
            int best_ = max(_l, max(oo, _r));
            int bestr = max(rl, max(r_, rr));

            int best = max(bestl, max(best_, bestr));
            memo[i][r1][r2] = best + gains;
        }

        return memo[i][r1][r2];
    }

    int bottomup(vector<vector<int>> &grid)
    {
        int m = grid[0].size();
        vector<vector<vector<int>>> dp(2, vector<vector<int>>(m, vector<int>(m, 0)));
        dp[1][0][m - 1] = getGains(grid, 0, 0, m - 1);
        int maxOverall = dp[1][0][m - 1];
        for (int i = 1; i < grid.size(); ++i)
        {
            int prev = i % 2;
            int next = (i + 1) % 2;
            // skip some not reachable indices
            for (int r1 = 0; r1 < min(i + 1, m); ++r1)
            {
                for (int r2 = m - 1; r2 >= max(0, m - i - 1); --r2)
                {
                    int maxCherries = bestPrev(dp, prev, r1, r2);
                    int gains = getGains(grid, i, r1, r2);
                    dp[next][r1][r2] = gains + maxCherries;
                    maxOverall = max(maxOverall, dp[next][r1][r2]);
                }
            }
        }

        return maxOverall;
    }

    int bestPrev(vector<vector<vector<int>>> &dp, int i, int r1, int r2)
    {
        int maxValue = 0;
        int m = dp[i].size() - 1;
        for (int j1 = max(0, r1 - 1); j1 <= min(m, r1 + 1); ++j1)
            for (int j2 = max(0, r2 - 1); j2 <= min(m, r2 + 1); ++j2)
                maxValue = max(maxValue, dp[i][j1][j2]);

        return maxValue;
    }

    int getGains(vector<vector<int>> &grid, int i, int r1, int r2)
    {
        int gains = grid[i][r1];
        if (r1 != r2)
            gains += grid[i][r2];
        return gains;
    }
};