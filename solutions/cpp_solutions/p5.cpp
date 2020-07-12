#include <string>
#include <algorithm>
using namespace std;

// Longest Palindromic Substring - Medium

// Given a string s, find the longest palindromic substring in s. 
// You may assume that the maximum length of s is 1000.

class Solution {
public:
    string longestPalindrome(string s) {
        if (s.empty()) return "";
        
        int st = 0, w = 0;
        
        for (int i = 0; i != s.size(); i++){
            int odd = width(s, i, i);
            int even = width(s, i, i+1);
            int width = max(odd, even);
            w = max(w, width);
            st = w == width ? (i - (width-1) / 2) : st;
        }
        
        return s.substr(st, w);
    }
    
    int width(const string &s, int l, int r){
        while (l >= 0 && r < s.size() && s[l] == s[r]) {
            l--;
            r++;
        }
        return r - l - 1;
    }
};