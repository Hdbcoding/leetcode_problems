#include <string>
#include <vector>
using namespace std;

// Minimum Window Subsequence - Hard

// Given strings S and T, find the minimum (contiguous) substring W of S, so that T is a subsequence of W.

// If there is no such window in S that covers all characters in T, return the empty string "".
// If there are multiple such minimum-length windows, return the one with the left-most starting index.

// Note:
// All the strings in the input will only contain lowercase letters.
// The length of S will be in the range [1, 20000].
// The length of T will be in the range [1, 100].
class Solution
{
public:
    // for each starting position, scan ahead until we have satisfied T
    // O(S^2), and too slow to pass
    string naive(string S, string T)
    {
        int l{-1}, r{-1};

        for (int i = 0; i < S.size(); ++i)
        {
            int sj = i;
            int tj = 0;
            while (sj < S.size() && tj < T.size())
            {
                // if this char in S is the next char in T, advance tj
                if (S[sj] == T[tj])
                    ++tj;
                // if we have exhausted T, we have a new candidate solution
                if (tj == T.size() && (r == -1 || sj - i < r - l))
                {
                    l = i;
                    r = sj;
                }
                sj++;
            }
        }
        return r == -1 ? "" : S.substr(l, r - l + 1);
    }

    // dynamic programming solution, where we consider slowly increasing subsets of T
    // in this version, will fill out the whole table of dp[T.size()][S.size()]
    // we only ever access 2 rows, so we don't need to use this much memory
    // O(S*T) time and space
    string dp_fulltable(string S, string T)
    {
        // dynamic programming table, building up to larger candidate subsequences of T
        //  dp[i][j] is a window size where a window ending at S[i] satisfies T through T[j]
        vector<vector<int>> dp(T.size());
        dp[0].assign(S.size(), -1);
        // base case - T is one character long. does S[i] == T[0]?
        for (int i = 0; i < S.size(); ++i){
            dp[0][i] = S[i] == T[0] ? i : -1;
        }

        // for each additional size subsequence
        for (int j = 1; j < T.size(); ++j)
        {
            int last = -1;
            dp[j].assign(S.size(), -1);

            for (int i = 0; i < S.size(); ++i)
            {
                if (last >= 0 && S[i] == T[j])
                    dp[j][i] = last;
                if (dp[j - 1][i] >= 0)
                    last = dp[j - 1][i];
            }
        }

        // choose the smallest window that encompasses the entire candidate string
        int l{0}, r{(int)S.size()};
        for (int end = 0; end < S.size(); ++end){
            int start = dp[T.size() - 1][end];
            if (start >= 0 && end - start < r - l){
                l = start;
                r = end;
            }
        }
        return r < S.size() ? S.substr(l, r - l + 1) : "";
    }

    // dynamic programming solution, where we consider slowly increasing subsets of T
    // in this version, will fill do the 2 row trick
    // O(S*T) time, but O(S) space this time
    string dp_2row(string S, string T)
    {
        // dynamic programming table, building up to larger candidate subsequences of T
        //  dp[i][j] is a window size where a window ending at S[i] satisfies T through T[j]
        vector<vector<int>> dp(2);
        // base case - T is one character long. does S[i] == T[0]?
        for (int i = 0; i < S.size(); ++i){
            dp[0][i] = S[i] == T[0] ? i : -1;
        }

        // for each additional size subsequence
        for (int j = 1; j < T.size(); ++j)
        {
            int last = -1;
            int current = j & 1;
            int old = ~j & 1;
            dp[current].assign(S.size(), -1);

            for (int i = 0; i < S.size(); ++i)
            {
                if (last >= 0 && S[i] == T[j])
                    dp[current][i] = last;
                if (dp[old][i] >= 0)
                    last = dp[old][i];
            }
        }

        // choose the smallest window that encompasses the entire candidate string
        int l{0}, r{(int)S.size()};
        int solutionRow = ~T.size() & 1;
        for (int end = 0; end < S.size(); ++end){
            int start = dp[solutionRow][end];
            if (start >= 0 && end - start < r - l){
                l = start;
                r = end;
            }
        }
        return r < S.size() ? S.substr(l, r - l + 1) : "";
    }

    string minWindow(string S, string T)
    {
        return dp_2row(S, T);
    }
};