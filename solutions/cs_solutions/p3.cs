public class p3
{
    // Longest Substring Without Repeating Characters - Medium

    // Given a string, find the length of the longest substring without repeating characters.
    public class Solution
    {
        public int LengthOfLongestSubstring(string s)
        {
            if (string.IsNullOrEmpty(s)) return 0;
            if (s.Trim().Length == 0) return 1;

            var map = new Dictionary<char, int>();
            int maxLen = 0;
            int f = 0;
            for (int l = 0; l < s.Length; l++)
            {
                var c = s[l];
                if (map.ContainsKey(c))
                {
                    f = Math.Max(map[c], f);
                }
                if (maxLen < l - f + 1) maxLen = l - f + 1;
                map[c] = l + 1;
            }
            return maxLen;
        }
    }
}