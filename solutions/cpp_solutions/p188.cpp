#include <vector>

using namespace std;

// Best Time to Buy and Sell Stock IV - Hard

// You are given an integer array prices where prices[i] is the price of a given stock on the ith day.

// Design an algorithm to find the maximum profit. You may complete at most k transactions.

// Notice that you may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).

class Solution
{
public:
    int maxProfit(int k, vector<int> &prices)
    {
        if (prices.size() == 0)
            return 0;
        if (k == 0)
            return 0;
        return bottomup(k, prices);
    }

    int bottomup(int k, vector<int> &prices)
    {
        vector<vector<int>> buydp(prices.size(), vector<int>(k + 1, -1e9));
        vector<vector<int>> selldp(prices.size(), vector<int>(k + 1, -1e9));
        buydp[0][0] = 0;
        selldp[0][1] = -prices[0];

        // dp concept
        // buydp[i][j] = max(
        //      buydp[i-1][j] // dont buy yet
        //      selldp[i-1][j] + prices[i] // sell

        // selldp[i][j] = max(
        //      selldp[i-1][j] // don't sell yet
        //      buydp[i-1][j-1] - prices[i] // buy

        for (int i = 1; i < prices.size(); ++i)
        {
            for (int j = 0; j <= k; ++j)
            {
                buydp[i][j] = max(
                    buydp[i - 1][j],
                    selldp[i - 1][j] + prices[i]);

                if (j > 0)
                {
                    selldp[i][j] = max(
                        selldp[i - 1][j],
                        buydp[i - 1][j - 1] - prices[i]);
                }
            }
        }

        int best = 0;
        for (int j = 0; j <= k; ++j)
        {
            best = max(best, buydp[prices.size() - 1][j]);
        }
        return best;
    }

    int memoization(int k, vector<int> &prices)
    {
        vector<vector<int>> buyMemo(prices.size(), vector<int>(k, -1));
        vector<vector<int>> sellMemo(prices.size(), vector<int>(k, -1));

        return memoizationInner(k, prices, 0, true, buyMemo, sellMemo);
    }

    int memoizationInner(int k, vector<int> &prices, int index, bool buy, vector<vector<int>> &buyMemo, vector<vector<int>> &sellMemo)
    {
        if (k == 0)
            return 0;
        if (prices.size() == index)
            return 0;

        if (buy)
        {
            if (buyMemo[index][k - 1] != -1)
                return buyMemo[index][k - 1];
            // if we are buying right now, consider the best option of buying or not buying today
            int buyThis = memoizationInner(k, prices, index + 1, false, buyMemo, sellMemo) - prices[index];
            int skipThis = memoizationInner(k, prices, index + 1, true, buyMemo, sellMemo);

            return buyMemo[index][k - 1] = max(buyThis, skipThis);
        }
        else
        {
            if (sellMemo[index][k - 1] != -1)
                return sellMemo[index][k - 1];
            int sellThis = memoizationInner(k - 1, prices, index + 1, true, buyMemo, sellMemo) + prices[index];
            int skipThis = memoizationInner(k, prices, index + 1, false, buyMemo, sellMemo);
            return sellMemo[index][k - 1] = max(sellThis, skipThis);
        }
    }

    int naive(int k, vector<int> &prices)
    {
        return naiveInner(k, prices, 0, true);
    }

    int naiveInner(int k, vector<int> &prices, size_t index, bool buy)
    {
        if (k == 0)
            return 0;
        if (prices.size() == index)
            return 0;

        if (buy)
        {
            // if we are buying right now, consider the best option of buying or not buying today
            int buyThis = naiveInner(k, prices, index + 1, false) - prices[index];
            int skipThis = naiveInner(k, prices, index + 1, true);

            return max(buyThis, skipThis);
        }
        else
        {
            int sellThis = naiveInner(k - 1, prices, index + 1, true) + prices[index];
            int skipThis = naiveInner(k, prices, index + 1, false);
            return max(sellThis, skipThis);
        }
    }
};