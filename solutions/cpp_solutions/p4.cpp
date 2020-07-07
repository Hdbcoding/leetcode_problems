#include <vector>
#include <algorithm>
using namespace std;

// Median of Two Sorted Arrays - Hard
// There are two sorted arrays nums1 and nums2 of size m and n respectively.
// Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).
// You may assume nums1 and nums2 cannot be both empty.

class Solution
{
public:
    double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
    {
        return findMedianSortedArraysEasy(nums1, nums2);
    }

    // easy solution - put everything in a sorted vector and return the median of that
    // violates the problem statement's time constraint
    double findMedianSortedArraysEasy(vector<int> &nums1, vector<int> &nums2)
    {
        vector<int> all(nums1.size() + nums2.size());
        vector<int>::const_iterator it1 = nums1.begin(), it2 = nums2.begin();
        // O(n) construction of combined vector via interleaving, like merge sort
        for (auto &elem : all)
        {
            if (it1 != nums1.end() && (it2 == nums2.end() || (*it1) < (*it2)))
                elem = *it1++;
            else
                elem = *it2++;
        }
        size_t mid = all.size() / 2;
        return all.size() % 2 == 0
                   ? (all[mid - 1] + all[mid]) / 2.0
                   : all[mid];
    }

    // idea - median is at the center of the combined set { nums1 + nums2 }
    // I want a binary search like speed
    // So I want a binary search on candidates of nums1 and nums2 that could conceivably be the pair involved in a median cut
    // an index in a single set identifies the median if it cuts the set in half
    // for two sets, we need two indices that don't necessarily cut their own set in half,
    //  but combined cut the two sets in half together
    // for 11 total elements, 4 in nums1, 7 in nums2
    // possibilities:
    //  {0,5} (median is smaller than all of nums1)   [0,1,2,3,4, 5,  6][0,1,2,3]
    //  {1, 4}                                        [0][0,1,2,3] [1, 2,3][4, 5,6]
    //  {2, 3}                                        [0,1][0,1,2] [2, 3][3, 4,5,6]
    //  {3, 2}                                        [0,1,2][0,1] [3][2, 3,4,5,6]
    //  {4, 1}  (median is greater than all of nums1) [0,1,2,3][0, 1,   2,3,4,5,6]
    // for 10 total elements, 4 in nums1, 6 in nums2
    double findMedianSortedArraysHard(vector<int> &nums1, vector<int> &nums2)
    {
        if (nums1.size() > nums2.size())
            return findMedianSortedArraysHard(nums2, nums1);

        int m = nums1.size();
        int n = nums2.size();
        int half = (m + n + 1) / 2;
        bool even = ((m + n) % 2) == 0;
        int l = 0;
        int r = m;

        while (l <= r){
            int i = (l + r) / 2;
            int j = half - i;

            // case 1 - the cut of nums1 is too low, go higher in nums1
            if (i < r && nums2[j-1] > nums1[i])
                l = i + 1;
            // case 2 - the cut of nums1 is too high, go lower in nums1
            else if (i > l && nums1[i-1] > nums2[j])
                r = i - 1;
            else {
                // this cut of nums1 captures the median
                int maxLeft;
                // if at bottom of nums1, max of left is in nums2
                if (i == 0)
                    maxLeft = nums2[j - 1];
                // if at bottom of nums2, max of left is in nums1
                else if (j == 0)
                    maxLeft = nums1[i - 1];
                // otherwise, max of left is in either set
                else
                    maxLeft = max(nums1[i - 1], nums2[j - 1]);
                
                if (!even)
                    return maxLeft;

                int minRight;
                // if at top of nums1, min of right is in nums2
                if (i == m)
                    minRight = nums2[j];
                // if at top of nums2, min of right is in nums1
                else if (j == n)
                    minRight = nums1[i];
                // otherwise, min of right is in either set
                else
                    minRight = min(nums1[i], nums2[j]);
                return (maxLeft + minRight) / 2.0;
            }
        }

        return 0;
    }
};