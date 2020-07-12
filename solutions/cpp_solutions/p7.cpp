#include <limits>

// Reverse Integer - Easy

// Given a 32-bit signed integer, reverse digits of an integer.

// Assume we are dealing with an environment which could only store 
// integers within the 32-bit signed integer range: [−231,  231 − 1]. 
// For the purpose of this problem, assume that your function returns 0 when the reversed integer overflows.

class Solution {
public:
    int reverse(int x) {
        int ret(0);
        int high = INT_MAX / 10;
        int highDigit = INT_MAX % 10;
        int low = INT_MIN / 10;
        int lowDigit = INT_MIN % 10;
        
        while (x != 0){
            int digit = x % 10;
            x /= 10;
            
            if (ret > high
                || ret < low
                || (ret == high && digit > highDigit)
                || (ret == low && digit < lowDigit))
                return 0;
            
            ret = ret * 10 + digit;
        }
        
        return ret;
    }
};