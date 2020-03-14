public class p273
{
    // Convert a non-negative integer to its english words representation. 
    // Given input is guaranteed to be less than 231

    public class Solution
    {
        //max value = 2^31 - 1 = 2,147,483,647
        //                       1,000,000,000

        private Dictionary<int, string> NumMap = new Dictionary<int, string>{
        {0, ""},
        {1, "One"},
        {2, "Two"},
        {3, "Three"},
        {4, "Four"},
        {5, "Five"},
        {6, "Six"},
        {7, "Seven"},
        {8, "Eight"},
        {9, "Nine"},
        {10, "Ten"},
        {11, "Eleven"},
        {12, "Twelve"},
        {13, "Thirteen"},
        {14, "Fourteen"},
        {15, "Fifteen"},
        {16, "Sixteen"},
        {17, "Seventeen"},
        {18, "Eighteen"},
        {19, "Nineteen"}
    };

        private Dictionary<int, string> TensMap = new Dictionary<int, string>{
        {20, "Twenty"},
        {30, "Thirty"},
        {40, "Forty"},
        {50, "Fifty"},
        {60, "Sixty"},
        {70, "Seventy"},
        {80, "Eighty"},
        {90, "Ninety"},
    };

        private Dictionary<int, string> BigMap = new Dictionary<int, string>{
        {100, "Hundred"},
        {1000, "Thousand"},
        {1000000, "Million"},
        {1000000000, "Billion"}
    };

        private int[] BigInts = new[] { 1000000000, 1000000, 1000, 100 };

        public string NumberToWords(int num)
        {
            //Console.WriteLine(num);
            return LeftToRight(num);
        }

        public string LeftToRight(int num)
        {
            if (num == 0) return "Zero";
            if (NumMap.ContainsKey(num)) return NumMap[num];

            foreach (var bigInt in BigInts)
            {
                if (num >= bigInt)
                {
                    //Console.WriteLine($"---num is bigger than: {bigInt}");
                    var left = num / bigInt;
                    var right = num - left * bigInt;
                    var bigString = NumberToWords(left) + " " + BigMap[bigInt];
                    if (right != 0) bigString += " " + NumberToWords(right);
                    return bigString;
                }
            }

            var ones = num % 10;
            var tens = num - ones;
            //Console.WriteLine($"---tens: {tens}, ones: {ones}");
            var smallString = TensMap[num - ones];
            if (ones != 0) smallString += " " + NumMap[ones];
            return smallString;
        }
    }
}