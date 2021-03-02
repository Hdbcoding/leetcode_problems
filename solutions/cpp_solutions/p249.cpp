#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

// Group shifted strings - Medium

// Given a string, we can "shift" each of its letter to its successive letter, for example: "abc" -> "bcd". We can keep "shifting" which forms the sequence:

// "abc" -> "bcd" -> ... -> "xyz"
// Given a list of non-empty strings which contains only lowercase alphabets, group all strings that belong to the same shifting sequence.


class Solution
{
public:
    vector<vector<string>> groupStrings(vector<string> &strings)
    {
        // build a map from a characteristic string to all similar strings
        unordered_map<string, vector<string>> forest;
        for (auto &a : strings)
            forest[getKey(a)].push_back(a);

        vector<vector<string>> result;
        for (auto &kvp : forest)
            result.push_back(kvp.second);
        return result;
    }

    string getKey(const string &a)
    {
        if (a.size() == 1)
            return "a";
        
        // get a characteristic string based on this string
        string key(a);
        key[0] = 'a';
        for (int i = 1; i < a.size(); ++i)
        {
            // modular calculation of the next character based on the previous character
            int diff = a[i] - a[i - 1];
            if (diff < 0)
                diff += 26;
            key[i] = key[i - 1] + diff;
        }
        return key;
    }
};