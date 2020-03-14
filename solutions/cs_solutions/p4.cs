public class p4
{
    // There are two sorted arrays nums1 and nums2 of size m and n respectively.
    // Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).
    // You may assume nums1 and nums2 cannot be both empty.
    public class Solution
    {
        public double FindMedianSortedArrays(int[] nums1, int[] nums2)
        {
            // ensure that nums1 is the bigger set
            if (nums2.Length < nums1.Length) return FindMedianSortedArrays(nums2, nums1);

            var imin = 0;
            var m = nums1.Length;
            var n = nums2.Length;
            var imax = m;
            var halfLen = (m + n + 1) / 2;
            var isEven = ((m + n) % 2) == 0;
            while (imin <= imax)
            {
                var i = (imin + imax) / 2;
                var j = halfLen - i;

                //cases:
                // nums2[j - 1] > nums1[i]; ==> nums1[i] is too small, increase i
                if (i < imax && nums2[j - 1] > nums1[i]) imin = i + 1;
                // nums1[i - 1] > nums2[j]; ==> nums1[i] is too large, decrease i
                else if (i > imin && nums1[i - 1] > nums2[j]) imax = i - 1;
                // nums2[j-1] <= nums1[i]; nums1[i-1] <= nums2[j]; ==> i marks the center
                else
                {
                    // Console.Write("Found a solution: ");
                    var maxLeft = 0;
                    if (i == 0) maxLeft = nums2[j - 1];
                    else if (j == 0) maxLeft = nums1[i - 1];
                    else maxLeft = Math.Max(nums1[i - 1], nums2[j - 1]);
                    if (!isEven) return maxLeft;

                    var minRight = 0;
                    if (i == m) minRight = nums2[j];
                    else if (j == n) minRight = nums1[i];
                    else minRight = Math.Min(nums1[i], nums2[j]);
                    return (maxLeft + minRight) / 2.0;
                }
            }

            return 0;
        }
    }
}