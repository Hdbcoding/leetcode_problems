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
    vector<trie *> branches;

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

    int getInt(char c)
    {
        return c == ' ' ? 26 : c - 'a';
    }

    trie *getBranch(char c)
    {
        int index = getInt(c);
        return branches[index];
    }

    trie *addBranch(char c)
    {
        int index = getInt(c);
        if (branches[index] == nullptr)
            branches[index] = new trie();
        return branches[index];
    }
};

struct hot
{
    string sentence;
    int times;

    bool operator<(const hot &other) const
    {
        if (times > other.times)
            return true;
        if (times < other.times)
            return false;

        int compare = sentence.compare(other.sentence);
        if (compare < 0)
            return true;
        return false;
    }
};

class AutocompleteSystem
{
    trie *root{new trie()};

    trie *currentT{nullptr};
    string currentS{""};
    char currentC{'#'};

    void insert(trie *t, string s, int times)
    {
        for (int i = 0; i < s.size(); ++i)
            t = t->addBranch(s[i]);
            
        // last node in a branch gets a sentence length
        t->times += times;
    }

    vector<string> lookupNext()
    {
        if (currentT == nullptr)
            return {};

        currentT = currentT->getBranch(currentC);

        if (currentT == nullptr)
            return {};

        priority_queue<hot> top3;
        traverse(currentS, currentT, top3);

        vector<string> res;
        while (!top3.empty())
        {
            res.push_back(top3.top().sentence);
            top3.pop();
        }
        reverse(res.begin(), res.end());

        return res;
    }

    void traverse(string s, trie *t, priority_queue<hot> &ret)
    {
        queue<pair<trie *, string>> toVisit;
        toVisit.push({t, s});

        while (!toVisit.empty())
        {
            auto &next = toVisit.front();
            auto nextT = next.first;
            auto nextS = next.second;
            toVisit.pop();

            if (nextT->times > 0)
                addToResult(nextS, nextT->times, ret);

            for (char c = 'a'; c <= 'z'; ++c)
                tryAddToQueue(nextT, c, nextS, toVisit);

            tryAddToQueue(nextT, ' ', nextS, toVisit);
        }
    }

    void addToResult(string &s, int times, priority_queue<hot> &ret)
    {
        ret.push({s, times});
        if (ret.size() == 4)
            ret.pop();
    }

    void tryAddToQueue(trie *t, char c, const string &s, queue<pair<trie *, string>> &toVisit)
    {
        trie *next = t->getBranch(c);
        if (next != nullptr)
            toVisit.push({next, s + c});
    }

public:
    AutocompleteSystem(vector<string> &sentences, vector<int> &times)
    {
        for (int i = 0; i < sentences.size(); ++i)
            insert(root, sentences[i], times[i]);
        currentT = root;
    }

    ~AutocompleteSystem()
    {
        delete root;
    }

    vector<string> input(char c)
    {
        if (c == '#')
        {
            insert(root, currentS, 1);
            currentT = root;
            currentS = "";
            return {};
        }

        currentC = c;
        currentS += c;

        return lookupNext();
    }
};