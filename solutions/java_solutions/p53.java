public class p53 {
    // Maximum Subarray - Easy

    // Given an integer array nums, find the contiguous subarray (containing at
    // least one number) which has the largest sum and return its sum.

    class Solution {
        public int maxSubArray(int[] nums) {
            int sum = Integer.MIN_VALUE;
            int currentSum = 0;
            for (int i = 0; i < nums.length; i++) {
                currentSum += nums[i];
                sum = Math.max(currentSum, sum);
                if (currentSum < 0)
                    currentSum = 0;
            }
            return sum;
        }
    }
}