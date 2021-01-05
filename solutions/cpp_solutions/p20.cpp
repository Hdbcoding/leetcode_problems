#include <string>
#include <vector>
using namespace std;

// Valid Parentheses - Easy

// Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

// An input string is valid if:

// Open brackets must be closed by the same type of brackets.
// Open brackets must be closed in the correct order.

class Solution {
public:
    bool isValid(string s) {
        if (s.size() == 0) return true;

        vector<char> closing;
        for (char c : s){
            if (c == '[')
                closing.push_back(']');
            else if (c == '{')
                closing.push_back('}');
            else if (c == '(')
                closing.push_back(')');
            else {
                if (closing.size() == 0)
                    return false;
                if (closing.back() != c)
                    return false;
                closing.pop_back();
            }
        }

        return closing.size() == 0;
    }
};
