#include <string>
#include <sstream>

using namespace std;

// Rearrange spaces between words - Easy

// You are given a string text of words that are placed among some number of spaces. 
// Each word consists of one or more lowercase English letters and are separated by at least one space. 
// It's guaranteed that text contains at least one word.

// Rearrange the spaces so that there is an equal number of spaces between every pair of adjacent words and that number is maximized. 
// If you cannot redistribute all the spaces equally, place the extra spaces at the end, meaning the returned string should be the same length as text.

// Return the string after rearranging the spaces.

class Solution
{
public:
    string reorderSpaces(string text)
    {
        int spaces{0};
        int words{0};
        bool inWord{false};
        for (char c : text)
        {
            bool isSpace = c == ' ';
            if (isSpace)
                ++spaces;
            // (inWord && !isSpace) || (!inWord && isSpace)
            // count through while sets of spaces or sets of letters
            if (inWord != isSpace)
                continue;

            if (isSpace)
            {
                // we have just ended a word, so increment word count
                inWord = false;
                ++words;
            }
            else
            {
                // we have just entered a word, so flip inWord
                inWord = true;
            }
        }
        // if we ended on a letter, make sure to count the last word
        if (inWord)
            ++words;
        if (spaces == 0)
            return text;

        // want to evenly disperse spaces between words
        // so words-1 groups of spaces
        // all groups have an even number of spaces, all of the remainder goes to the last space
        int spaceGroups = words - 1;
        int spacesPerGroup = spaceGroups == 0 ? 0 : spaces / spaceGroups;
        int extraAtEnd = spaceGroups == 0 ? spaces : spaces % spaceGroups;
        // loop through the text, now populating a stringstream
        // after we get to the end of a word, fill in a spaceGroup
        // at the last space group, fill in extraAtEnd
        inWord = false;
        stringstream ss;
        for (char c : text)
        {
            bool isSpace = c == ' ';
            if (inWord != isSpace)
            {
                // if we're in a word, fill out the stringstream
                if (inWord)
                    ss << c;
                continue;
            }
            if (isSpace)
            {
                // we have just ended a word, so now add our spaces
                inWord = false;
                --spaceGroups;
                if (spaceGroups >= 0)
                    addSpaces(ss, spacesPerGroup);
            }
            else
            {
                // we just entered a word
                inWord = true;
                ss << c;
            }
        }
        addSpaces(ss, extraAtEnd);
        return ss.str();
    }

    void addSpaces(stringstream &ss, int spaces)
    {
        for (int i = 0; i < spaces; ++i)
            ss << ' ';
    }
};