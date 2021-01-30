#include <vector>
#include <string>
using namespace std;
// Minimum distance to type a word using two fingers

// You have a keyboard layout as shown above in the XY plane, where each English uppercase letter is located at some coordinate,
//  for example, the letter A is located at coordinate (0,0), the letter B is located at coordinate (0,1), the letter P is located at coordinate (2,3) and the letter Z is located at coordinate (4,1).

// Given the string word, return the minimum total distance to type such string using only two fingers.
// The distance between coordinates (x1,y1) and (x2,y2) is |x1 - x2| + |y1 - y2|.

// Note that the initial positions of your two fingers are considered free so don't count towards your total distance,
//  also your two fingers do not have to start at the first letter or the first two letters.

class Solution
{
    int distance(int i, int j, const vector<pair<int, int>> &keyboard)
    {
        return distance(keyboard[i], keyboard[j]);
    }

    int distance(pair<int, int> a, pair<int, int> b)
    {
        return abs(a.first - b.first) + abs(a.second - b.second);
    }

public:
    // the naive solution doesn't even work
    int naive(const vector<pair<int, int>> &keyboard, const string &word)
    {
        pair<int, int> left = keyboard[word[0] - 'A'];
        pair<int, int> right = keyboard[word[1] - 'A'];

        int sum = 0;
        for (int i = 2; i < word.size(); ++i)
        {
            pair<int, int> next = keyboard[word[i] - 'A'];
            int dleft = distance(left, next);
            int dright = distance(right, next);
            if (dleft <= dright)
            {
                sum += dleft;
                left = next;
            }
            else
            {
                sum += dright;
                right = next;
            }
        }
        return sum;
    }

    int dynamicProgramming(const vector<pair<int, int>> &keyboard, string word)
    {
        // at kth iteration, dp[i][j] optimal distance to type word[0:k] if fingers are now at [i][j]
        //  so for k + 1, dp[i][i] = min(move left, move right)
        //                           min(dp[word[k]][j] + dist(word[k], i), dp[i][word[k]] + dist(word[k], j))
        vector<vector<int>> dp(26, vector<int>(26));
        for (int k = 1; k <= word.size(); ++k)
        {
            int c = word[k - 1] - 'A';
            for (int i = 0; i < 26; ++i)
            {
                for (int j = 0; j < 26; ++j)
                {
                    int left = distance(i, c, keyboard);
                    int right = distance(j, c, keyboard);
                    dp[i][j] = min(dp[c][j] + left, dp[i][c] + right);
                }
            }
        }

        int result = numeric_limits<int>::max();
        int lastC = word[word.size() - 1] - 'A';
        for (int i = 0; i < 26; ++i)
        {
            result = min(result, dp[i][lastC]);
            result = min(result, dp[lastC][i]);
        }

        return result;
    }

    int minimumDistance(string word)
    {
        if (word.size() == 2)
            return 0;

        vector<pair<int, int>> keyboard;
        char current = 0;
        for (int row = 0; row < 5; ++row)
        {
            for (int col = 0; col < 6; ++col)
            {
                keyboard.push_back({row, col});
                if (++current == 26)
                    break;
            }
        }

        return dynamicProgramming(keyboard, word);
    }
};