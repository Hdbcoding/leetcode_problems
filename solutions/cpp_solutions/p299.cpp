#include <string>
#include <unordered_map>
using namespace std;

// Bulls and Cows - Medium

// You are playing the Bulls and Cows game with your friend.

// You write down a secret number and ask your friend to guess what the number is.
// When your friend makes a guess, you provide a hint with the following info:

// The number of "bulls", which are digits in the guess that are in the correct position.
// The number of "cows", which are digits in the guess that are in your secret number but are located in the wrong position.
// Specifically, the non-bull digits in the guess that could be rearranged such that they become bulls.
// Given the secret number secret and your friend's guess guess, return the hint for your friend's guess.

// The hint should be formatted as "xAyB", where x is the number of bulls and y is the number of cows.
// Note that both secret and guess may contain duplicate digits.

class Solution
{
public:
    string getHint(string secret, string guess)
    {
        unordered_map<char, int> secretChars;
        int bulls{0}, cows{0};
        // count bulls, and build map of mismatches
        for (int i = 0; i < guess.size(); ++i)
        {
            if (secret[i] == guess[i])
            {
                ++bulls;
                secret.replace(i, 1, "_");
                guess.replace(i, 1, "_");
            }
            else
            {
                secretChars[secret[i]]++;
            }
        }
        // count cows using the mismatch map
        for (int i = 0; i < guess.size(); ++i)
        {
            if (guess[i] == '_')
                continue;
            auto it = secretChars.find(guess[i]);
            if (it != secretChars.end() && it->second != 0)
            {
                ++cows;
                --it->second;
            }
        }

        return to_string(bulls) + "A" + to_string(cows) + "B";
    }
};