#include <vector>

using namespace std;

class Solution
{
public:
    int confusingNumberII(int N)
    {
        if (N < 6)
            return 0;
        if (N < 9)
            return 1;
        if (N < 10)
            return 2;

        return construction(N);
    }

    int construction(int N)
    {
        // construct every number < N which is confusing
        // so, every number made up of confusing numbers which is not a palindrome
        // we can construct all possible combinations of potentially confusing digits using a sort of DFS
        // starting from a digit {1, 6, 8, 9}, dfs
        //   at a number, like 1, my next step is to multiply by 10 and add one of the possible digits:
        //     1 ->   { 10, 11, 16, 18, 19 }
        //     10 ->  { 100, 101, 106, 108, 109 }
        //     100 -> { 1000, 1001, 1006, 1009 }
        //   etc.
        // when one of these numbers is confusing, increment count

        int count = 2;
        vector<int> numbers = {0, 1, 6, 8, 9};
        for (int i = 1; i < numbers.size(); ++i)
            generateNumbers(numbers, numbers[i], N, count);

        return count;
    }

    void generateNumbers(vector<int> &numbers, long long num, int N, int &count)
    {
        if (num > N)
            return;
        for (int i : numbers)
        {
            // try adding this number after num
            long long temp = num * 10 + i;
            if (temp > N)
                return;

            int result = flip(temp);
            if (result != temp)
                ++count;
            generateNumbers(numbers, temp, N, count);
        }
    }

    int flip(long long t)
    {
        int result = 0;
        while (t > 0)
        {
            int d = t % 10;
            result *= 10;
            if (d == 1 || d == 8)
                result += d;
            if (d == 6)
                result += 9;
            if (d == 9)
                result += 6;
            t /= 10;
        }
        return result;
    }

    // iterate through numbers smaller than N, check if they're confusing
    int naive(int N)
    {
        int confusedNumbers = 0;
        for (int i = 0; i < N; ++i)
            if (isConfusing(i + 1))
                ++confusedNumbers;
        return confusedNumbers;
    }

    bool isConfusing(int i)
    {
        // walk through digits
        // if any digits are invalid, return false;
        // compute the entire flipped number
        int num{i};
        vector<int> digits;
        while (num > 0)
        {
            int d = num % 10;
            if (d == 2 || d == 3 || d == 4 || d == 5 || d == 7)
                return false;
            if (d == 0 || d == 1 || d == 8)
                digits.push_back(d);
            else if (d == 6)
                digits.push_back(9);
            else
                digits.push_back(6);
            num /= 10;
        }

        int power = 1;
        int flipped = 0;
        for (int i = digits.size() - 1; i >= 0; --i)
        {
            flipped += digits[i] * power;
            power *= 10;
        }

        return i != flipped;
    }
};