#include <vector>
#include <queue>
using namespace std;
// Find valid matrix given row and column sums

// You are given two arrays rowSum and colSum of non-negative integers where rowSum[i] is the sum of the elements in the ith row and colSum[j] is the sum of the elements of the jth column of a 2D matrix.
// In other words, you do not know the elements of the matrix, but you do know the sums of each row and column.

// Find any matrix of non-negative integers of size rowSum.length x colSum.length that satisfies the rowSum and colSum requirements.

// Return a 2D array representing any matrix that fulfills the requirements. It's guaranteed that at least one matrix that fulfills the requirements exists.

class Solution
{
public:
    vector<vector<int>> restoreMatrix(vector<int> &rowSum, vector<int> &colSum)
    {
        vector<vector<int>> result(rowSum.size(), vector(colSum.size(), 0));

        priority_queue<pair<int, int>> nextRow, nextCol;
        for (int i = 0; i < rowSum.size(); ++i)
            nextRow.push({rowSum[i], i});
        for (int i = 0; i < colSum.size(); ++i)
            nextCol.push({colSum[i], i});

        while (nextRow.top().first > 0)
        {
            // greedily pick the next row and the next col with the greatest sum
            auto row = nextRow.top();
            auto col = nextCol.top();

            // fill that m[row][col] as much as possible
            int v = min(row.first, col.first);
            result[row.second][col.second] = v;

            // reset the value for that row/col with the remaining sum
            nextRow.push({row.first - v, row.second});
            nextCol.push({col.first - v, col.second});
            nextRow.pop();
            nextCol.pop();
        }

        return result;
    }
};