#include <vector>
#include <unordered_map>
using namespace std;

// Two Sum - Easy
// Given an array of integers, return indices of the two numbers such that they add up to a specific target.
// You may assume that each input would have exactly one solution, and you may not use the same element twice.

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int,int> set{};
        
        for (int i = 0; i != nums.size(); ++i){
            unordered_map<int,int>::const_iterator got = set.find(target - nums[i]);
            if (got != set.end()) {
                return { got->second, i };
            }
            set[nums[i]] = i;
        }
        return {};
    }
};