import java.util.HashSet;

public class p686 {
    // Given two strings A and B, find the minimum number of times A has to be
    // repeated such that B is a substring of it. If no such solution, return -1.
    // For example, with A = "abcd" and B = "cdabcdab".
    // Return 3, because by repeating A three times (“abcdabcdabcd”), B is a
    // substring of it; and B is not a substring of A repeated two times
    // ("abcdabcd").
    // Note:
    // The length of A and B will be between 1 and 10000.

    class Solution {
        public int repeatedStringMatch(String A, String B) {
            HashSet<Character> letters = new HashSet<Character>();
            for (char ch : A.toCharArray()){
                if (!letters.contains(ch)) letters.add(ch);
            }
            
            char bFirst = B.charAt(0);
            if (!letters.contains(bFirst)){
                return -1;
            }
            //try to iterate through A and B, cycling through A when we get to the end of it
            int aOffset = 0;
            while (aOffset != -1){
                int loops = 0;
                int aFirstIndex = A.indexOf(bFirst, aOffset);
    
                if (aFirstIndex == -1){
                    //we've tried enough different offsets of A that now there's nothing left to try
                    return -1;
                }
                
                //we already compared 0 to 0, so let's start at 1 and 1
                int aIndex = aFirstIndex + 1;
                int bIndex = 1;
                while (bIndex < B.length()){
                    if (aIndex == A.length()){
                        aIndex = 0;
                        //whenever we loop around the end of A, increment loops
                        loops++;
                    }
                    if (!letters.contains(B.charAt(bIndex))) {
                        //if we've found a character in B not available in A, obviously quit
                        return -1;
                    }
                    if (B.charAt(bIndex) != A.charAt(aIndex)){
                        //if we ever find an out of sequence character, try a different offset for A
                        break;
                    }
                    aIndex++;
                    bIndex++;
                }
                
                //if we successfully iterated all the way through B, then we're done
                if (bIndex == B.length()) {
                    return loops + 1;
                //otherwise, try a different offset
                } else {
                    aOffset = aFirstIndex + 1;
                }
            }
            
            return -1;
        }
    }
}