#include <vector>
#include <iostream>
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
    // exponential time! horrific
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

    // naive solution - try every combination of popping baloons
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

public:
    int maxCoins(vector<int> &nums)
    {
        return naive(nums);
    }
};

int main()
{
    Solution s;

    vector<int> t1{3, 1, 5, 8};
    cout << s.maxCoins(t1) << endl;

    vector<int> t2{1, 5};
    cout << s.maxCoins(t2) << endl;

    vector<int> t3{7, 9, 8, 0, 7, 1, 3, 5, 5, 2, 3};
    cout << s.maxCoins(t3) << endl;
}