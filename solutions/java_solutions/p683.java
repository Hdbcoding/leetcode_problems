public class p683 {
    // You have N bulbs in a row numbered from 1 to N. Initially, all the bulbs are
    // turned off. We turn on exactly one bulb everyday until all bulbs are on after
    // N days.
    // You are given an array bulbs of length N where bulbs[i] = x means that on the
    // (i+1)th day, we will turn on the bulb at position x where i is 0-indexed and
    // x is 1-indexed.
    // Given an integer K, find out the minimum day number such that there exists
    // two turned on bulbs that have exactly K bulbs between them that are all
    // turned off.
    // If there isn't such day, return -1.

    class Solution {
        public int kEmptySlots(int[] flowers, int k) {
            return slidingWindow(flowers, k);
        }

        private int slidingWindow(int[] flowers, int k) {
            int[] days = new int[flowers.length];
            for (int i = 0; i < flowers.length; i++) {
                days[flowers[i] - 1] = i + 1;
            }

            // System.out.print("days: ");
            // for (int i = 0; i < days.length; i++) System.out.print(days[i] + ",");
            // System.out.println();

            int firstGapDay = Integer.MAX_VALUE;
            int left = 0, right = k + 1;
            slide: while (right < days.length) {
                int first = days[left];
                int last = days[right];
                for (int i = left + 1; i < right; ++i) {
                    if (days[i] < first || days[i] < last) {
                        left = i;
                        right = i + k + 1;
                        continue slide;
                    }
                }

                int max = Math.max(days[left], days[right]);
                firstGapDay = Math.min(firstGapDay, max);
                left = right;
                right = left + k + 1;
            }

            return firstGapDay < Integer.MAX_VALUE ? firstGapDay : -1;
        }
    }
}