public class p42 {
    // Trapping rain water - Easy

    // Given n non-negative integers representing an elevation map where the width
    // of each bar is 1, compute how much water it is able to trap after raining.

    class Solution {
        public int trap(int[] height) {
            if (height.length <= 2)
                return 0;
            return twoPointer(height);
        }

        int twoPointer(int[] height) {
            int l = 0;
            int r = height.length - 1;
            int hl = height[l];
            int hr = height[r];
            int walls = 0;
            int water = 0;

            while (l < r) {
                walls = Math.max(Math.min(hl, hr), walls);

                if (hl <= hr) {
                    l++;
                    hl = height[l];
                    if (hl < walls)
                        water += walls - hl;
                } else {
                    r--;
                    hr = height[r];
                    if (hr < walls)
                        water += walls - hr;
                }
            }
            return water;
        }
    }
}