#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

// 3Sum - Medium

// Given an array nums of n integers, are there elements a, b, c in nums such that a + b + c = 0?
// Find all unique triplets in the array which gives the sum of zero.
// Notice that the solution set must not contain duplicate triplets.

// Example 1:
// Input: nums = [-1,0,1,2,-1,-4]
// Output: [[-1,-1,2],[-1,0,1]]

// Example 2:
// Input: nums = []
// Output: []

// Example 3:
// Input: nums = [0]
// Output: []

// Constraints:
// 0 <= nums.length <= 3000
// -105 <= nums[i] <= 105

class Solution
{
public:
    bool sumIsZero(vector<int> &nums)
    {
        return (nums[0] + nums[1] + nums[2]) == 0;
    }

    bool isSimilar(vector<int> &l, vector<int> &r)
    {
        return l[0] == r[0] && l[1] == r[1] && l[2] == r[2];
    }

    bool noSimilarTriples(vector<vector<int>> &result, vector<int> &current)
    {
        for (int i = 0; i < result.size(); i++)
        {
            if (isSimilar(result[i], current))
                return false;
        }
        return true;
    }

    // runtime n^3
    // space only limited by the size of the solution set (i.e., number of triples)
    vector<vector<int>> bruteForce(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        vector<vector<int>> result;
        vector<int> current;

        for (int i = 0; i < nums.size() - 2; ++i)
        {
            current.push_back(nums[i]);
            for (int j = i + 1; j < nums.size() - 1; ++j)
            {
                current.push_back(nums[j]);
                for (int k = j + 1; k < nums.size(); ++k)
                {
                    current.push_back(nums[k]);

                    if (sumIsZero(current) && noSimilarTriples(result, current))
                        result.push_back({current});

                    current.pop_back();
                }
                current.pop_back();
            }
            current.pop_back();
        }

        return result;
    }

    vector<vector<int>> withMap(vector<int> &nums)
    {
        // count the number of times each element appears
        unordered_map<int, int> numCounts;

        for (int i = 0; i < nums.size(); i++)
        {
            numCounts[nums[i]]++;
        }

        vector<vector<int>> result;
        int currentSum = 0;
        std::unordered_map<int, int>::const_iterator got;
        for (auto it = numCounts.begin(); it != numCounts.end(); ++it)
        {
            currentSum = it->first;

            // if it appears twice, see if that works
            if (it->second > 1)
            {
                currentSum += it->first;
                got = numCounts.find(-1 * currentSum);
                if (got != numCounts.end())
                    result.push_back({it->first, it->first, got->first});
                currentSum -= it->first;
            }

            // if current sum is even, check for a double
            if (currentSum % 2 == 0)
            {
                got = numCounts.find(-1 * currentSum / 2);
                if (got != numCounts.end() && got->second > 1)
                {
                    result.push_back({it->first, got->first, got->first});
                }
            }

            // it once, then something else, then something else
            for (auto that = next(it); that != numCounts.end(); ++that)
            {
                currentSum += that->first;
                // already covered this case in the mod2 check above
                if (currentSum != -1 * that->first)
                {
                    got = numCounts.find(-1 * currentSum);
                    if (got != numCounts.end())
                        result.push_back({it->first, that->first, got->first});
                }

                currentSum -= that->first;
            }
        }

        return result;
    }

    vector<vector<int>> threeSum(vector<int> &nums)
    {
        if (nums.size() < 3)
            return {};
        // return bruteForce(nums);
        return withMap(nums);
    }
};