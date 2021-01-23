#include <vector>
using namespace std;
// Toeplitz matrix - Easy

// Given an m x n matrix, return true if the matrix is Toeplitz. Otherwise, return false.

// A matrix is Toeplitz if every diagonal from top-left to bottom-right has the same elements.

class Solution
{
public:
    bool isToeplitzDiagonal(int i, int j, vector<vector<int>> &matrix)
    {
        int v = matrix[i++][j++];
        while (i < matrix.size() && j < matrix[0].size())
        {
            if (matrix[i++][j++] != v)
                return false;
        }
        return true;
    }

    bool isToeplitzMatrix(vector<vector<int>> &matrix)
    {
        for (int i = 0; i < matrix.size(); ++i)
        {
            if (!isToeplitzDiagonal(i, 0, matrix))
                return false;
        }

        for (int i = 1; i < matrix[0].size(); ++i)
        {
            if (!isToeplitzDiagonal(0, i, matrix))
                return false;
        }

        return true;
    }
};