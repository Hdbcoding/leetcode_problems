#include <vector>
#include <utility>
#include <sstream>
using namespace std;

// Integer to Roman - Medium
// Roman numerals are represented by seven different symbols: I, V, X, L, C, D and M.
// For example, 2 is written as II in Roman numeral, just two one's added together.
// 12 is written as XII, which is simply X + II. The number 27 is written as XXVII, which is XX + V + II.
// Roman numerals are usually written largest to smallest from left to right.
// However, the numeral for four is not IIII.
// Instead, the number four is written as IV.
// Because the one is before the five we subtract it making four.
// The same principle applies to the number nine, which is written as IX.
// There are six instances where subtraction is used:
// - I can be placed before V (5) and X (10) to make 4 and 9.
// - X can be placed before L (50) and C (100) to make 40 and 90.
// - C can be placed before D (500) and M (1000) to make 400 and 900.
// Given an integer, convert it to a roman numeral.

struct NumeralBlock
{
    int roof;
    char tens;
    char fives;
    char ones;

    void parsePlace(int num, stringstream &ss) const
    {
        switch (num){
            case 1:
                ss << ones;
                break;
            case 2:
                ss << ones << ones;
                break;
            case 3:
                ss << ones << ones << ones;
                break;
            case 4:
                ss << ones << fives;
                break;
            case 5:
                ss << fives;
                break;
            case 6:
                ss << fives << ones;
                break;
            case 7:
                ss << fives << ones << ones;
                break;
            case 8:
                ss << fives << ones << ones << ones;
                break;
            case 9:
                ss << ones << tens;
                break;
        }
    }
};

class Solution
{
    const vector<NumeralBlock> numerals
    {
        { 1000, 'E', 'E', 'M' },
        { 100, 'M', 'D', 'C' },
        { 10, 'C', 'L', 'X' },
        { 1, 'X', 'V', 'I' }
    };

public:
    string intToRoman(int num)
    {
        stringstream ss;

        for (int i = 0; i < numerals.size(); ++i){
            numerals[i].parsePlace(num / numerals[i].roof, ss);
            num = num % numerals[i].roof;
        }

        return ss.str();
    }
};