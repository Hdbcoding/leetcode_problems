#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
using namespace std;

// Sentence Similarity - Easy

// We can represent a sentence as an array of words, for example, the sentence "I am happy with leetcode" 
// can be represented as arr = ["I","am",happy","with","leetcode"].

// Given two sentences sentence1 and sentence2 each represented as a string array and given an array of string pairs 
// similarPairs where similarPairs[i] = [xi, yi] indicates that the two words xi and yi are similar.

// Return true if sentence1 and sentence2 are similar, or false if they are not similar.

// Two sentences are similar if:

// They have the same length (i.e. the same number of words)
// sentence1[i] and sentence2[i] are similar.
// Notice that a word is always similar to itself, also notice that the similarity relation is not transitive. 
// For example, if the words a and b are similar and the words b and c are similar, a and c are not necessarily similar.

class Solution {
public:
    bool areSentencesSimilar(vector<string>& sentence1, vector<string>& sentence2, vector<vector<string>>& similarPairs) {
        if (sentence1.size() != sentence2.size()) return false;
        
        unordered_map<string, unordered_set<string>> similarWords;
        for (auto &pair : similarPairs)
        {
            similarWords[pair[0]].insert(pair[1]);
            similarWords[pair[1]].insert(pair[0]);
        }
        
        for (int i = 0; i < sentence1.size(); ++i)
        {
            if (sentence1[i] == sentence2[i]) 
                continue;
            
            auto set = similarWords[sentence1[i]];
            auto found = set.find(sentence2[i]);
            if (found == set.end())
                return false;
        }
        return true;
    }
};