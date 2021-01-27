#include <vector>
#include <string>
#include <queue>
#include <algorithm>
using namespace std;

// Design Search Autocomplete System - Harm

// Design a search autocomplete system for a search engine. 
// Users may input a sentence (at least one word and end with a special character '#'). 
// For each character they type except '#', you need to return the top 3 historical hot sentences that have prefix the same as the part of sentence already typed. 
// Here are the specific rules:

// The hot degree for a sentence is defined as the number of times a user typed the exactly same sentence before.
// The returned top 3 hot sentences should be sorted by hot degree (The first is the hottest one). 
// If several sentences have the same degree of hot, you need to use ASCII-code order (smaller one appears first).
// If less than 3 hot sentences exist, then just return as many as you can.
// When the input is a special character, it means the sentence ends, and in this case, you need to return an empty list.
// Your job is to implement the following functions:

// The constructor function:

// AutocompleteSystem(String[] sentences, int[] times): This is the constructor. The input is historical data. 
// Sentences is a string array consists of previously typed sentences. 
// Times is the corresponding times a sentence has been typed. 
// Your system should record these historical data.

// Now, the user wants to input a new sentence. 
// The following function will provide the next character the user types:

// List<String> input(char c): The input c is the next character typed by the user. 
// The character will only be lower-case letters ('a' to 'z'), blank space (' ') or a special character ('#'). 
// Also, the previously typed sentence should be recorded in your system. 
// The output will be the top 3 historical hot sentences that have prefix the same as the part of sentence already typed.

struct trie
{
    int times{0};
    vector<trie*> branches;
    
    trie()
    {
        branches.assign(27, nullptr);
    }
    
    ~trie()
    {
        for (int i = 0; i < 27; ++i)
            if (branches[i] != nullptr) 
                delete branches[i];
    }
};

struct hot
{
    string sentence;
    int times;
    
    bool operator <(const hot& other) const
    {
        if (times > other.times) return true;
        if (times < other.times) return false;
        
        int compare = sentence.compare(other.sentence);
        if (compare < 0) return true;
        return false;
    }
};

class AutocompleteSystem {
    trie *root{new trie()};
    
    trie *currentT{nullptr};
    string currentS{""};
    char lastc{'#'};
    
    int getInt(char c)
    {
        return c == ' ' ? 26 : c - 'a';
    }
    
    void insert(trie *t, string s, int times){
        for (int i = 0; i < s.size(); ++i)
        {
            int index = getInt(s[i]);
            if (t->branches[index] == nullptr)
                t->branches[index] = new trie();
            
            t = t->branches[index];
        }
        t->times += times; // last node in a branch gets a sentence length
    }
    
    priority_queue<hot> lookup(trie *t, string s)
    {
        priority_queue<hot> ret;
        
        for (int i = 0; i < s.size(); ++i)
        {
            int index = getInt(s[i]);
            trie *next = t->branches[index];
            if (next == nullptr) return ret;
            
            t = next;
        }
        traverse(s, t, ret);
        
        return ret;
    }
    
    priority_queue<hot> lookupNext()
    {
        int index = getInt(lastc);
        trie *next = currentT->branches[index];
        if (next == nullptr) return {};
        currentT = next;
        priority_queue<hot> ret;
        traverse(currentS, next, ret);
        return ret;
    }
    
    void traverse(string s, trie *t, priority_queue<hot> &ret)
    {
        if (t->times > 0) addToQueue(s, t->times, ret);
        for (char i = 'a'; i <= 'z'; ++i)
            doTraverse(s, i, t, ret);
        doTraverse(s, ' ', t, ret);
    }
    
    void addToQueue(string &s, int times, priority_queue<hot> &ret)
    {
        ret.push({s, times});
        if (ret.size() == 4) ret.pop();
    }
    
    void doTraverse(string s, char c, trie *t, priority_queue<hot> &ret)
    {
        int index = getInt(c);
        if (t->branches[index] != nullptr)
            traverse(s + c, t->branches[index], ret);
    }
    
public:
    AutocompleteSystem(vector<string>& sentences, vector<int>& times) {
        for (int i = 0; i < sentences.size(); ++i)
            insert(root, sentences[i], times[i]);
        currentT = root;
    }
    
    ~AutocompleteSystem()
    {
        delete root;
    }
    
    vector<string> input(char c) {
        lastc = c;
        if (c == '#')
        {
            insert(root, currentS, 1);
            currentT = root;
            currentS = "";
            return {};
        }
        
        currentS += c;
        // priority_queue<hot> list = lookup(root, currentS);
        priority_queue<hot> list = lookupNext();
        
        vector<string> res;
        while (!list.empty())
        {
            res.push_back(list.top().sentence);
            list.pop();
        }
        reverse(res.begin(), res.end());
        
        return res;
    }
};