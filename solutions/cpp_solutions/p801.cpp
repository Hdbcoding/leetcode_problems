#include <vector>

using namespace std;

// Minimum swaps to make sequences increasing - Medium

// We have two integer sequences A and B of the same non-zero length.

// We are allowed to swap elements A[i] and B[i].
// Note that both elements are in the same index position in their respective sequences.

// At the end of some number of swaps, A and B are both strictly increasing.
// (A sequence is strictly increasing if and only if A[0] < A[1] < A[2] < ... < A[A.length - 1].)

// Given A and B, return the minimum number of swaps to make both sequences strictly increasing.
// It is guaranteed that the given input always makes it possible.

class Solution
{
public:
    int minSwap(vector<int> &A, vector<int> &B)
    {
        return memoized(A, B);
    }

    int memoized(vector<int> &A, vector<int> &B)
    {
        vector<vector<int>> memo(2, vector<int>(A.size(), -1));

        int dontSwap = memoizedInner(A, B, 1, 0, memo);
        // if it would make no difference to swap 0, then don't
        if (A[0] == B[0])
            return dontSwap;

        int doSwap = memoizedInner(A, B, 1, 1, memo);

        if (doSwap == -1)
            return dontSwap;
        if (dontSwap == -1)
            return doSwap + 1;
        return min(doSwap + 1, dontSwap);
    }

    int memoizedInner(vector<int> &A, vector<int> &B, int i, int swappedLast, vector<vector<int>> &memo)
    {
        if (i == A.size())
            return 0;

        bool okIfNotSwapped = A[i] > A[i - 1] && B[i] > B[i - 1];
        bool okIfSwapped = A[i] > B[i - 1] && B[i] > A[i - 1];

        if (swappedLast == 1)
        {
            bool temp = okIfNotSwapped;
            okIfNotSwapped = okIfSwapped;
            okIfSwapped = temp;
        }

        // if we've entered an invalid state, return -1
        // e.g., we can't use this arrangement and we can't swap
        if (!okIfNotSwapped && !okIfSwapped)
            return -1;

        if (memo[swappedLast][i] == -1)
        {
            int dontSwap = okIfNotSwapped ? memoizedInner(A, B, i + 1, false, memo) : -1;
            if (A[i] == B[i])
                return memo[swappedLast][i] = dontSwap;

            int doSwap{-1};
            if (okIfSwapped)
                doSwap = memoizedInner(A, B, i + 1, true, memo);

            if (doSwap == -1)
                return memo[swappedLast][i] = dontSwap;
            if (dontSwap == -1)
                return memo[swappedLast][i] = doSwap + 1;
            return memo[swappedLast][i] = min(doSwap + 1, dontSwap);
        }

        return memo[swappedLast][i];
    }
};