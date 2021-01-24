#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
// Burst Balloons - Hard

// You are given n balloons, indexed from 0 to n - 1. Each balloon is painted with a number on it represented by an array nums.
// You are asked to burst all the balloons.

// If you burst the ith balloon, you will get nums[i - 1] * nums[i] * nums[i + 1] coins. If i - 1 or i + 1 goes out of
// bounds of the array, then treat it as if there is a balloon with a 1 painted on it.

// Return the maximum coins you can collect by bursting the balloons wisely.

struct balloon
{
    int score{1};
    int isPopped{false};

    int left{-1};
    int right{-1};
};

int getPop(balloon b, vector<balloon> &balloons)
{
    int l = b.left == -1 ? 1 : balloons[b.left].score;
    int r = b.right == -1 ? 1 : balloons[b.right].score;
    return l * b.score * r;
}

void pop(int i, vector<balloon> &balloons)
{
    balloon b = balloons[i];
    if (b.left != -1)
    {
        balloons[b.left].right = b.right;
    }
    if (b.right != -1)
    {
        balloons[b.right].left = b.left;
    }
    balloons[i].isPopped = true;
}

void unpop(int i, vector<balloon> &balloons)
{
    balloon b = balloons[i];
    if (b.left != -1)
    {
        balloons[b.left].right = i;
    }
    if (b.right != -1)
    {
        balloons[b.right].left = i;
    }
    balloons[i].isPopped = false;
}

class Solution
{
    // exponential time! horrific complexity of O(n!)
    int naiveInner(vector<balloon> &balloons)
    {
        int sum = 0;
        for (int i = 0; i < balloons.size(); ++i)
        {
            if (balloons[i].isPopped)
                continue;

            int value = getPop(balloons[i], balloons);

            pop(i, balloons);
            int sumOfRest = naiveInner(balloons);
            unpop(i, balloons);

            sum = max(sum, value + sumOfRest);
        }
        return sum;
    }

    // naive solution - try every combination of popping baloons recursively
    int naive(vector<int> &nums)
    {
        vector<balloon> balloons(nums.size(), {1});
        for (int i = 0; i < nums.size(); ++i)
        {
            balloons[i].score = nums[i];

            if (i > 0)
                balloons[i].left = i - 1;
            if (i < nums.size() - 1)
                balloons[i].right = i + 1;
        }
        return naiveInner(balloons);
    }

    // we should be able to divide and conquer.
    // when we pop balloon i, we next need the solution for balloons[0,i] and ballons[i + 1:end]
    // pop balloons in "reverse order" to avoid the adjacency tracking in the naive solution
    // since we pop in reverse order, we always know exactly what the left and right balloons are, because we just used them
    // score for popping ith balloon: nums[left] * nums[i] * nums[right] + dp(left, i) + dp(i, right);
    //  where, this score is the score if we popped the ith balloon *last*
    //  then, the best score is the score if we popped the left section optimally, then the right section optimally, then popped i
    //  (which section is popped first is arbritrary, because the overall result is the same)
    // O(n^3)
    // dp[i][j] means the most coins you would get if you popped every balloon between i and j in the best order
    int bottomUpDp(vector<int> &nums)
    {
        // to avoid edge checking, make a bigger vector with 1 at the edges
        int n = nums.size() + 2;
        vector<int> nums2(n, 1);
        for (int i = 0; i < nums.size(); ++i)
            nums2[i + 1] = nums[i];

        vector<vector<int>> dp(n, vector<int>(n, 0));

        for (int left = n - 3; left > -1; --left)
        {
            // cout << "considering left index: " << left << ":" << nums2[left] << endl;
            for (int right = left + 2; right < n; ++right)
            {
                // cout << "\tconsidering right index " << right << ":" << nums2[right]  << endl;
                for (int i = left + 1; i < right; ++i)
                {
                    // cout << "\t\tconsidering balloon " << i << ":" << nums2[i] << endl;

                    // int pop = nums2[left] * nums2[i] * nums2[right];
                    // int oldLeft = dp[left][i];
                    // int oldRight = dp[i][right];
                    // int oldLeftRight = dp[left][right];

                    // cout << "\t\t\tpop:" << pop << ", oldLeft:" << oldLeft << ", oldRight:" << oldRight << ", oldLeftRight:" << oldLeftRight << endl;

                    // dp[left][right] = max(oldLeftRight, pop + oldLeft + oldRight);

                    // cout << "\t\t\tnewLeftRight:" << dp[left][right] << endl;

                    dp[left][right] = max(dp[left][right], nums2[left] * nums2[i] * nums2[right] + dp[left][i] + dp[i][right]);
                }
            }
        }

        return dp[0][n - 1];
    }

    int slightlyFasterDP(vector<int> &nums)
    {
        int n = nums.size();
        // mangle the original array to save memory over copying... time not really saved here
        nums.insert(nums.begin(), 1);
        nums.insert(nums.end(), 1);

        // same dp definition as before
        vector<vector<int>> dp(nums.size(), vector<int>(nums.size(), 0));
        for (int length = 1; length <= n; ++length)
        {
            for (int start = 1; start <= n - length + 1; ++start)
            {
                int end = start + length - 1;
                int best = 0;
                for (int i = start; i <= end; ++i)
                {
                    int v = nums[start - 1] * nums[i] * nums[end + 1] + dp[start][i - 1] + dp[i + 1][end];
                    if (v > best)
                        best = v;
                }
                dp[start][end] = best;
            }
        }
        return dp[1][n];
    }

    // as a heuristic, we sould always cut valleys first
    // scan left to right, looking for local minima
    int heuristicCut(vector<int> &nums)
    {
        int result = 0;
        int n = nums.size();
        int vmax = *max_element(nums.begin(), nums.end());

        int mid = 1;
        int right = mid + 1;
        while (right < n)
        {
            // vleft is always the next value before mid
            int vleft = nums[mid - 1];
            int vmid = nums[mid];
            int vright = nums[right];
            cout << "considering left"
                 << ":" << mid - 1
                 << ":" << vleft
                 << ", mid"
                 << ":" << mid
                 << ":" << vmid
                 << ", right"
                 << ":" << right
                 << ":"  << vright
                 << endl;

            if (vmid <= vleft && vmid <= vright
                // vmid smaller than vleft and vright makes sense.
                // but not sure about what the next calculation means
                && vleft * vright * (vmid + vmax) >= vmid * vmax * (vleft + vright))
            {
                cout << "\tdeleting local minima " << vmid << endl;
                // pop the local minimum
                result += vleft * vmid * vright;
                // if the mid is 1, copy vright over it
                // advance right, but leave mid where it is
                if (mid == 1)
                {
                    cout << "\tcopying right:" << right << " to mid " << mid << endl;
                    nums[mid] = nums[right++];
                }
                // otherwise decrement mid
                else
                {

                    --mid;
                }
            }
            else
            {
                cout << "\tcopying right:" << right << " to mid+1:" << mid + 1 << endl;
                // if mid is not a local minima, copy the right value over the successor to mid
                nums[++mid] = nums[right++];
            }
        }
        nums.resize(mid + 1);
        return result;
    }

    // with local minima deleted, do essentially the same dp algorithm, but on a smaller result set
    // still O(n^3), and no change in runtime for sets without local minima (e.g., strictly increasing or decreasing or flat)
    int dpWithHeuristicInner(vector<int> &nums)
    {
        int n = nums.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        for (int length = 2; length < n; ++length)
        {
            for (int start = 0; start < n - length; ++start)
            {
                int end = start + length;
                for (int i = start + 1; i < end; ++i)
                {
                    int v = nums[start] * nums[i] * nums[end] + dp[start][i] + dp[i][end];
                    dp[start][end] = max(dp[start][end], v);
                }
            }
        }
        return dp[0][n - 1];
    }

    int dpWithHeuristic(vector<int> &nums)
    {
        nums.insert(nums.begin(), 1);
        nums.insert(nums.end(), 1);
        int base = heuristicCut(nums);
        int result = base + dpWithHeuristicInner(nums);
        return result;
    }

public:
    int maxCoins(vector<int> &nums)
    {
        return dpWithHeuristic(nums);
    }
};

int main()
{
    Solution s;

    // vector<int> t1{3, 1, 5, 8};
    // cout << s.maxCoins(t1) << endl;

    // vector<int> t2{1, 5};
    // cout << s.maxCoins(t2) << endl;

    vector<int> t3{7, 9, 8, 0, 7, 1, 3, 5, 5, 2, 3};
    cout << s.maxCoins(t3) << endl;
}