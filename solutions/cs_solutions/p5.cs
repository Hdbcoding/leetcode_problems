public class p5
{
    // Largest Palindromic Substring - medium

    // Given a string s, find the longest palindromic substring in s. You may assume that the maximum length of s is 1000.
    public class Solution
    {
        public string LongestPalindrome(string s)
        {
            return ExpandFromCenter(s);
        }

        private string ExpandFromCenter(string s)
        {
            if (string.IsNullOrEmpty(s)) return "";

            int start = 0, end = 0;
            for (int i = 0; i < s.Length; i++)
            {
                int lenOdd = WidthAtCenter(s, i, i);
                int lenEven = WidthAtCenter(s, i, i + 1);
                int width = Math.Max(lenOdd, lenEven);
                if (width > end - start)
                {
                    start = i - (width - 1) / 2;
                    end = i + width / 2;
                }
            }
            return s.Substring(start, end - start + 1);
        }

        private int WidthAtCenter(string s, int left, int right)
        {
            //Console.Write($"expanding from center: {left},{right}");
            int L = left, R = right;
            while (L >= 0 && R < s.Length && s[L] == s[R])
            {
                //Console.Write($"... {s[L]},{s[R]}");
                L--; R++;
            }
            //Console.WriteLine($"\n--- Max width was: {R - L - 1}");
            return R - L - 1;
        }

        private string BruteForceWithMemory(string s)
        {
            if (s.Length == 0) return "";
            int bigJ = 0, bigI = 0;
            var dromes = new Dictionary<int, HashSet<int>>();

            for (int l = 1; l < s.Length; l++)
            { //scan over each length
                for (int i = 0; i < s.Length - l; i++)
                { //scan from 0 to end with length
                    var j = i + l;
                    if (IsPalindromeMemory(s, i, j, dromes)
                        && (j - i) > (bigJ - bigI))
                    {
                        bigJ = j;
                        bigI = i;
                    }
                    //Console.WriteLine(string.Join("; ", dromes.Select(n => $"{n.Key}: {string.Join(",", n.Value)}")));
                }
            }
            return s.Substring(bigI, bigJ - bigI + 1);
        }

        private bool IsPalindromeMemory(string s, int first, int last, Dictionary<int, HashSet<int>> dromes)
        {
            var half = (last + 1 - first) / 2;
            //Console.Write($"---check palindrome - {first},{last}-{s.Substring(first, last-first+1)}");

            for (int i = 0; i < half; i++)
            {
                var left = first + i;
                var right = last - i;
                //Console.WriteLine($"------could be palindrome? {left},{s[left]} ?== {right},{s[right]}");

                if (dromes.ContainsKey(left) && dromes[left].Contains(right))
                {
                    //Console.Write($"--inner {s.Substring(left, right-left+1)} was cached");
                    break;
                }
                if (s[left] != s[right])
                {
                    //Console.WriteLine("-- not a palindrome");
                    return false;
                }
            }
            //Console.WriteLine("--found a drome - should update cache");

            if (dromes.ContainsKey(first))
            {
                //Console.WriteLine("existing drome");
                dromes[first].Add(last);
            }
            else
            {
                //Console.WriteLine("new drome");
                dromes.Add(first, new HashSet<int> { last });
            }
            return true;
        }

        private string ScanFromEdges(string s)
        {
            string biggest = s.Length > 0 ? s.Substring(0, 1) : "";
            var letterPositions = GetLetterPositions(s);

            foreach (var letter in letterPositions)
            {
                //Console.WriteLine($"Checking {letter.Key} - ({string.Join(",", letter.Value)})");
                var count = letter.Value.Count;
                if (count == 1) continue;

                for (int i = 0; i < count; i++)
                {
                    for (int j = count - 1; j > i; j--)
                    {
                        //Console.WriteLine($"--- i: {i}, j: {j}");
                        var first = letter.Value[i];
                        var last = letter.Value[j] + 1;
                        var length = last - first;
                        if (length < biggest.Length)
                        {
                            //Console.WriteLine($"--- {first}-{last}: too short, ignore!");
                            break;
                        }

                        var candidate = s.Substring(first, length);
                        //Console.WriteLine($"--- {first}-{last}: {candidate}");
                        if (IsPalindrome(candidate)) biggest = candidate;
                    }
                }
            }

            return biggest;
        }

        //preprocess - order(n)
        private Dictionary<char, List<int>> GetLetterPositions(string s)
        {
            var searchHelper = new Dictionary<char, List<int>>();

            for (int i = 0; i < s.Length; i++)
            {
                var letter = s[i];
                if (searchHelper.ContainsKey(letter))
                {
                    searchHelper[letter].Add(i);
                }
                else
                {
                    searchHelper.Add(letter, new List<int> { i });
                }
            }

            return searchHelper;
        }

        //palindrome - order(n)
        private bool IsPalindrome(string s)
        {
            for (int i = 0; i < s.Length / 2; i++)
            {
                if (s[i] != s[s.Length - i - 1]) return false;
            }
            return true;
        }
    }
}