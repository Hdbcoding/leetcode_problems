public class p7
{
    // Reverse Integer - Easy

    // Given a 32-bit signed integer, reverse digits of an integer.
    // Assume we are dealing with an environment which could only store 
    //  integers within the 32-bit signed integer range: [−231,  231 − 1]. 
    //  For the purpose of this problem, assume that your function returns 0 
    //  when the reversed integer overflows.
    public class Solution
    {
        public int Reverse(int x)
        {
            int reversed = 0;
            int high = int.MaxValue / 10;
            int highDigit = int.MaxValue % 10;
            int low = int.MinValue / 10;
            int lowDigit = int.MinValue % 10;

            //Console.WriteLine($"{high} - {highDigit} - {low} - {lowDigit}");

            while (x != 0)
            {
                var digit = x % 10;
                x = x / 10;

                if (reversed > high || (reversed == high && digit > highDigit)) return 0;
                if (reversed < low || (reversed == low && digit < lowDigit)) return 0;

                reversed = reversed * 10 + digit;
            }

            return reversed;
        }
    }
}