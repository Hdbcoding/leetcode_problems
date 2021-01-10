#include <vector>
using namespace std;

// Longest Increasing Path in a Matrix - Hard

// Given an m x n matrix, return the length of the longest increasing path in matrix.

// From each cell, you can either move in four directions: left, right, up, or down. 
// You may not move diagonally or move outside the boundary (i.e., wrap-around is not allowed).

class Solution {
public:
    vector<vector<int>> seen;
    
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        seen.resize(matrix.size());
        for (int i = 0; i < matrix.size(); ++i){
            seen[i] = vector<int>();
            seen[i].assign(matrix[i].size(), -1);
        }
        
        for (int i = 0; i < matrix.size(); ++i){
            for (int j = 0; j < matrix[i].size(); ++j){
                dfs(matrix, i, j);
            }
        }
        
        int maxLength = 1;
        for (int i = 0; i < seen.size(); ++i){
            for (int j = 0; j < seen[i].size(); ++j){
                maxLength = max(maxLength, seen[i][j]);
            }
        }
        
        return maxLength;
    }
    
    int dfs(vector<vector<int>>& matrix, int i, int j){        
        // already explored
        if (seen[i][j] != -1) return seen[i][j];
        
        seen[i][j] = 1;
        
        int up{0}, left{0}, right{0}, down{0};
        
        if (i >= 1 && matrix[i - 1][j] > matrix[i][j])
            up = dfs(matrix, i - 1, j);
        if (j >= 1 && matrix[i][j-1] > matrix[i][j])
            left = dfs(matrix, i, j - 1);
        if (i < matrix.size() - 1 && matrix[i+1][j] > matrix[i][j])
            down = dfs(matrix, i + 1, j);
        if (j < matrix[i].size() - 1 && matrix[i][j+1] > matrix[i][j])
            right = dfs(matrix, i, j + 1);
        
        seen[i][j] += max(up, max(left, max(right, down)));
        return seen[i][j];
    }
};