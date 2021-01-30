#include <vector>
#include <queue>
using namespace std;

// Mean of Array after Removing Some Elements - Easy

// Given an integer array arr, return the mean of the remaining integers after removing the smallest 5% and the largest 5% of the elements.

// Answers within 10-5 of the actual answer will be considered accepted.

class Solution
{
public:
    double trimMean(vector<int> &arr)
    {
        int fivepercent = arr.size() / 20;

        // max queue of smallest elements (pop removes biggest elements)
        priority_queue<int> smaller;
        // min queue of biggest elements (pop removes smallest elements)
        priority_queue<int, vector<int>, greater<int>> greater;

        double total;
        for (int i : arr)
        {
            total += i;
            smaller.push(i);
            greater.push(i);

            if (smaller.size() > fivepercent)
                smaller.pop();
            if (greater.size() > fivepercent)
                greater.pop();
        }

        for (int i = 0; i < fivepercent; ++i)
        {
            total -= smaller.top();
            total -= greater.top();
            smaller.pop();
            greater.pop();
        }

        return total / (arr.size() - fivepercent * 2);
    }
};