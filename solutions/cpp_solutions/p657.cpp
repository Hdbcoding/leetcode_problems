#include <string>
using namespace std;
// Robot return to origin - Easy

class Solution {
public:
    // O(moves.size())
    // pretty easy
    bool judgeCircle(string moves) {
        if (moves.size() == 0) return true;
        
        int u{0}, d{0}, l{0}, r{0};
        for (char c : moves){
            switch (c){
                case 'U': ++u;
                    break;
                case 'D': ++d;
                    break;
                case 'L': ++l;
                    break;
                case 'R': ++r;
                    break;
            }
        }
        
        return u == d && l == r;
    }
};