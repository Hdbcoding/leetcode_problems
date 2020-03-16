public class p65 {
    // Valid Number - Hard

    // Validate if a given string can be interpreted as a decimal number.
    // "0" => true
    // " 0.1 " => true
    // "abc" => false
    // "1 a" => false
    // "2e10" => true
    // " -90e3 " => true
    // " 1e" => false
    // "e3" => false
    // " 6e-1" => true
    // " 99e2.5 " => false
    // "53.5e93" => true
    // " --6 " => false
    // "-+3" => false
    // "95a54e53" => false
    // Note: It is intended for the problem statement to be ambiguous. You should
    // gather all requirements up front before implementing one. However, here is a
    // list of characters that can be in a valid decimal number:
    // Numbers 0-9
    // Exponent - "e"
    // Positive/negative sign - "+"/"-"
    // Decimal point - "."
    // Of course, the context of these characters also matters in the input.

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

            for (int i = 0; i < trim.length(); i++) {
                char current = trim.charAt(i);

                if (current == '+' || current == '-') {
                    boolean legalExponentSign = hasExponent && !exponentHasDigits && !exponentHasSign;
                    boolean legalSign = !hasSign && !hasWholeDigits && !hasDecimalPoint && !hasDecimalDigits;
                    if (!legalSign && !legalExponentSign)
                        return false;
                    hasSign = true;
                } else if (current == '.') {
                    if (hasDecimalPoint || hasExponent)
                        return false;
                    hasDecimalPoint = true;
                } else if (current == 'e') {
                    if ((!hasWholeDigits && !hasDecimalDigits) || hasExponent)
                        return false;
                    hasExponent = true;
                } else if (Character.isDigit(current)) {
                    if (!hasDecimalPoint && !hasExponent)
                        hasWholeDigits = true;
                    if (hasDecimalPoint && !hasExponent)
                        hasDecimalDigits = true;
                    if (hasExponent)
                        exponentHasDigits = true;
                } else {
                    return false;
                }
            }

            if (!hasWholeDigits && !hasDecimalDigits)
                return false;
            if (hasExponent && !exponentHasDigits)
                return false;

            return true;
        }
    }
}