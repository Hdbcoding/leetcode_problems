#include <vector>
#include <algorithm>
using namespace std;

// Container With Most Water - Medium
// Given n non-negative integers a1, a2, ..., an , where each represents a point at coordinate (i, ai). n vertical lines 
// are drawn such that the two endpoints of line i is at (i, ai) and (i, 0). Find two lines, which together 
//  with x-axis forms a container, such that the container contains the most water.

// Note: You may not slant the container and n is at least 2.

class Solution {
public:
    int maxArea(vector<int>& height) {
        int l = 0, r = height.size() - 1, maxHeight = 0;
        
        while (l < r){
            int h = min(height[l], height[r]);
            int w = r - l;
            maxHeight = max(maxHeight, h * w);
            if (height[l] > height[r]) r--;
            else l++;
        }
        
        return maxHeight;
    }
};