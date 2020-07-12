#include <limits>
#include <string>
using namespace std;

// String to Integer (atoi) - Medium

// Implement atoi which converts a string to an integer.
// The function first discards as many whitespace characters as necessary until the first non-whitespace character is found. 
// Then, starting from this character, takes an optional initial plus or minus sign followed by as many 
// numerical digits as possible, and interprets them as a numerical value.
// The string can contain additional characters after those that form the integral number, 
// which are ignored and have no effect on the behavior of this function.
// If the first sequence of non-whitespace characters in str is not a valid integral number, 
// or if no such sequence exists because either str is empty or it contains only whitespace characters, 
// no conversion is performed.
// If no valid conversion could be performed, a zero value is returned.
// Note:
// Only the space character ' ' is considered as whitespace character.
// Assume we are dealing with an environment which could only store integers within the 32-bit signed integer range: 
// [−231,  231 − 1]. If the numerical value is out of the range of representable values, INT_MAX (231 − 1) or 
// INT_MIN (−231) is returned.

class Solution {
public:
    int myAtoi(string str) {
        int ret(0);
        int high(INT_MAX / 10);
        int highDigit(INT_MAX % 10);
        int low(INT_MIN / 10);
        int lowDigit(INT_MIN % 10);
        
        int i (0);
        bool intFound(false);
        int negate(1);
        for (int i = 0; i != str.size(); ++i) {
            // discard leading whitespace
            if (!intFound && str[i] == ' ') continue;
            
            // register first leading + or -
            if (!intFound && (str[i] == '-' || str[i] == '+')) {
                intFound = true;
                negate = str[i] == '-' ? -1 : 1;
                continue;
            }
            
            // invalid character, return ret
            if (!isdigit(str[i])) return ret;
            
            int digit = (str[i] - '0') * negate;
            
            if (ret > high || ret == high && digit > highDigit) return INT_MAX;
            if (ret < low || ret == low && digit < lowDigit) return INT_MIN;
            
            ret = ret * 10 + digit;
            
            
            intFound = true;
        }
        
        return ret;
    }
};