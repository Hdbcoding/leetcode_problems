#include <vector>
#include <string>
#include <unordered_set>
#include <sstream>
using namespace std;

// Occurrences after bigram - easy

// Given words first and second, consider occurrences in some text of the form "first second third", where second comes immediately after first, and third comes immediately after second.

// For each such occurrence, add "third" to the answer, and return the answer.

class Solution {
public:
    vector<string> findOcurrences(string text, string first, string second) {
        // indices of first
        unordered_set<int> firstSet;
        // indices of second
        unordered_set<int> secondSet;
        // words by index
        vector<string> wordMap;
        vector<string> result;
        
        // fill maps with words
        stringstream ss;
        string word;
        int i = 0;
        for (char c : text){
            if (c == ' '){
                word = ss.str();
                wordMap.push_back(word);
                if (word == first) firstSet.insert(i);
                else if (word == second) secondSet.insert(i);
                ss.str(string());
                ++i;
            } else {
                ss << c;
            }
        }
        word = ss.str();
        wordMap.push_back(word);
        if (word == first) firstSet.insert(i);
        else if (word == second) secondSet.insert(i);
        
        for (auto &j : firstSet){
            if (secondSet.count(j + 1) && j + 2 < wordMap.size())
                result.push_back(wordMap[j + 2]);
        }
        
        return result;
    }
};