public class p123 {
    // Best Time to Buy and Sell Stock III - Hard

    // Say you have an array for which the ith element is the price of a given stock
    // on day i.

    // Design an algorithm to find the maximum profit. You may complete at most two
    // transactions.

    // Note: You may not engage in multiple transactions at the same time (i.e., you
    // must sell the stock before you buy again).

    public static void main(String[] args) {
        System.out.println(new Solution().maxProfit(new int[] { 3, 3, 5, 0, 0, 3, 1, 4 }));
        System.out.println(new Solution().maxProfit(new int[] { 1, 2, 4, 2, 5, 7, 2, 4, 9, 0 }));
    }

    static class Solution {
        public int maxProfit(int[] prices) {
            return holdRelease(prices);
        }

        // this is slower than the naive solution, but a lot of rework can be simplified
        public int straightforwardDP(int[] prices) {
            if (prices.length <= 1)
                return 0;
            
            // dp[k, i] = max(dp[k, i-1], prices[i] - prices[j] + dp[k-1, j-1]), j=[0..i-1]
            // k transactions, ith day
            // best result for k transactions on day i
            //   if the max of:
            //     dp[k, i-1]
            //     dp[k - 1, j - 1] + prices[i] - prices[j] for all j < i

            var dp = new int[3][prices.length];
            for (int k = 1; k <= 2; k++) {
                for (int i = 1; i < prices.length; i++) {
                    int p = prices[0];
                    for (int j = 1; j <= i; j++)
                        p = Math.min(p, prices[j] - dp[k - 1][j - 1]);
                    dp[k][i] = Math.max(dp[k][i - 1], prices[i] - p);
                }
            }
            
            return dp[2][prices.length - 1];
        }

        public int holdRelease(int[] prices) {
            // max after buying the first stock
            int hold1 = Integer.MIN_VALUE;
            // max after buying the second stock
            int hold2 = Integer.MIN_VALUE;
            // max after selling the first stock
            int release1 = 0;
            // max after selling the second stock
            int release2 = 0;

            for (int p : prices) {
                release2 = Math.max(release2, hold2 + p);
                hold2 = Math.max(hold2, release1 - p);
                release1 = Math.max(release1, hold1 + p);
                hold1 = Math.max(hold1, -p);
            }
            return release2;
        }

        public int naive(int[] prices) {
            int sum = 0;

            for (int i = 0; i < prices.length; i++) {
                sum = Math.max(sum, maxProfit(prices, 0, i + 1) + maxProfit(prices, i, prices.length));
            }

            return sum;
        }

        public int maxProfit(int[] prices, int s, int t) {
            if (t - s <= 1)
                return 0;

            int min = Integer.MAX_VALUE;
            int profit = 0;

            for (int i = s; i < t; i++) {
                if (prices[i] < min)
                    min = prices[i];
                else if (prices[i] - min > profit)
                    profit = prices[i] - min;
            }

            return profit;
        }

        int biggestProfit = 0;
        int secondBiggestProfit = 0;

        // this doesn't work!
        public int greedy(int[] prices) {
            int last = Integer.MAX_VALUE;
            int min = Integer.MAX_VALUE;
            int currentProfit = 0;

            for (int i = 0; i < prices.length; i++) {
                int current = prices[i];

                if (current < last) {
                    establish(currentProfit);
                    min = current;
                    currentProfit = 0;
                } else {
                    currentProfit = current - min;
                }

                last = current;
            }
            establish(currentProfit);

            return biggestProfit + secondBiggestProfit;
        }

        void establish(int profit) {
            if (profit > biggestProfit) {
                secondBiggestProfit = biggestProfit;
                biggestProfit = profit;
            } else if (profit > secondBiggestProfit) {
                secondBiggestProfit = profit;
            }
        }
    }
}