#include <string>
#include <bitset>
using namespace std;

// Binary String With Substrings Representing 1 To N - Medium

// Given a binary string S (a string consisting only of '0' and '1's) and a positive integer N, return true if and only if for every integer X from 1 to N, the binary representation of X is a substring of S.

class Solution {
public:
    bool queryString(string S, int N) {
        while (N > 0){
            string s = bitset<32>(N).to_string();
            
            if (S.find(s.substr(s.find('1'))) == string::npos) return false;
            
            --N;
        }
        
        return true;
    }
};