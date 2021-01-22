#include <string>
#include <vector>
using namespace std;

// A message containing letters from A-Z can be encoded into numbers using the following mapping:

// 'A' -> "1"
// 'B' -> "2"
// ...
// 'Z' -> "26"
// To decode an encoded message, all the digits must be mapped back into letters using the
// reverse of the mapping above (there may be multiple ways). For example, "111" can have each of
// its "1"s be mapped into 'A's to make "AAA", or it could be mapped to "11" and "1" ('K' and 'A' respectively)
// to make "KA". Note that "06" cannot be mapped into 'F' since "6" is different from "06".

// Given a non-empty string num containing only digits, return the number of ways to decode it.

// The answer is guaranteed to fit in a 32-bit integer.

class Solution
{
public:
    int numDecodings(string s)
    {
        // if the string is empty, or has a prefix of 0, we can't encode it
        if (s.empty() || s[0] == '0')
            return 0;

        // there is one way to encode a string of length 1
        vector<int> dp(s.size() + 1, 0);
        dp[0] = 1;
        dp[1] = 1;

        for (int i = 2; i <= s.size(); ++i)
        {
            // consider the next character alone (if it encodes)
            // the number of ways to get to i is the number of ways to get to i - 1
            if (s[i - 1] != '0')
                dp[i] = dp[i - 1];

            // consider encoding the next character as the second in a pair
            // the first char before that must be 1 or 0
            // if the first char is 2, the second char must be <= 6
            bool tens = s[i - 2] == '1';
            bool twenties = s[i - 2] == '2';
            bool six = s[i - 1] <= '6';
            // add instead of set - to count both ways to get to this character
            if (tens || (twenties && six))
                dp[i] += dp[i - 2];
        }

        return dp[s.size()];
    }
};