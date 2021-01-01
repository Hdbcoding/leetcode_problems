#include <unordered_map>
#include <string>
using namespace std;

// Roman to Integer - Easy
// For example, 2 is written as II in Roman numeral, just two one's added together.
// 12 is written as XII, which is simply X + II.
// The number 27 is written as XXVII, which is XX + V + II.

// Roman numerals are usually written largest to smallest from left to right.
// However, the numeral for four is not IIII.
// Instead, the number four is written as IV.
// Because the one is before the five we subtract it making four.
// The same principle applies to the number nine, which is written as IX.
// There are six instances where subtraction is used:

// I can be placed before V (5) and X (10) to make 4 and 9.
// X can be placed before L (50) and C (100) to make 40 and 90.
// C can be placed before D (500) and M (1000) to make 400 and 900.
// Given a roman numeral, convert it to an integer.

class Solution
{
public:
    const unordered_map<char, int> numerals{
        {'M', 1000},
        {'D', 500},
        {'C', 100},
        {'L', 50},
        {'X', 10},
        {'V', 5},
        {'I', 1}};

    bool isPowerOfTen(int v)
    {
        while (v > 9 && v % 10 == 0)
            v /= 10;
        return v == 1;
    }

    int romanToInt(string s)
    {
        int lastVal{numerals.at(s[s.size() - 1])};
        int result{lastVal};
        for (int i = s.size() - 2; i >= 0; --i)
        {
            int current = numerals.at(s[i]);
            if (current < lastVal)
                result -= current;
            else
                result += current;
            lastVal = current;
        }
        return result;
    }
};