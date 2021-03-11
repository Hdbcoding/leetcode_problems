#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

// Alien Dictionary - Hard

// There is a new alien language which uses the latin alphabet. However, the
// order among letters are unknown to you. You receive a list of non-empty words
// from the dictionary, where words are sorted lexicographically by the rules of
// this new language. Derive the order of letters in this language.
// You may assume all letters are in lowercase.
// You may assume that if a is a prefix of b, then a must appear before b in the
// given dictionary.
// If the order is invalid, return an empty string.
// There may be multiple valid order of letters, return any one of them is fine.

struct Node
{
    char c;
    bool visited{false};
    unordered_set<char> children;

    Node(char ch)
    {
        this->c = ch;
    }
};

class Solution
{
    void buildGraph(vector<string> &words, vector<Node *> &graph, int start, int end, int col)
    {
        // nothing to do
        if (start > end)
            return;

        // sometimes a word is just really long
        if (start == end)
        {
            if (col < words[start].size())
            {
                addNode(graph, words[start][col]);
                buildGraph(words, graph, start, end, col + 1);
            }
            return;
        }

        char oldC = '_';
        int nextStart = 0;
        int nextEnd = -1;
        bool sawChar = false;
        for (int i = start; i <= end; ++i)
        {
            if (col >= words[i].size())
            {
                if (sawChar)
                    throw "invalid position for empty char";
                continue;
            }
            else
            {
                sawChar = true;
            }

            char c = words[i][col];
            addNode(graph, c);
            if (oldC == '_')
            {
                oldC = c;
                nextStart = nextEnd = i;
            }
            else if (c == oldC)
            {
                ++nextEnd;
            }
            else
            {
                // oldC < c, so add an edge from oldC -> c
                addEdge(graph, oldC, c);
                // build graph for the next column
                buildGraph(words, graph, nextStart, nextEnd, col + 1);
                oldC = c;
                nextStart = nextEnd = i;
            }
        }
        // in case we didn't hit that last else,
        // make sure to check if we missed the last group
        buildGraph(words, graph, nextStart, nextEnd, col + 1);
    }

    void addNode(vector<Node *> &graph, char a)
    {
        if (graph[a - 'a'] == nullptr)
            graph[a - 'a'] = new Node(a);
    }

    void addEdge(vector<Node *> &graph, char a, char b)
    {
        graph[a - 'a']->children.insert(b);
    }

    string toposort(vector<Node *> &graph)
    {
        vector<char> alphabet;
        for (Node *a : graph)
        {
            if (a == nullptr)
                continue;
            dfsOrder(graph, a, alphabet);
        }
        reverse(alphabet.begin(), alphabet.end());
        // check for cycle - is any letter bigger than its children?
        unordered_map<char, int> pos;
        for (int i = 0; i < alphabet.size(); ++i)
        {
            pos[alphabet[i]] = i;
        }
        for (int i = 0; i < alphabet.size(); ++i)
        {
            int p1 = pos[alphabet[i]];
            Node *n = graph[alphabet[i] - 'a'];
            for (char c : n->children)
            {
                int p2 = pos[c];
                if (p1 > p2)
                    return "";
            }
        }

        string result(alphabet.size(), 'a');
        for (int i = 0; i < alphabet.size(); ++i)
        {
            result[i] = alphabet[i];
        }

        return result;
    }

    void dfsOrder(vector<Node *> &graph, Node *a, vector<char> &alphabet)
    {
        if (a->visited)
            return;
        a->visited = true;
        int maxOrder = -1;
        for (const char &c : a->children)
            dfsOrder(graph, graph[c - 'a'], alphabet);
        alphabet.push_back(a->c);
    }

public:
    string alienOrder(vector<string> &words)
    {
        vector<Node *> graph(26);
        try
        {
            buildGraph(words, graph, 0, words.size() - 1, 0);
            return toposort(graph);
        }
        catch (...)
        {
            return "";
        }
    }
};