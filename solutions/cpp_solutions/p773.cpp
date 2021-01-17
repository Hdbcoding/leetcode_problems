#include <vector>
#include <string>
#include <sstream>
#include <queue>
#include <unordered_set>
#include <iostream>
using namespace std;

// Sliding Puzzle - Hard

class Solution {
    struct move{
        vector<vector<int>> board{{0, 1, 2},{3, 4, 5}};
        string boardState;
        int row;
        int col;
        int depth;
        
        move(vector<vector<int>>& board, int row, int col, int depth){
            for (int i = 0; i < board.size(); ++i)
                for (int j = 0; j < board[0].size(); ++j)
                    this->board[i][j] = board[i][j];
            
            this->row = row;
            this->col = col;
            this->depth = depth;
            this->boardState = stringify(this->board);
        }
    
        string stringify(vector<vector<int>>& board){
            stringstream ss;
            for (int i = 0; i < board.size(); ++i)
                for (int j = 0; j < board[i].size(); ++j)
                    ss << board[i][j];
            return ss.str();
        }
    };
    
public:
    int slidingPuzzle(vector<vector<int>>& board) {
        int startRow{0}, startColumn{0};
        for (startRow = 0; startRow < board.size(); startRow++){
            for (startColumn = 0; startColumn < board[0].size(); startColumn++){
                if (board[startRow][startColumn] == 0) goto foundZero;
            }
        }
        foundZero:
        
        move start = {board, startRow, startColumn, 0};
        queue<move> toVisit;
        toVisit.push(start);
        
        // seen board states
        unordered_set<string> seen_states;
        seen_states.insert(start.boardState);
        
        int directions[4][2] = {
            // down
            {1, 0},
            // up
            {-1, 0}, 
            // left
            {0, 1}, 
            // right
            {0, -1}
        };
        
        string target = "123450";
        int result = -1;
        while (!toVisit.empty()){
            move here = toVisit.front();
            toVisit.pop();

            // cout << "Exploring board state: " << here.boardState << endl;

            if (here.boardState.compare(target) == 0){
                result = here.depth;
                break;
            }
            
            for (int i = 0; i < 4; i++){
                int row = here.row + directions[i][0];
                int col = here.col + directions[i][1];
                if (row < 0 || col < 0 || row > 1 || col > 2)
                    continue;
                
                vector<vector<int>> newboard
                {
                    { here.board[0][0], here.board[0][1], here.board[0][2] },
                    { here.board[1][0], here.board[1][1], here.board[1][2] } 
                };
                
                newboard[here.row][here.col] = newboard[row][col];
                newboard[row][col] = 0;
                
                move next = { newboard, row, col, here.depth + 1 };
                // if we haven't seen this board state before
                if (seen_states.find(next.boardState) == seen_states.end()){
                    // explore it later
                    toVisit.push(next);
                    seen_states.insert(next.boardState);
                    // cout << "\tadding board state to visit: " << next.boardState << "; toVisit size: " << toVisit.size() << endl;
                }
            }
        }
        
        return result;
    }
};

int main(){
    Solution s;
    vector<vector<int>> board{{1, 2, 3}, {4, 0, 5}};
    cout << s.slidingPuzzle(board) << endl;
}