#include <string>
#include <vector>
#include <sstream>
#include <cmath>
using namespace std;

// Letter Combinations of a Phone Number - Medium

// Given a string containing digits from 2-9 inclusive,
// return all possible letter combinations that the number could represent.
// Return the answer in any order.

// A mapping of digit to letters (just like on the telephone buttons) is given below. Note that 1 does not map to any letters.

// 0 <= digits.length <= 4
// digits[i] is a digit in the range ['2', '9'].

class Solution
{
    const vector<vector<char>> map{
        {'a', 'b', 'c'},
        {'d', 'e', 'f'},
        {'g', 'h', 'i'},
        {'j', 'k', 'l'},
        {'m', 'n', 'o'},
        {'p', 'q', 'r', 's'},
        {'t', 'u', 'v'},
        {'w', 'x', 'y', 'z'}};

public:
    vector<char> getMap(char digit)
    {
        int i = digit - '0';
        // 2 -> 0
        return map[i - 2];
    }

    void addDigit(vector<string> &result, char c)
    {
        vector<char> letters = getMap(c);
        if (result.size() == 0)
        {
            for (char l : letters)
                result.push_back({l});
        }
        else
        {
            int arr_length = result.size();
            int word_length = result[0].size();
            // reserve enough space for the words to be added (only does something if more space needed)
            result.reserve(arr_length * letters.size());

            // add a new word for each old word and each letter
            for (int i = 0; i < arr_length; ++i)
            {
                for (int j = 1; j < letters.size(); ++j)
                {
                    result.push_back(result[i] + letters[j]);
                }
            }

            // update each old word
            for (int i = 0; i < arr_length; ++i)
            {
                result[i] = result[i] + letters[0];
            }
        }
    }

    // i mean, it does only the work asked, but it is still exponential time
    // O(3^N * 4^M) where N is digits.where(n in set {2,3,4,5,6,8}), N is digits.where(n in set {7,9})
    vector<string> bruteForce(string digits)
    {
        vector<string> result{};
        // reserve enough space for at least 3 letters per digit
        result.reserve(pow(3, digits.size()));
        for (char c : digits)
        {
            addDigit(result, c);
        }
        return result;
    }

    vector<string> letterCombinations(string digits)
    {
        return bruteForce(digits);
    }
};
