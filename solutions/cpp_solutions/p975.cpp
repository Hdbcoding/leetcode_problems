#include <vector>
#include <stack>
#include <algorithm>
#include <map>
using namespace std;
// Odd Even Jump - Hard

// You are given an integer array A. From some starting index, you can make a series of jumps. 
// The (1st, 3rd, 5th, ...) jumps in the series are called odd-numbered jumps, 
// and the (2nd, 4th, 6th, ...) jumps in the series are called even-numbered jumps. 
// Note that the jumps are numbered, not the indices.

// You may jump forward from index i to index j (with i < j) in the following way:

// During odd-numbered jumps (i.e., jumps 1, 3, 5, ...), you jump to the index j such that A[i] <= A[j] and A[j] is the smallest possible value. 
// If there are multiple such indices j, you can only jump to the smallest such index j.

// During even-numbered jumps (i.e., jumps 2, 4, 6, ...), you jump to the index j such that A[i] >= A[j] and A[j] is the largest possible value. 
// If there are multiple such indices j, you can only jump to the smallest such index j.

// It may be the case that for some index i, there are no legal jumps.
// A starting index is good if, starting from that index, you can reach the end of the array (index A.length - 1) by jumping some number of times (possibly 0 or more than once).

// Return the number of good starting indices.

struct index_comparator
{
    vector<int> a;
    bool desc;
    
    bool operator() (const int &i, const int &j)
    {
        if (a[i] == a[j]) return i < j;
        return (desc ? a[i] > a[j] : a[i] < a[j]);
    }
};

class Solution {
    void fillNextJumpVector(vector<int> &jumps, vector<int> &indices)
    {
        stack<int> s;
        for (int i : indices)
        {
            // while i is greater than everything in the stack
            while (!s.empty() && i > s.top())
            {
                // mark i as the destination of everything in the stack
                int j = s.top();
                s.pop();
                jumps[j] = i;
            }
            s.push(i);
        }
    }
    
    // even though this is o(nlogn), it times out for larger inputs
    int monotonicStack(vector<int>& A)
    {
        vector<int> indices(A.size());
        for (int i = 0; i < A.size(); ++i) indices[i] = i;
        index_comparator comp{A};
        
        // build monotonic stacks of the next available odd jump location 
        // sort indices by increasing value for odd (increasing value) jumps
        sort(indices.begin(), indices.end(), comp);
        vector<int> nextOdd(A.size(), -1);
        fillNextJumpVector(nextOdd, indices);
        
        // build monotonic stacks of the next available even jump location  
        // reverse sort for decreasing values    
        comp.desc = true;
        sort(indices.begin(), indices.end(), comp);
        vector<int> nextEven(A.size(), -1);
        fillNextJumpVector(nextEven, indices);
        
        // reverse order dp
        // we can always get to the last location, whether by an even or an odd jump
        vector<bool> odd(A.size(), false);
        vector<bool> even(A.size(), false);
        odd[A.size() - 1] = true;
        even[A.size() - 1] = true;
        for (int i = A.size() - 2; i >= 0; --i)
        {
            // for each index before that, does an odd or an even jump from here lead to the end?
            if (nextOdd[i] != -1)
                odd[i] = even[nextOdd[i]];
            if (nextEven[i] != -1)
                even[i] = odd[nextEven[i]];
        }
        
        int count = 0;
        for (bool v : odd)
            if (v) ++count;

        return count;
    }
    
    int withMap(vector<int>& A)
    {
        int result = 1;
        int n = A.size();
        
        vector<bool> oddJump(n, false), evenJump(n, false);
        // balanced bst of already seen values -> indices
        map<int, int> seen;
        
        oddJump[n - 1] = evenJump[n - 1] = true;
        seen[A[n - 1]] = n - 1;
        
        for (int i = n - 2; i >= 0; --i)
        {
            // if we've already seen this key, we can check for even and odd jumps from here
            auto findIt = seen.find(A[i]);
            if (findIt != seen.end())
            {
                oddJump[i] = evenJump[findIt->second];
                evenJump[i] = oddJump[findIt->second];
            } else {
                // otherwise, check for the next greater and next lower elements
                // upper_bound -> first thing strictly greater than v
                auto oddIt = seen.upper_bound(A[i]);
                if (oddIt != seen.end()) oddJump[i] = evenJump[oddIt->second];
                
                // lower_bound -> first thing equal to or greater than v
                // (so we need to take the predecessor of lower bound, if it isn't the beginning)
                auto evenIt = seen.lower_bound(A[i]);
                if (evenIt == seen.begin()) evenIt = seen.end();
                else evenIt = prev(evenIt);
                if (evenIt != seen.end()) evenJump[i] = oddJump[evenIt->second];
            }
            
            // record the earliest index where we have seen this value
            seen[A[i]] = i;
            if (oddJump[i]) ++result;
        }
        return result;
    }
    
public:
    int oddEvenJumps(vector<int>& A) {
        return withMap(A);
    }
};