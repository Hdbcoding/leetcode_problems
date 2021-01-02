#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <set>
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
    // this guy times out
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

    vector<int> getVector(int a, int b, int c)
    {
        vector<int> triplet{a, b, c};
        sort(triplet.begin(), triplet.end());
        return triplet;
    }

    // slow, but fast enough to pass.
    // n^2 runtime, no sorting of the input array
    // ~750ms
    vector<vector<int>> withMap(vector<int> &nums)
    {
        // count the number of times each element appears
        unordered_map<int, int> numCounts;

        for (int i = 0; i < nums.size(); i++)
        {
            numCounts[nums[i]]++;
        }

        set<vector<int>> result;
        int currentSum = 0;
        std::unordered_map<int, int>::const_iterator got;
        for (auto it = numCounts.begin(); it != numCounts.end(); ++it)
        {
            currentSum = it->first;
            it->second--;

            // if it appears twice, see if that works
            if (it->second > 0)
            {
                currentSum += it->first;
                it->second--;

                got = numCounts.find(-1 * currentSum);
                if (got != numCounts.end() && got->second > 0)
                    result.insert(getVector(it->first, it->first, got->first));
                currentSum -= it->first;
                it->second++;
            }

            // it once, then something else, then something else
            for (auto that = next(it); that != numCounts.end(); ++that)
            {
                if (that->second > 0)
                {
                    currentSum += that->first;
                    that->second--;

                    got = numCounts.find(-1 * currentSum);
                    if (got != numCounts.end() && got->second > 0)
                        result.insert(getVector(it->first, that->first, got->first));

                    that->second++;
                    currentSum -= that->first;
                }
            }
        }

        return {result.begin(), result.end()};
    }

    // runtine n^2
    // two-pointer solution
    // ~80ms
    vector<vector<int>> twoPointer(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        vector<vector<int>> result;
        vector<int> current;

        for (int i = 0; i < nums.size() - 2; ++i)
        {
            // skip duplicating this num
            if (i > 0 && nums[i] == nums[i - 1])
                continue;
            int lo = i + 1;
            int hi = nums.size() - 1;
            while (lo < hi)
            {
                int sum = nums[i] + nums[lo] + nums[hi];
                if (sum < 0)
                {
                    ++lo;
                }
                else if (sum > 0)
                {
                    --hi;
                }
                else
                {
                    result.push_back({nums[i], nums[lo], nums[hi]});
                    // do
                    // {
                        --hi;
                    // } while (lo < hi && nums[hi] == nums[hi - 1]);
                    do
                    {
                        ++lo;
                    } while (lo < hi && nums[lo] == nums[lo - 1]);
                }
            }
        }

        return result;
    }

    // runtime n^2
    // ~1800ms what why so much slower than two pointer??
    vector<vector<int>> withMapAndSorting(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        vector<vector<int>> result;

        for (int i = 0; i < nums.size(); ++i)
        {
            if (nums[i] > 0)
                break;
            if (i > 0 && nums[i] == nums[i - 1])
                continue;

            unordered_set<int> seen;
            for (int j = i + 1; j < nums.size(); ++j)
            {
                int complement = -nums[i] - nums[j];
                if (seen.count(complement))
                {
                    result.push_back({nums[i], complement, nums[j]});
                    while (j + 1 < nums.size() && nums[j] == nums[j + 1])
                        ++j;
                }
                seen.insert(nums[j]);
            }
        }

        return result;
    }

    vector<vector<int>> threeSum(vector<int> &nums)
    {
        if (nums.size() < 3)
            return {};
        // return bruteForce(nums);
        // return withMap(nums);
        return twoPointer(nums);
        // return withMapAndSorting(nums);
    }
};