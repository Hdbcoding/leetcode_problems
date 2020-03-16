public class p482 {
    // License Key Formatting - Easy

    // You are given a license key represented as a string S which consists only
    // alphanumeric character and dashes. The string is separated into N+1 groups by
    // N dashes.
    // Given a number K, we would want to reformat the strings such that each group
    // contains exactly K characters, except for the first group which could be
    // shorter than K, but still must contain at least one character. Furthermore,
    // there must be a dash inserted between two groups and all lowercase letters
    // should be converted to uppercase.
    // Given a non-empty string S and a number K, format the string according to the
    // rules described above.

    // The length of string S will not exceed 12,000, and K is a positive integer.
    // String S consists only of alphanumerical characters (a-z and/or A-Z and/or
    // 0-9) and dashes(-).
    // String S is non-empty.

    class Solution {
        public String licenseKeyFormatting(String S, int K) {
            StringBuilder sb = new StringBuilder();
            int m = K;
            for (int i = S.length() - 1; i >= 0; i--){
                char c = S.charAt(i);
                if (c == '-') continue; // ignore dashes already in the string
                if (m == 0){ 
                    sb.append("-"); 
                    m = K;
                }
                sb.append(Character.toUpperCase(c));
                m--;
            }
            return sb.reverse().toString();
        }
    }
}