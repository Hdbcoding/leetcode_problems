#include <unordered_map>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

// Alphabet Board Path - Medium

// On an alphabet board, we start at position (0, 0), corresponding to character board[0][0].

// Here, board = ["abcde", "fghij", "klmno", "pqrst", "uvwxy", "z"], as shown in the diagram below.

// We may make the following moves:

// 'U' moves our position up one row, if the position exists on the board;
// 'D' moves our position down one row, if the position exists on the board;
// 'L' moves our position left one column, if the position exists on the board;
// 'R' moves our position right one column, if the position exists on the board;
// '!' adds the character board[r][c] at our current position (r, c) to the answer.
// (Here, the only positions that exist on the board are positions with letters on them.)

// Return a sequence of moves that makes our answer equal to target in the minimum number of moves.  You may return any path that does so.

struct pair_hash{
    template<class t1, class t2>
    size_t operator () (const pair<t1,t2> &p) const {
        auto h1 = hash<t1>{}(p.first);
        auto h2 = hash<t2>{}(p.second);
        return h1 ^ h2;
    }
};

class Solution {
    
    void buildMaps(unordered_map<char, pair<int,int>> &charMap, unordered_map<pair<int,int>, char, pair_hash> &posMap){
        vector<string> board = {
            "abcde", 
            "fghij", 
            "klmno", 
            "pqrst", 
            "uvwxy", 
            "z"
        };
        
        for (int i = 0; i < board.size(); ++i){
            for (int j = 0; j < board[i].size(); ++j){
                pair<int,int> pos = {i, j};
                char c = board[i][j];
                charMap[c] = pos;
                posMap[pos] = c;
            }
        }
    }
    
public:
    string alphabetBoardPath(string target) {
        stringstream ss;
        unordered_map<char, pair<int,int>> charMap{};
        unordered_map<pair<int,int>, char, pair_hash> posMap{};
        
        buildMaps(charMap, posMap);
        
        pair<int,int> pos = {0,0};
        for (int i = 0; i < target.size(); ++i) {
            pair<int,int> p2 = charMap[target[i]];
            char startingAt = posMap[pos];
            
            // special cases at 'z'
            // both at z, just add a ! and skip
            if (target[i] == 'z' && startingAt == 'z')
            {
                ss << '!';
                continue;
            } 
            // only target at z, move all the way left and rewrite pos
            if (target[i] == 'z')
            {
                for (int j = 0; j < pos.second; ++j)
                    ss << 'L';
                pos = {pos.first, 0};
            }
            // if starting at z, move up one and rewrite pos
            if (startingAt == 'z'){
                ss << 'U';
                pos = {4, 0};
            }
            
            for (int j = 0; j < p2.first - pos.first; ++j)
                ss << 'D';
            for (int j = 0; j < pos.first - p2.first; ++j)
                ss << 'U';
            for (int j = 0; j < p2.second - pos.second; ++j)
                ss << 'R';
            for (int j = 0; j < pos.second - p2.second; ++j)
                ss << 'L';
            ss << '!';
            pos = p2;
        }
        
        
        return ss.str();
    }
};