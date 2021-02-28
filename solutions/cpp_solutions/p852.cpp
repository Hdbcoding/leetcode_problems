#include <vector>

using namespace std;

// Peak index in a mountain array - Easy

// Let's call an array arr a mountain if the following properties hold:

// arr.length >= 3
// There exists some i with 0 < i < arr.length - 1 such that:
// arr[0] < arr[1] < ... arr[i-1] < arr[i]
// arr[i] > arr[i+1] > ... > arr[arr.length - 1]
// Given an integer array arr that is guaranteed to be a mountain, return any i such that arr[0] < arr[1] < ... arr[i - 1] < arr[i] > arr[i + 1] > ... > arr[arr.length - 1].

class Solution
{
public:
    int peakIndexInMountainArray(vector<int> &arr)
    {
        int l = 1;
        int r = arr.size() - 2;
        while (l < r)
        {
            int m = (l + r) / 2;

            bool isIncreasingLeft = isIncreasing(arr, m - 1);
            bool isIncreasingRight = isIncreasing(arr, m);

            bool isPeak = isIncreasingLeft && !isIncreasingRight;
            if (isPeak)
                return m;

            bool goRight = isIncreasingLeft && isIncreasingRight;
            if (goRight)
            {
                l = m + 1;
            }
            else
            {
                r = m - 1;
            }
        }
        return l;
    }

    bool isIncreasing(vector<int> &arr, int i)
    {
        return arr[i] < arr[i + 1];
    }

    bool isPeak(vector<int> &arr, int i)
    {
        return isIncreasing(arr, i - 1) && !isIncreasing(arr, i);
    }
};