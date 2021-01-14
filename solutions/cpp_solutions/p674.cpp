#include <vector>
using namespace std;

// Longest Continuous Increasing Subsequence - Easy

// Given an unsorted array of integers nums, return the length of the longest continuous increasing subsequence (i.e. subarray). 
//  The subsequence must be strictly increasing.

// A continuous increasing subsequence is defined by two indices l and r (l < r) such that it is [nums[l], nums[l + 1], 
// ..., nums[r - 1], nums[r]] and for each l <= i < r, nums[i] < nums[i + 1].

class Solution {
public:
    int findLengthOfLCIS(vector<int>& nums) {
        if (nums.size() == 0)
            return 0;

        int maxLength = 0;
        int start = 0;
        for (int i = 1; i < nums.size(); ++i){
            if (nums[i] <= nums[i-1]){
                maxLength = max(maxLength, i - start);
                start = i;
            }
        }
        maxLength = max(maxLength, (int)nums.size() - start);

        return maxLength;
    }
};