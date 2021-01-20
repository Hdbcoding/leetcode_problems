#include <string>
#include <stack>
#include <sstream>
using namespace std;
// Decode String - Medium

// Given an encoded string, return its decoded string.

// The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is being repeated exactly k times. 
// Note that k is guaranteed to be a positive integer.

// You may assume that the input string is always valid; No extra white spaces, square brackets are well-formed, etc.

// Furthermore, you may assume that the original data does not contain any digits and that digits are only for those repeat numbers, k. 
// For example, there won't be input like 3a or 2[4].

class Solution {
public:
    string decodeString(string s) {
        stack<int> counts;
        stack<stringstream*> builders;
        stringstream *current = new stringstream();
        int k = 0;
        for (char c : s){
            if (isdigit(c)){
                k = k * 10 + c - '0';
            } else if (c == '['){
                counts.push(k);
                builders.push(current);
                current = new stringstream();
                k = 0;
            } else if (c == ']') {
                string currentString = current->str();
                int count = counts.top();
                counts.pop();
                stringstream *decoded = builders.top();
                builders.pop();
                for (int i = 0; i < count; ++i)
                    (*decoded) << currentString;
                delete current;
                current = decoded;
            } else {
                (*current) << c;
            }
        }
        return current->str();
    }
};