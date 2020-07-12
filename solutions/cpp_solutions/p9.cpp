#include <limits>

// Palindrome number - Easy

// Determine whether an integer is a palindrome. An integer is a palindrome when it reads the same backward as forward.
// Negative numbers cannot be palindromes

class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) return false;
        return x == reverse(x);
    }
    
    int reverse(int x){
        int ret(0);
        int high = INT_MAX / 10;
        int highDigit = INT_MAX % 10;
        
        while (x != 0){
            int digit = x % 10;
            x /= 10;
            
            if (ret > high
                || (ret == high && digit > highDigit))
                return 0;
            
            ret = ret * 10 + digit;
        }
        
        return ret;
    }
};