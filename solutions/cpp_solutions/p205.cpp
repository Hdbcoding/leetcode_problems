#include <string>
#include <unordered_map>
using namespace std;

// Isomorphic strings

// Given two strings s and t, determine if they are isomorphic.

// Two strings s and t are isomorphic if the characters in s can be replaced to get t.

// All occurrences of a character must be replaced with another character while preserving the order of characters. 
// No two characters may map to the same character, but a character may map to itself.


class Solution {
public:
    bool isIsomorphic(string s, string t) {
        if (s.size() <= 1) return true;
        
        unordered_map<char,char> s_to_t;
        unordered_map<char,char> t_to_s;
        
        for (int i = 0; i < s.size(); ++i){
            char sc = s[i];
            char tc = t[i];
            
            auto founds = s_to_t.find(sc);
            auto foundt = t_to_s.find(tc);
            
            if (founds == s_to_t.end() && foundt == t_to_s.end())
            {
                s_to_t[sc] = tc;
                t_to_s[tc] = sc;
            }
            else if (founds != s_to_t.end() && foundt != t_to_s.end())
            {
                if (founds->second != tc) return false;
                if (foundt->second != sc) return false;
            }
            else return false;
        }
        return true;
    }
};