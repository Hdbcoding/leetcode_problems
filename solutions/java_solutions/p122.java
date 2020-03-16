public class p122 {
    // Best Time to Buy and Sell Stock II - Easy

    // Say you have an array for which the ith element is the price of a given stock
    // on day i.

    // Design an algorithm to find the maximum profit. You may complete as many
    // transactions as you like (i.e., buy one and sell one share of the stock
    // multiple times).

    // Note: You may not engage in multiple transactions at the same time (i.e., you
    // must sell the stock before you buy again).

    class Solution {
        public int maxProfit(int[] prices) {
            int sum = 0;

            int last = Integer.MAX_VALUE;
            int min = Integer.MAX_VALUE;
            int currentProfit = 0;

            for (int i = 0; i < prices.length; i++) {
                int current = prices[i];

                if (current < last) {
                    sum += currentProfit;
                    min = current;
                    currentProfit = 0;
                } else {
                    currentProfit = current - min;
                }

                last = current;
            }

            sum += currentProfit;

            return sum;
        }
    }
}