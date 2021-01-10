#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <vector>
using namespace std;

// Most stones removed with same row or column - Medium

// On a 2D plane, we place n stones at some integer coordinate points. 
//  Each coordinate point may have at most one stone.

// A stone can be removed if it shares either the same row or the same column as another stone that has not been removed.

// Given an array stones of length n where stones[i] = [xi, yi] represents the location of the ith stone, 
//  return the largest possible number of stones that can be removed.

class Solution {
public:
    typedef unordered_map<int, unordered_set<int>> coordSet;
    
    // for every row, collect each stone in a list (value will be column)
    coordSet rows;
    // vice versa for columns
    coordSet cols;
        
    int removeStones(vector<vector<int>>& stones) {
        if (stones.size() <= 1) return 0;
        
        for (auto &pair : stones) {
            rows[pair[0]].insert(pair[1]);
            cols[pair[1]].insert(pair[0]);
        }
        
        int totalRemoved = 0;
        while (!rows.empty()){
            auto pair = rows.begin();
            int x = pair->first;
            int y = *(pair->second.begin());
            int currentCount = dfsCount(x, y);
            totalRemoved += currentCount;
        }
        
        return totalRemoved;
    }
    
    int dfsCount(int x, int y)
    {
        int count = -1;
        stack<pair<int, int>> toVisit;
        removeFromMaps(x, y);
        toVisit.push({x, y});
        
        while (!toVisit.empty()){
            ++count;
            pair<int, int> next = toVisit.top();
            toVisit.pop();
            
            // find the next x neighbor
            auto rowiter = rows.find(next.first);
            if (rowiter != rows.end())
            {
                int otherY = *(rowiter->second.begin());
                removeFromMaps(next.first, otherY);
                toVisit.push({next.first, otherY});
            }
            
            // find the next y neighbor
            auto coliter = cols.find(next.second);
            if (coliter != cols.end()){
                int otherX = *(coliter->second.begin());
                removeFromMaps(otherX, next.second);
                toVisit.push({otherX, next.second});
            }
        }
        
        return count;
    }
    
    void removeFromMaps(int x, int y)
    {
        rows[x].erase(y);
        if (rows[x].empty()) rows.erase(x);
        
        cols[y].erase(x);
        if (cols[y].empty()) cols.erase(y);
    }
};