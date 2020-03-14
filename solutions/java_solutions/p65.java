public class p65 {
    // "0" => true
    // " 0.1 " => true
    // "abc" => false
    // "1 a" => false
    // "2e10" => true
    // " -90e3   " => true
    // " 1e" => false
    // "e3" => false
    // " 6e-1" => true
    // " 99e2.5 " => false
    // "53.5e93" => true
    // " --6 " => false
    // "-+3" => false
    // "95a54e53" => false

    class Solution {
        public boolean isNumber(String s) {
            String trim = s.trim();
            boolean hasSign = false;
            boolean hasWholeDigits = false;
            
            boolean hasDecimalPoint = false;
            boolean hasDecimalDigits = false;
            
            boolean hasExponent = false;
            boolean exponentHasDigits = false;
            boolean exponentHasSign = false;
            
            for (int i = 0; i < trim.length(); i++){
                char current = trim.charAt(i);
                
                if (current == '+' || current == '-') {
                    boolean legalExponentSign = hasExponent && !exponentHasDigits && !exponentHasSign;
                    boolean legalSign = !hasSign && !hasWholeDigits && !hasDecimalPoint && !hasDecimalDigits;
                    if (!legalSign && !legalExponentSign)
                        return false;
                    hasSign = true;
                } else if (current == '.') {
                    if (hasDecimalPoint || hasExponent) return false;
                    hasDecimalPoint = true;
                } else if (current == 'e') {
                    if ((!hasWholeDigits && !hasDecimalDigits) || hasExponent) return false;
                    hasExponent = true;
                } else if (Character.isDigit(current)) {
                    if (!hasDecimalPoint && !hasExponent) hasWholeDigits = true;
                    if (hasDecimalPoint && !hasExponent) hasDecimalDigits = true;
                    if (hasExponent) exponentHasDigits = true;
                } else {
                    return false;
                }
            }
            
            if (!hasWholeDigits && !hasDecimalDigits) return false;
            if (hasExponent && !exponentHasDigits) return false;
            
            return true;
        }
    }
}