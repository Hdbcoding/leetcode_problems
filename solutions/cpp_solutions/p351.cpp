#include <vector>
using namespace std;

// Android Unlock Patterns - Medium

// Android devices have a special lock screen with a 3 x 3 grid of dots. 
// Users can set an "unlock pattern" by connecting the dots in a specific sequence, forming a series of joined line 
// segments where each segment's endpoints are two consecutive dots in the sequence. 
// A sequence of k dots is a valid unlock pattern if both of the following are true:

// All the dots in the sequence are distinct.
// If the line segment connecting two consecutive dots in the sequence passes through any other dot, 
// the other dot must have previously appeared in the sequence. 
// No jumps through non-selected dots are allowed.

class Solution {
    int calculatePatterns(int last, int length)
    {
        if (length == 0) return 1;
        int sum = 0;
        for (int i = 0; i < 9; ++i)
        {
            if (isValid(last, i))
            {
                used[i] = true;
                sum += calculatePatterns(i, length - 1);
                used[i] = false;
            }
        }
        return sum;
    }
    
    bool isValid(int last, int next)
    {
        if (used[next]) return false;
        
        if (last == -1) return true;
        
        // 0 1 2
        // 3 4 5
        // 6 7 8
        // adjacent and knight move -> (last + next) % 2 == 1
        if ((last + next) % 2 == 1)
            return true;
        
        // midway happens to be half of sum (last + next) / 2
        int mid = (last + next) / 2;
        if (mid == 4) return used[mid];
        
        // diagonal adjacent if last % 3 != next % 3 and last / 3 != next / 3
        if ((last % 3 != next % 3) && (last / 3 != next / 3))
            return true;
        
        return used[mid];
    }
    
public:
    vector<bool> used;
    
    int numberOfPatterns(int m, int n) {
        used.assign(9, false);
        int result = 0;
        for (int l = m; l <= n; ++l)
        {
            result += calculatePatterns(-1, l);
            used.assign(9, false);
        }
        return result;
    }
};