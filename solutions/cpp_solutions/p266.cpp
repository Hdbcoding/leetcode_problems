#include <unordered_map>
#include <string>
using namespace std;

// Palindrome Permutation - Easy
// Given a string, determine if a permutation of the string could form a palindrome.

class Solution
{
public:
    bool canPermutePalindrome(string s)
    {
        unordered_map<char, int> counts;
        for (char c : s)
        {
            counts[c]++;
        }

        bool sawOdd = false;
        for (auto &pair : counts)
        {
            if (pair.second % 2 == 1)
            {
                if (sawOdd)
                    return false;
                sawOdd = true;
            }
        }
        return true;
    }
};