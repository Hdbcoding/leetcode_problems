#include <vector>
#include <random>

using namespace std;

// Random Pick with Weight - Medium

class Solution {
    vector<int> numsTotal;
    default_random_engine dre;
    uniform_int_distribution<int> dist;
public:
    Solution(vector<int>& w) : dre(), numsTotal(w.size()) {
        int prefix = 0;
        for (int i = 0; i < w.size(); ++i)
        {
            prefix += w[i];
            numsTotal[i] = prefix;
        }
        dist = uniform_int_distribution<int>(0, numsTotal.back());
    }
    
    int pickIndex() {
        // int target = dist(dre);
        // return upper_bound(numsTotal.begin(), numsTotal.end(), target) - numsTotal.begin();
        float randNum = (float) rand() / RAND_MAX;
        float target =  randNum * numsTotal.back();
        
        int lo = 0; 
        int hi = numsTotal.size();
        while (lo < hi)
        {
            int m = (lo + hi) / 2;
            if (target >= numsTotal[m])
                lo = m + 1;
            else
                hi = m;
        }
        
        return lo;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(w);
 * int param_1 = obj->pickIndex();
 */