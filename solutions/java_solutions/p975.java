import java.util.Arrays;
import java.util.Comparator;
import java.util.Stack;

public class p975 {
    // You are given an integer array A. From some starting index, you can make a
    // series of jumps. The (1st, 3rd, 5th, ...) jumps in the series are called odd
    // numbered jumps, and the (2nd, 4th, 6th, ...) jumps in the series are called
    // even numbered jumps.

    // You may from index i jump forward to index j (with i < j) in the following
    // way:

    // During odd numbered jumps (ie. jumps 1, 3, 5, ...), you jump to the index j
    // such that A[i] <= A[j] and A[j] is the smallest possible value. If there are
    // multiple such indexes j, you can only jump to the smallest such index j.
    // During even numbered jumps (ie. jumps 2, 4, 6, ...), you jump to the index j
    // such that A[i] >= A[j] and A[j] is the largest possible value. If there are
    // multiple such indexes j, you can only jump to the smallest such index j.
    // (It may be the case that for some index i, there are no legal jumps.)
    // A starting index is good if, starting from that index, you can reach the end
    // of the array (index A.length - 1) by jumping some number of times (possibly 0
    // or more than once.)

    // Return the number of good starting indexes.

    class Solution {
        public int oddEvenJumps(int[] A) {
            Integer[] B = getIndices(A);
            ArrayIndexComparator c = new ArrayIndexComparator(A);
            Arrays.sort(B, c);
            int[] nextOdd = generateNextArray(B);
            c.desc = true;
            Arrays.sort(B, c);
            int[] nextEven = generateNextArray(B);

            // solve with dp
            boolean[] odd = new boolean[A.length];
            boolean[] even = new boolean[B.length];
            odd[A.length - 1] = even[A.length - 1] = true;
            for (int i = A.length - 2; i >= 0; i--) {
                if (nextOdd[i] != -1)
                    odd[i] = even[nextOdd[i]];
                if (nextEven[i] != -1)
                    even[i] = odd[nextEven[i]];
            }

            int count = 0;
            for (boolean v : odd)
                if (v)
                    count++;

            return count;
        }

        Integer[] getIndices(int[] A) {
            Integer[] B = new Integer[A.length];

            for (int i = 0; i < B.length; i++)
                B[i] = i;

            return B;
        }

        int[] generateNextArray(Integer[] B) {
            int[] result = new int[B.length];
            Arrays.fill(result, -1);
            Stack<Integer> s = new Stack<>();
            for (int i : B) {
                while (!s.isEmpty() && i > s.peek()) {
                    result[s.pop()] = i;
                }
                s.push(i);
            }
            return result;
        }

        class ArrayIndexComparator implements Comparator<Integer> {
            int[] A;
            boolean desc;

            ArrayIndexComparator(int[] A) {
                this.A = A;
            }

            @Override
            public int compare(Integer i, Integer j) {
                return desc ? A[j] - A[i] : A[i] - A[j];
            }
        }
    }
}