
// Find in Mountain Array - Hard

// You may recall that an array A is a mountain array if and only if:

// A.length >= 3
// There exists some i with 0 < i < A.length - 1 such that:
// A[0] < A[1] < ... A[i-1] < A[i]
// A[i] > A[i+1] > ... > A[A.length - 1]
// Given a mountain array mountainArr, return the minimum index such that mountainArr.get(index) == target.  If such an index doesn't exist, return -1.

// You can't access the mountain array directly.  You may only access the array using a MountainArray interface:

// MountainArray.get(k) returns the element of the array at index k (0-indexed).
// MountainArray.length() returns the length of the array.
// Submissions making more than 100 calls to MountainArray.get will be judged Wrong Answer.  Also, any solutions that attempt to circumvent the judge will result in disqualification.


// This is the MountainArray's API interface.
// You should not implement it, or speculate about its implementation
class MountainArray
{
public:
    int get(int index);
    int length();
};

class Solution
{
    struct Peak
    {
        int index{-1};
        int targetIndex{-1};
    };
    int callsLeft{100};

public:
    int findInMountainArray(int target, MountainArray &mountainArr)
    {
        // binary search for the peak
        Peak peak = findPeak(mountainArr, target);
        // if we already found the target, and it's in the left half or center
        // then we can return it right away
        if (peak.targetIndex >= 0 && peak.targetIndex <= peak.index)
            return peak.targetIndex;

        // binary search left half for the target
        int targetIndex = search(mountainArr, target, 0, peak.index - 1, true);
        if (targetIndex >= 0)
            return targetIndex;

        // if we already found the target when searching for the peak, return that now
        // otherwise, search right half
        if (peak.targetIndex >= 0)
            return peak.targetIndex;
        return search(mountainArr, target, peak.index + 1, mountainArr.length() - 1, false);
    }

    Peak findPeak(MountainArray &mountainArr, int target)
    {
        Peak peak;
        int l = 1;
        int r = mountainArr.length() - 2;
        while (l < r)
        {
            int m = (l + r) / 2;
            int leftVal = get(mountainArr, m - 1);
            if (leftVal == target)
                peak.targetIndex = m - 1;
            int val = get(mountainArr, m);
            if (val == target)
                peak.targetIndex = m;
            int rightVal = get(mountainArr, m + 1);
            if (rightVal == target)
                peak.targetIndex = m + 1;

            bool isIncreasingLeft = leftVal < val;
            bool isIncreasingRight = val < rightVal;
            bool isPeak = isIncreasingLeft && !isIncreasingRight;
            if (isPeak)
            {
                peak.index = m;
                return peak;
            }

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

        peak.index = l;
        // possible that the peak is the target, check it now
        if (get(mountainArr, l) == target)
            peak.targetIndex = l;

        return peak;
    }

    int search(MountainArray &mountainArr, int target, int l, int r, bool increase)
    {
        while (l <= r)
        {
            int m = (l + r) / 2;
            int val = get(mountainArr, m);

            if (val == target)
                return m;

            bool tooBig = val > target;
            if (tooBig != increase)
            {
                l = m + 1;
            }
            else
            {
                r = m - 1;
            }
        }

        return -1;
    }

    int get(MountainArray &mountainArr, int i)
    {
        int v = mountainArr.get(i);
        --callsLeft;
        return v;
    }
};