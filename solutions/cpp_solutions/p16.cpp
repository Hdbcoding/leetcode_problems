#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

// 3Sum Closest - Medium

// Given an array nums of n integers and an integer target, find three integers in nums such that the sum is closest to target.
// Return the sum of the three integers.
// You may assume that each input would have exactly one solution.

// Input: nums = [-1,2,1,-4], target = 1
// Output: 2
// Explanation: The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).

// Constraints:

// 3 <= nums.length <= 10^3
// -10^3 <= nums[i] <= 10^3
// -10^4 <= target <= 10^4

class Solution
{
public:
    int closer(int target, int a, int b)
    {
        int diffA{abs(a - target)}, diffB{abs(b - target)};
        if (diffA <= diffB)
            return a;
        return b;
    }

    // runtime O(n^3), extra space O(1)
    // actually is just barely accepted at around 880ms
    int bruteForce(vector<int> &nums, int target)
    {
        int result{nums[0] + nums[1] + nums[2]};

        for (int i = 0; i < nums.size(); ++i)
            for (int j = i + 1; j < nums.size(); ++j)
                for (int k = j + 1; k < nums.size(); ++k)
                    result = closer(target, result, nums[i] + nums[j] + nums[k]);

        return result;
    }

    // runtime O(n^2), extra space O(1)
    // but, it does sort the incoming array, which may not be acceptable
    // ~12ms, quite a bit faster than brute force
    int twoVector(vector<int> &nums, int target)
    {
        sort(nums.begin(), nums.end());
        int result{nums[0] + nums[1] + nums[2]};

        for (int i = 0; i < nums.size(); ++i)
        {
            // skip duplicating this num
            if (i > 0 && nums[i] == nums[i - 1])
                continue;

            int lo = i + 1;
            int hi = nums.size() - 1;

            while (lo < hi)
            {
                int sum = nums[i] + nums[lo] + nums[hi];
                result = closer(target, result, sum);
                if (sum < target)
                {
                    ++lo;
                }
                else if (sum > target)
                {
                    --hi;
                }
                else
                    return target;
            }
        }

        return result;
    }

    int threeSumClosest(vector<int> &nums, int target)
    {
        if (nums.size() < 3)
            return 0;
        if (nums.size() == 3)
            return nums[0] + nums[1] + nums[2];

        // return bruteForce(nums, target);
        return twoVector(nums, target);
    }
};