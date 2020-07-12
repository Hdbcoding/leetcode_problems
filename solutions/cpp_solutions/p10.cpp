#include <string>
#include <vector>
using namespace std;

// Regular Expression Matching - Hard

// Given an input string (s) and a pattern (p), implement regular expression matching with support for '.' and '*'.
// '.' Matches any single character.
// '*' Matches zero or more of the preceding element.
// The matching should cover the entire input string (not partial).

// Note:

// s could be empty and contains only lowercase letters a-z.
// p could be empty and contains only lowercase letters a-z, and characters like . or *.

class Solution {
public:
    bool isMatch(string s, string p) {
        if (p.empty()) return s.empty();
        // memo table
        vector<vector<bool>> memo(s.size() + 1, vector<bool>(p.size() + 1, false));
        memo[s.size()][p.size()] = true;
        
        for (int i = s.size(); i >= 0; --i)
        for (int j = p.size() - 1; j >= 0; --j){
            // is the current character available to be repeated or deleted?
            bool repeat = j + 1 < p.size() && p[j+1] == '*';
            
            // if the current character is marked with '*'
            // then this part of the string is valid the string matches the rest of the pattern
            if (repeat && memo[i][j + 2]){
                memo[i][j] = memo[i][j+2];
                continue;
            }
            
            // matching character? (or wildcard)
            bool match = i < s.size() && (p[j] == s[i] || p[j] == '.');
            // mismatched characters -> this part of the string doesn't match the pattern
            if (!match) continue;
            
            // if we have a matching character, this part of the string is good 
            //   if the rest of the string matches the rest of the pattern
            int nextJ = repeat ? j : j + 1;
            memo[i][j] = memo[i+1][nextJ];
        }
        return memo[0][0];
    }
};