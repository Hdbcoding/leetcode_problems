#include <vector>
#include <cmath>

using namespace std;

// Perfect Squares - Medium

// Given an integer n, return the least number of perfect square numbers that sum to n.

// A perfect square is an integer that is the square of an integer; in other words, 
// it is the product of some integer with itself. For example, 1, 4, 9, and 16 are perfect squares while 3 and 11 are not.

class Solution {
public:
    int numSquares(int n) {
        return bottomup2(n);
    }
    
    // O(n) dp works
    int bottomup2(int n)
    {
        if (n <= 3) return n;
        
        vector<int> dp(n + 1);
        dp[0] = 0;
        dp[1] = 1;
        dp[2] = 2;
        dp[3] = 3;
        for (int i = 4; i <= n; ++i)
        {
            // i can at least add up ones
            dp[i] = i;
            
            // for each square smaller than this, see if I can use it to reduce this count
            for (int j = 1; j <= ceil(sqrt(i)); ++j)
            {
                int sqr = j * j;
                if (sqr > i) break;
                dp[i] = min(dp[i], 1 + dp[i - sqr]);
            }
        }
        return dp[n];
    }
    
    // O(n^2) dp is too slow to pass
    int bottomup(int n)
    {
        if (n == 1) 
            return 1;
        
        // at iteration i
        // dp[j] is the best way to construct (j + 1) with numbers [1:i]
        // dp[j] = min over 
        vector<int> dp(n + 1, 0);
        // considering 1 -> best way to construct is i
        for (int i = 0; i <= n; ++i)
            dp[i] = i;
        
        // considering 2 -> best way to construct is best way to add 4 to get the num, + 1 or 0
        
        // for 3, we add 9s some number of times, leading us back earlier in the dp table
        // we get the best minimizing over dp[j - 9 * m]
        
        int root = (int)sqrt((double)n);
        for (int i = 1; i < root; ++i)
        {
            int num = i + 1;
            int square = num * num;
            
            for (int j = square; j <= n; ++j)
            {
                for (int prev = j - square, k = 1; prev >= 0; prev -= square, ++k)
                {
                    dp[j] = min(dp[j], dp[prev] + k);
                }
            }
        }
        

        return dp[n];
    }
    
    // too slow to pass
    // int root = (int)sqrt((double)n);
    // vector<vector<int>> memo(n + 1, vector<int>(root + 1, -1));
    // return numSquaresRecurse(n, root, memo);
    int numSquaresRecurse(int n, int i, vector<vector<int>> memo)
    {
        if (n == 0) return 0;
        if (n < 0) return numeric_limits<int>::max() - 1;
        if (i == 1) return n;
        
        if (memo[n][i] == -1)
        {
            int square = i * i;
            int useThis = numSquaresRecurse(n - square, i, memo) + 1;
            int skipThis = numSquaresRecurse(n, i - 1, memo);

            memo[n][i] = min(useThis, skipThis);
        }
        
        return memo[n][i];
    }
};