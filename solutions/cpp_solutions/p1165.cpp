#include <string>
using namespace std;
// Single-Row Keyboard

// There is a special keyboard with all keys in a single row.

// Given a string keyboard of length 26 indicating the layout of the keyboard (indexed from 0 to 25),
// initially your finger is at index 0. To type a character, you have to move your finger to the index of the desired character.
// The time taken to move your finger from index i to index j is |i - j|.

// You want to type a string word. Write a function to calculate how much time it takes to type it with one finger.

class Solution
{
public:
    int calculateTime(string keyboard, string word)
    {
        // remember where letters are on the keyboard
        int letterIndex[26];
        for (int i = 0; i < keyboard.size(); ++i)
            letterIndex[keyboard[i] - 'a'] = i;

        // index of my finger
        int sum = 0;
        int idx = 0;
        for (char c : word)
        {
            int dest = letterIndex[c - 'a'];
            sum += abs(dest - idx);
            idx = dest;
        }
        return sum;
    }
};