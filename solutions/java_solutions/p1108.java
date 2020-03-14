public class p1108 {
    // Defanging an IP Address - Easy

    // Given a valid (IPv4) IP address, return a defanged version of that IP
    // address.
    // A defanged IP address replaces every period "." with "[.]".

    class Solution {
        public String defangIPaddr(String address) {
            StringBuilder sb = new StringBuilder();
            for (int i = 0; i < address.length(); i++) {
                char c = address.charAt(i);
                if (c == '.')
                    sb.append("[.]");
                else
                    sb.append(c);
            }
            return sb.toString();
        }
    }
}