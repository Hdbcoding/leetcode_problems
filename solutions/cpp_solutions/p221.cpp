#include <vector>
using namespace std;
// Maximal Square - Medium

// Given an m x n binary matrix filled with 0's and 1's, find the largest square containing only 1's and return its area.

class Solution
{
public:
    int fulldp(vector<vector<char>> &matrix)
    {
        int rows = matrix.size();
        int cols = matrix[0].size();
        int maxSize = 0;
        vector<vector<int>> dp(rows + 1, vector<int>(cols + 1));
        for (int i = 1; i <= rows; ++i)
        {
            for (int j = 1; j <= cols; ++j)
            {
                if (matrix[i - 1][j - 1] == '1')
                {
                    dp[i][j] = min(dp[i - 1][j], min(dp[i - 1][j - 1], dp[i][j - 1])) + 1;
                    maxSize = max(maxSize, dp[i][j]);
                }
            }
        }
        return maxSize * maxSize;
    }

    int tworowdp(vector<vector<char>> &matrix)
    {
        int rows = matrix.size();
        int cols = matrix[0].size();
        int maxSize = 0;
        vector<vector<int>> dp(2, vector<int>(cols + 1));

        for (int i = 1; i <= rows; ++i)
        {
            int current = i & 1;
            int old = ~i & 1;
            for (int j = 1; j <= cols; ++j)
            {
                if (matrix[i - 1][j - 1] == '1')
                {
                    dp[current][j] = min(dp[old][j], min(dp[old][j - 1], dp[current][j - 1])) + 1;
                    maxSize = max(maxSize, dp[current][j]);
                }
            }
        }
        return maxSize * maxSize;
    }

    int maximalSquare(vector<vector<char>> &matrix)
    {
        return tworowdp(matrix);
    }
};