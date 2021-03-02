#include <vector>
#include <unordered_map>

using namespace std;

// Number of Islands II - Hard

// A 2d grid map of m rows and n columns is initially filled with water. 
// We may perform an addLand operation which turns the water at position (row, col) into a land. 
// Given a list of positions to operate, count the number of islands after each addLand operation. 
// An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. 
// You may assume all four edges of the grid are all surrounded by water.

class Solution {
public:
    vector<int> numIslands2(int m, int n, vector<vector<int>>& positions) {
        // representative parent
        vector<int> parents(positions.size(), -1);
        for (int i = 0; i < parents.size(); ++i)
            parents[i] = i;
        vector<int> result(positions.size(), 1);
        // index of this position in the parents array
        unordered_map<int, unordered_map<int,int>> lookup;
        for (int i = 0; i < positions.size(); ++i)
        {
            pair<int,int> here = {positions[i][0], positions[i][1]};
            
            // if I've already seen this piece of land before, skip it
            int location = getLocation(lookup, here);
            if (location != -1)
            {
                if (i > 0)
                    result[i] = result[i-1];
                
                continue;
            }
            
            lookup[here.first][here.second] = i;
            vector<int> neighbors = {
                getLocation(lookup, {here.first - 1, here.second}),
                getLocation(lookup, {here.first + 1, here.second}),
                getLocation(lookup, {here.first, here.second - 1}),
                getLocation(lookup, {here.first, here.second + 1})
            };
            
            // if I made no combinations, then we have a new island
            // if I made 1 combination, we have no new islands
            int comboCount = 0;
            for (auto &j : neighbors)
            {
                if (j == -1) continue;
                // if we are not on the same island
                int nParent = getParent(parents, j);
                int mParent = getParent(parents, i);
                if (nParent != mParent)
                {
                    // combine our islands
                    ++comboCount;
                    parents[nParent] = mParent;
                }
            }
            
            if (i == 0)
                result[i] = 1;
            else {
                if (comboCount == 0)
                {
                    result[i] = result[i-1] + 1;
                } else {
                    result[i] = result[i-1] - comboCount + 1;
                }
            }
        }
        return result;
    }
    
    int getLocation(unordered_map<int, unordered_map<int,int>> &lookup, const pair<int,int> &pos)
    {
        auto it = lookup.find(pos.first);
        if (it == lookup.end())
            return -1;
        auto it2 = it->second.find(pos.second);
        if (it2 == it->second.end())
            return -1;
        return it2->second;
    }
    
    int getParent(vector<int> &parents, int index)
    {
        // essentially union find with path compression
        if (parents[index] != index)
        {
            parents[index] = getParent(parents, parents[index]);
            return parents[index];
        }
        return index;
    }
};