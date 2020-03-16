public class p20
{
     // Valid Parentheses - Easy

    // Given a string containing just the characters '(', ')', '{', '}', 
    //  '[' and ']', determine if the input string is valid.
    // An input string is valid if:
    //   Open brackets must be closed by the same type of brackets.
    //   Open brackets must be closed in the correct order.
    // Note that an empty string is also considered valid.
    public class Solution
    {
        public bool IsValid(string s)
        {
            if (s.Length == 0) return true;

            var closing = new Stack<char>();

            foreach (char c in s)
            {
                if (c == '[') closing.Push(']');
                else if (c == '(') closing.Push(')');
                else if (c == '{') closing.Push('}');
                else if (closing.Count == 0 || closing.Pop() != c)
                    return false;
            }
            return closing.Count == 0;
        }
    }
}