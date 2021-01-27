#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>
#include <queue>
using namespace std;

// Sentence similarity II - Medium

// Given two sentences words1, words2 (each represented as an array of strings), and a list of similar word pairs pairs, determine if two sentences are similar.

// For example, words1 = ["great", "acting", "skills"] and words2 = ["fine", "drama", "talent"] are similar, if the similar word pairs are pairs = [["great", "good"], ["fine", "good"], ["acting","drama"], ["skills","talent"]].

// Note that the similarity relation is transitive. For example, if "great" and "good" are similar, and "fine" and "good" are similar, then "great" and "fine" are similar.

// Similarity is also symmetric. For example, "great" and "fine" being similar is the same as "fine" and "great" being similar.

// Also, a word is always similar with itself. For example, the sentences words1 = ["great"], words2 = ["great"], pairs = [] are similar, even though there are no specified similar word pairs.

// Finally, sentences can only be similar if they have the same number of words. So a sentence like words1 = ["great"] can never be similar to words2 = ["doubleplus","good"].

class Solution {
    bool search(unordered_map<string, unordered_set<string>> &similarWords, string &start, string &end)
    {
        unordered_set<string> seen;
        queue<string> toVisit;
        toVisit.push(start);
        while (!toVisit.empty())
        {
            string here = toVisit.front();
            toVisit.pop();
            seen.insert(here);
            auto &set = similarWords[here];
            for (auto &word : set)
            {
                if (word == end) 
                    return true;
                auto found = seen.find(word);
                if (found == seen.end())
                {
                    toVisit.push(word);
                }
            }
        }
        return false;
    }
    
public:
    bool areSentencesSimilarTwo(vector<string>& words1, vector<string>& words2, vector<vector<string>>& pairs) {
        if (words1.size() != words2.size()) return false;
        
        unordered_map<string, unordered_set<string>> similarWords;
        for (auto &pair : pairs)
        {
            similarWords[pair[0]].insert(pair[1]);
            similarWords[pair[1]].insert(pair[0]);
        }
        
        for (int i = 0; i < words1.size(); ++i)
        {
            if (words1[i] == words2[i]) 
                continue;
            
            auto &set = similarWords[words1[i]];
            auto found = set.find(words2[i]);
            if (found == set.end() && !search(similarWords, words1[i], words2[i]))
                return false;
        }
        return true;
    }
};