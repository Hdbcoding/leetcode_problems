public class p11
{
    // Given n non-negative integers a1, a2, ..., an , where each represents a 
    //  point at coordinate (i, ai). n vertical lines are drawn such that the 
    //  two endpoints of line i is at (i, ai) and (i, 0). Find two lines, which 
    //  together with x-axis forms a container, such that the container contains 
    //  the most water.
    // Note: You may not slant the container and n is at least 2.
    public class Solution
    {
        public int MaxArea(int[] height)
        {
            return TwoPointer(height);
        }

        public int TwoPointer(int[] height)
        {
            int l = 0, r = height.Length - 1;
            int max = 0;

            while (l < r)
            {
                max = Math.Max(max, (r - l) * Math.Min(height[l], height[r]));
                if (height[l] > height[r]) r--;
                else l++;
            }

            return max;
        }

        public int SomethingElse(int[] height)
        {
            //weird heuristic, ignore that
            //NlogN version - for each left, binary search the biggest right?
            var sorted = height.Select((h, i) => new { h, i })
                .OrderByDescending(n => n.h * Math.Abs(height.Length - n.i))
                .ToList();
            int maxPossible = sorted[0].h * height.Length;
            int max = 0;
            bool couldDoBetter = true;
            for (int i = 0; i < height.Length - 1; i++)
            {
                var left = sorted[i];
                for (int j = i + 1; j < height.Length; j++)
                {
                    var right = sorted[j];
                    var current = Math.Abs(left.i - right.i) * Math.Min(left.h, right.h);
                    max = Math.Max(max, current);
                }
            }
            return max;
        }

        public int BruteForce(int[] height)
        {
            int max = 0;

            //O(N^2)
            for (int i = 0; i < height.Length - 1; i++)
            {
                for (int j = i + 1; j < height.Length; j++)
                {
                    max = Math.Max(max, (j - i) * Math.Min(height[i], height[j]));
                }
            }
            return max;
        }
    }
}