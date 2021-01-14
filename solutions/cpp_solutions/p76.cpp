#include <string>
#include <unordered_set>
#include <unordered_map>
using namespace std;

// Minimum Window Substring - Hard

// Given two strings s and t, return the minimum window in s which will contain all the characters in t.
// If there is no such window in s that covers all characters in t, return the empty string "".

// Note that If there is such a window, it is guaranteed that there will always be only one unique minimum window in s.

class Solution
{
    bool covering(unordered_map<char, int> &scounts, unordered_map<char, int> &tchars)
    {
        if (tchars.size() > scounts.size())
            return false;

        for (auto &pair : tchars)
        {
            auto found = scounts.find(pair.first);
            if (found == scounts.end())
                return false;
            if (pair.second > found->second)
                return false;
        }
        return true;
    }

public:
    // this version using a separate method to calculate the covering of the s and t maps
    // this increases the runtime to O(S*T)
    // it's possible to do the sliding window without this
    string o_st_time_sliding_window(string s, string t)
    {
        unordered_map<char, int> tchars;
        for (char tc : t)
            tchars[tc]++;

        unordered_map<char, int> scounts;
        int bestl = 0, bestr = 0;
        string best;
        int l = 0;
        int r = 0;
        while (r <= s.size())
        {
            // if this is a covering map
            if (covering(scounts, tchars))
            {
                // if this is a better substring than the best one we found previously, store it
                if (bestl == bestr || bestr - bestl > r - l)
                {
                    bestl = l;
                    bestr = r;
                    if (r - l == t.size())
                        break;
                }

                // slide the left pointer to the right
                scounts[s[l]]--;
                ++l;
            }
            else
            {
                scounts[s[r]]++;
                ++r;
            }
        }
        return bestr - bestl == 0 ? "" : s.substr(bestl, bestr - bestl);
    }

    string betterSlidingWindow(string s, string t)
    {
        unordered_map<char, int> tchars;
        for (char tc : t)
            tchars[tc]++;

        unordered_map<char, int> scounts;
        int bestl{-1}, bestr{-1};
        string best;
        int l{0};
        int r{0};

        // if formed == tchars.size(), we're done forming t in this sliding window
        int formed{0};

        while (r < s.length())
        {
            // get the char from the right side of the window
            char cr = s[r];
            scounts[cr]++;
            auto found = tchars.find(cr);
            if (found != tchars.end() && scounts[cr] == tchars[cr])
                ++formed;

            // if the dictionary is satisfied, contract the left side of the window
            while (l <= r && formed == tchars.size()){
                char cl = s[l];
                // if we found a better solution than before, record it
                if (bestr == -1 || bestr - bestl > r - l){
                    bestr = r;
                    bestl = l;
                    if (r - l + 1 == t.size())
                        return s.substr(bestl, bestr - bestl + 1);
                }
                scounts[cl]--;
                found = tchars.find(cl);
                if (found != tchars.end() && scounts[cl] < tchars[cl])
                    --formed;
                ++l;
            }
            ++r;
        }
        return bestr == -1 ? "" : s.substr(bestl, bestr - bestl + 1);
    }

    string minWindow(string s, string t)
    {
        return betterSlidingWindow(s, t);
    }
};