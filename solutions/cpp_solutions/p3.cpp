#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

// Longest Substring Without Repeating Characters - Medium
// Given a string, find the length of the longest substring without repeating characters.

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> set{};
        int maxLength{0};
        int start{0};
        int i{0};
        for (; i != s.size(); ++i){
            unordered_map<char,int>::const_iterator got = set.find(s.at(i));
            if (got != set.end() && got->second >= start)
                start = got->second + 1;
            set[s.at(i)] = i;
            maxLength = max(maxLength, i - start + 1);
        }
        maxLength = max(maxLength, i - start);
        return maxLength;
    }
};