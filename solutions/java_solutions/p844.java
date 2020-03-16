import java.util.Stack;

public class p844 {
    // Backspace String Compare - Easy

    // Given two strings S and T, return if they are equal when both are typed into
    // empty text editors. # means a backspace character.
    // Bonus points if O(1) space

    class Solution {
        public boolean backspaceCompare(String S, String T) {
            return iterative(S, T);
        }

        boolean iterative(String s, String t) {
            // current positions
            int i = s.length() - 1;
            int j = t.length() - 1;
            // strings to delete
            int bs = 0;
            int bt = 0;

            while (i >= 0 || j >= 0) {
                // find next i which is actually a character
                while (i >= 0) {
                    if (s.charAt(i) == '#') {
                        bs++;
                        i--;
                    } else if (bs > 0) {
                        bs--;
                        i--;
                    } else
                        break;
                }
                // find next j which is actually a character
                while (j >= 0) {
                    if (t.charAt(j) == '#') {
                        bt++;
                        j--;
                    } else if (bt > 0) {
                        bt--;
                        j--;
                    } else
                        break;
                }

                boolean sHasChar = i >= 0;
                boolean tHasChar = j >= 0;

                if (sHasChar && tHasChar && s.charAt(i) != t.charAt(j))
                    return false;

                if (sHasChar != tHasChar)
                    return false;

                i--;
                j--;
            }

            return true;
        }

        boolean simple(String S, String T) {
            Stack<Character> s = buildStack(S);
            Stack<Character> t = buildStack(T);
            return stacksEqual(s, t);
        }

        Stack<Character> buildStack(String word) {
            Stack<Character> s = new Stack<>();
            for (char c : word.toCharArray())
                if (c == '#') {
                    if (!s.isEmpty())
                        s.pop();
                } else
                    s.push(c);
            return s;
        }

        boolean stacksEqual(Stack<Character> s, Stack<Character> t) {
            if (s.size() != t.size())
                return false;

            while (!s.isEmpty())
                if (s.pop() != t.pop())
                    return false;

            return true;
        }
    }
}