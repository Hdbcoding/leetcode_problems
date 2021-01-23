#include <string>
#include <unordered_map>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;
// Evaluate Division - Medium

// You are given an array of variable pairs equations and an array of real numbers values,
// where equations[i] = [Ai, Bi] and values[i] represent the equation Ai / Bi = values[i].
// Each Ai or Bi is a string that represents a single variable.

// You are also given some queries, where queries[j] = [Cj, Dj] represents the jth query
// where you must find the answer for Cj / Dj = ?.

// Return the answers to all queries. If a single answer cannot be determined, return -1.0.

// Note: The input is always valid. You may assume that evaluating the queries will not result in
// division by zero and that there is no contradiction.

class Solution
{
public:
    double search(string &a,
                  string &b,
                  unordered_map<string, int> &nodeIndices,
                  vector<string> &nodes,
                  vector<vector<pair<int, double>>> &edges)
    {
        // if either node is missing from the set, return -1;
        auto startIt = nodeIndices.find(a);
        if (startIt == nodeIndices.end())
            return -1;
        int start = startIt->second;

        auto endIt = nodeIndices.find(b);
        if (endIt == nodeIndices.end())
            return -1;
        int end = endIt->second;

        // if we are going to the start, return 1
        if (a == b)
            return 1;

        // all distances from start
        vector<double> d(nodes.size(), 0);
        d[start] = 0;
        vector<bool> seen(nodes.size(), false);
        seen[start] = true;

        queue<int> toVisit;
        toVisit.push(start);
        while (!toVisit.empty())
        {
            int n = toVisit.front();
            toVisit.pop();
            for (auto edge : edges[n])
            {
                if (seen[edge.first])
                    continue;
                d[edge.first] = d[n] + edge.second;
                toVisit.push(edge.first);
            }
            seen[n] = true;
            if (n == end)
                break;
        }

        return seen[end] ? exp(d[end]) : -1;
    }

    vector<double> calcEquation(vector<vector<string>> &equations, vector<double> &values, vector<vector<string>> &queries)
    {
        // nodes
        vector<string> nodes;
        // edge exists from a to b
        vector<vector<pair<int, double>>> edges;
        // node index map
        unordered_map<string, int> nodeIndices;

        int index{0};
        for (int i = 0; i < equations.size(); ++i)
        {
            double v = log(values[i]);
            vector<string> p = equations[i];

            // find or add p[0]
            auto it1 = nodeIndices.find(p[0]);
            if (it1 == nodeIndices.end())
            {
                nodeIndices[p[0]] = index++;
                nodes.push_back(p[0]);
                edges.push_back({});
                it1 = nodeIndices.find(p[0]);
            }

            // find or add p[1]
            auto it2 = nodeIndices.find(p[1]);
            if (it2 == nodeIndices.end())
            {
                nodeIndices[p[1]] = index++;
                nodes.push_back(p[1]);
                edges.push_back({});
                it2 = nodeIndices.find(p[1]);
            }

            edges[it1->second].push_back({it2->second, v});
            edges[it2->second].push_back({it1->second, -v});
        }

        vector<double> results(queries.size(), -1);
        for (int i = 0; i < queries.size(); ++i)
        {
            vector<string> query = queries[i];
            results[i] = search(query[0], query[1], nodeIndices, nodes, edges);
        }

        return results;
    }
};