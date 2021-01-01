#include <vector>
#include <string>
#include <sstream>
using namespace std;

// Longest Common Prefix - Easy

// Write a function to find the longest common prefix string amongst an array of strings.
// If there is no common prefix, return an empty string "".

class Solution
{
public:
    string getPrefix(const string &left, const string &right)
    {
        int i{0};
        while (left[i] == right[i] && i < left.size() && i < right.size())
            i++;
        return left.substr(0, i);
    }


    string linear(vector<string> &strs)
    {
        string prefix = strs[0];

        for (int i = 1; i < strs.size(); i++)
        {
            prefix = getPrefix(strs[i], prefix);
            if (prefix.size() == 0)
                break;
        }

        return prefix;
    }

    // a divide and conquer approach doesn't necessarily reduce the runtime
    // but it does increase the space requirement
    // it might run faster only in cases where short prefixes just happen to be found sooner than they would be in a linear scan
    string dcRecursive(vector<string> &strs, int l, int r)
    {
        if (l == r)
            return strs[l];

        int mid = (l + r) / 2;
        string left = dcRecursive(strs, l, mid);
        string right = dcRecursive(strs, mid + 1, r);
        return getPrefix(left, right);
    }

    string longestCommonPrefix(vector<string> &strs)
    {
        if (strs.size() == 0)
            return "";
        if (strs.size() == 1)
            return strs[0];

        // return linear(strs);
        return dcRecursive(strs, 0, strs.size() - 1);
    }
};