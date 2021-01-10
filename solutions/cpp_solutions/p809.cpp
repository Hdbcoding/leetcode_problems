#include <vector>
#include <string>
using namespace std;
// Expressive words - medium

// Sometimes people repeat letters to represent extra feeling, such as "hello" -> "heeellooo", "hi" -> "hiiii".  
// In these strings like "heeellooo", we have groups of adjacent letters that are all the same:  "h", "eee", "ll", "ooo".

// For some given string S, a query word is stretchy if it can be made to be equal to 
//  S by any number of applications of the following extension operation: 
//  choose a group consisting of characters c, and add some number of characters c to the group so that the size of the group is 3 or more.

// For example, starting with "hello", we could do an extension on the group "o" to get "hellooo", 
//  but we cannot get "helloo" since the group "oo" has size less than 3.  
//  Also, we could do another extension like "ll" -> "lllll" to get "helllllooo".  
//  If S = "helllllooo", then the query word "hello" would be stretchy because of these two extension operations: 
//  query = "hello" -> "hellooo" -> "helllllooo" = S.

// Given a list of query words, return the number of words that are stretchy. 

class Solution {
public:
    struct stretchy
    {
        char c;
        int count;
    };
      
    vector<stretchy> buildStretchyMap(string s){
        vector<stretchy> result;
        char c{s[0]};
        int count = 1;
        for (int i = 1; i < s.size(); ++i){
            if (s[i] != c) {
                result.push_back({c, count});
                c = s[i];
                count = 1;
            } else {
                ++count;
            }
        }
        
        result.push_back({c, count});
        
        return result;
    }
    
    int expressiveWords(string S, vector<string>& words) {
        if (S.size() == 0 || words.size() == 0) return 0;
        
        auto smap = buildStretchyMap(S);
        
        int count = 0;
        for (string w : words){
            auto wmap = buildStretchyMap(w);
            // could save time here if I knew the whole key for the map
            if (smap.size() != wmap.size()) continue;
            
            bool madeExtension = false;
            for (int i = 0; i < smap.size(); ++i){
                stretchy si = smap[i];
                stretchy wi = wmap[i];
                // different char, obviously not right
                if (si.c != wi.c) {
                    madeExtension = false;
                    break;
                }
                // the source word has fewer of this char than the candidate, obviously not right
                if (si.count < wi.count) 
                {
                    madeExtension = false;
                    break;
                }
                
                if (si.count > wi.count){
                    if (si.count >= 3) madeExtension = true;
                    else {
                        madeExtension = false;
                        break;
                    }
                }
            }
            if (madeExtension) count++;
        }
        return count;
    }
};