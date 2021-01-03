#include <vector>
#include <algorithm>
using namespace std;

// 4Sum - Medium

// Given an array nums of n integers and an integer target,
// are there elements a, b, c, and d in nums such that a + b + c + d = target?
// Find all unique quadruplets in the array which gives the sum of target.

// Notice that the solution set must not contain duplicate quadruplets.

// Constraints:
// 0 <= nums.length <= 200
// -109 <= nums[i] <= 109
// -109 <= target <= 109

class Solution
{
public:
    // runtime n^3
    // 68ms
    // pretty much the same as p15, just with an extra loop layer
    vector<vector<int>> twoPointer(vector<int> &nums, int target)
    {
        sort(nums.begin(), nums.end());
        vector<vector<int>> result;
        vector<int> current;

        for (int i = 0; i < nums.size() - 3; ++i)
        {
            // skip duplicating this num
            if (i > 0 && nums[i] == nums[i - 1])
                continue;

            for (int j = i + 1; j < nums.size() - 2; ++j)
            {
                // skip duplicating this num
                if (j > i + 1 && nums[j] == nums[j - 1])
                    continue;

                int lo = j + 1;
                int hi = nums.size() - 1;
                while (lo < hi)
                {
                    int sum = nums[i] + nums[j] + nums[lo] + nums[hi];
                    if (sum < target)
                    {
                        ++lo;
                    }
                    else if (sum > target)
                    {
                        --hi;
                    }
                    else
                    {
                        result.push_back({nums[i], nums[j], nums[lo], nums[hi]});
                        do
                        {
                            --hi;
                        } while (lo < hi && nums[hi] == nums[hi + 1]);
                        do
                        {
                            ++lo;
                        } while (lo < hi && nums[lo] == nums[lo - 1]);
                    }
                }
            }
        }

        return result;
    }

    vector<vector<int>> fourSum(vector<int> &nums, int target)
    {
        if (nums.size() < 4)
            return {};
        return twoPointer(nums, target);
    }
};