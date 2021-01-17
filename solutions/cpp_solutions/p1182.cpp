#include <vector>
#include <cmath>
using namespace std;

// Shortest Distance to Target Color - Medium

// You are given an array colors, in which there are three colors: 1, 2 and 3.

// You are also given some queries. Each query consists of two integers i and c, 
//   return the shortest distance between the given index i and the target color c. 
// If there is no solution return -1.

class Solution {
public:
    int findClosest(int i, int color, vector<int>& colors, vector<int> &indices){
        if (colors[i] == color) return 0;
        if (indices.size() == 0) return -1;
        if (indices.size() == 1) return abs(indices[0] - i);
        
        int l{0}, r{(int)indices.size() - 1};
        int bestDiff = -1;
        int bestIndex = -1;
        while (l <= r) {
            int m = (l + r) / 2;
            int mid = indices[m];
            int diff = abs(mid - i);
            if (bestDiff == -1 || diff < bestDiff){
                bestDiff = diff;
                bestIndex = mid;
            }
            
            if (mid < i) {
                l = m + 1;
            } else {
                r = m - 1;
            }
        }
        return bestDiff;
    }
    
    vector<int> shortestDistanceColor(vector<int>& colors, vector<vector<int>>& queries) {
        vector<int> indices1{};        
        vector<int> indices2{};
        vector<int> indices3{};
        vector<int> result{};
        
        for (int i = 0; i < colors.size(); ++i)
        {
            switch(colors[i])
            {
                case 1: 
                    indices1.push_back(i);
                    break;
                case 2: 
                    indices2.push_back(i);
                    break;
                case 3: 
                    indices3.push_back(i);
                    break;
            }
        }
        
        for (auto &pair : queries){
            int index = pair[0];
            int color = pair[1];
            int closest;
            switch(color)
            {
                case 1:
                    closest = findClosest(index, color, colors, indices1);
                    break;
                case 2:
                    closest = findClosest(index, color, colors, indices2);
                    break;
                case 3:
                    closest = findClosest(index, color, colors, indices3);
                    break;
            }
            result.push_back(closest);
        }

        return result;
    }
};