public class p540 {
    // You are given a sorted array consisting of only integers where every element
    // appears exactly twice, except for one element which appears exactly once.
    // Find this single element that appears only once.

    class Solution {
        public int singleNonDuplicate(int[] nums) {
            int start = 0;
            int end = nums.length - 1;
            while (start < end) {
                int middle = (start + end) / 2;

                if (lookLeft(nums, middle))
                    end = middle - 1;
                else
                    start = middle + 1;
            }
            return nums[start];
        }

        private boolean lookLeft(int[] nums, int middle) {
            boolean even = middle % 2 == 0;
            int adjustment = even ? 1 : -1;
            int other = middle + adjustment;
            boolean singleIsRight = nums[middle] == nums[other];

            return !singleIsRight;
        }
    }
}