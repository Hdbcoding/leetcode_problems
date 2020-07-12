#include <string>
#include <unordered_map>
using namespace std;

// ZigZag Conversion - Medium

// The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: (you may want to display this pattern in a fixed font for better legibility)

// And then read line by line: "PAHNAPLSIIGYIR"

// Write the code that will take a string and make this conversion given a number of rows:

class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows == 1) return s;
        return convertDirectly(s, numRows);
    }

    string convertDirectly(string &s, int numRows){
        string ret;
        int n = s.size();
        // cycle length is clear from the cycle pattern, say numRows is 5:
        // 1       9 <-- back to start, so 8 steps to get back to start, e.g. 5 * 2 - 2
        // 2     8 10 <- 10 = 2 + 8; 7 = 0 + 8 - 1 
        // 3   7   11 <- 11 = 3 + 8; 6 = 0 + 8 - 2
        // 4 6     12 <- 12 = 4 + 8; 5 = 0 + 8 - 3... next would be 13 = 8 + 8 - 3
        // 5       13
        // first and last row can simply use the cycle length
        // all middle rows get one extra index per cycle
        //
        int cycle = 2 * numRows - 2;
        for (int i = 0; i != numRows; ++i)
        for (int j = 0; j + i < n; j += cycle) {
            ret += s[j + i];
            if (i != 0
                && i != numRows - 1
                && j + cycle - i < n)
                ret += s[j + cycle - i];
        }
        return ret;
    }

    string convertWithMap(string &s, int numRows){
        vector<vector<int>> map(numRows);
        
        // walk through the string, appending the char index to the map for the appropriate row
        int row(0);
        bool down(true);
        for (int i = 0; i != s.size(); ++i){
            map[row].push_back(i);
            if (down) row++;
            else row--;
            
            if (row == -1){
                down = true;
                row = 1;
            } else if (row == numRows){
                row = numRows - 2;
                down = false;
            }
        }
        
        // generate an output string based on the map
        string ret;
        ret.reserve(s.size());
        for (int i = 0; i != numRows; ++i){
            for (int j = 0; j != map[i].size(); ++j){
                ret.push_back(s[map[i][j]]);
            }
        }
        
        return ret;
    }
};