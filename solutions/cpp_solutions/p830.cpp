#include <vector>
#include <string>

using namespace std;

// Positions of Large Groups - Easy

// In a string s of lowercase letters, these letters form consecutive groups of the same character.

// For example, a string like s = "abbxxxxzyy" has the groups "a", "bb", "xxxx", "z", and "yy".

// A group is identified by an interval [start, end], where start and end denote the start and end indices (inclusive) of the group. In the above example, "xxxx" has the interval [3,6].

// A group is considered large if it has 3 or more characters.

// Return the intervals of every large group sorted in increasing order by start index.

class Solution
{
public:
    vector<vector<int>> largeGroupPositions(string s)
    {
        vector<vector<int>> res;
        char c = s[0];
        int start = 0;
        int end = 0;
        int length = 1;
        for (int i = 1; i < s.size(); ++i)
        {
            if (s[i] == c)
            {
                end = i;
            }
            else
            {
                length = end - start + 1;
                if (length >= 3)
                    res.push_back({start, end});
                start = i;
                end = i;
                c = s[i];
            }
        }

        length = end - start + 1;
        if (length >= 3)
            res.push_back({start, end});

        return res;
    }
};