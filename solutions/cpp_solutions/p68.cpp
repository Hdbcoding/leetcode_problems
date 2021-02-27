#include <vector>
#include <string>
#include <sstream>

using namespace std;

// Text Justification - Hard

// Given an array of words and a width maxWidth, format the text such that each line has exactly maxWidth characters and is fully (left and right) justified.

// You should pack your words in a greedy approach; that is, pack as many words as you can in each line.
// Pad extra spaces ' ' when necessary so that each line has exactly maxWidth characters.

// Extra spaces between words should be distributed as evenly as possible.
// If the number of spaces on a line do not divide evenly between words, the empty slots on the left will be assigned more spaces than the slots on the right.

// For the last line of text, it should be left justified and no extra space is inserted between words.

// Note:

// A word is defined as a character sequence consisting of non-space characters only.
// Each word's length is guaranteed to be greater than 0 and not exceed maxWidth.
// The input array words contains at least one word.

class Solution
{
public:
    vector<string> fullJustify(vector<string> &words, int maxWidth)
    {
        int start = 0;
        int end = 0;
        vector<string> result;
        int remainingSpace{maxWidth};
        // size of word that would exactly satisfy the remaining space
        // (accounting for spaces between earlier words)
        int maxPossibleWord{maxWidth};
        for (auto &w : words)
        {
            if ((int)w.size() <= maxPossibleWord)
            {
                // if this word fits, add it to the pending row
                ++end;
                remainingSpace -= w.size();
                int minSpaces = end - start;
                maxPossibleWord = remainingSpace - minSpaces;
            }
            else
            {
                // otherwise, process the pending row into the result
                processMidRow(result, words, start, end, remainingSpace);
                start = end++;
                remainingSpace = maxWidth - w.size();
                maxPossibleWord = maxWidth - w.size() - 1;
            }
        }
        // if there is a pending row, process that into the result too
        processLastRow(result, words, start, end, remainingSpace);
        return result;
    }

    void processMidRow(vector<string> &result, vector<string> &words, int start, int end, int remainingSpace)
    {
        // no words - don't add a row
        if (end == start)
            return;
        stringstream ss;
        ss << words[start];
        int length = end - start;
        // one or two words - add first word, then all spaces, then last word
        if (length == 1 || length == 2)
        {
            for (int i = 0; i < remainingSpace; ++i)
                ss << ' ';

            if (length == 2)
                ss << words[start + 1];
        }
        else
        {
            // otherwise, we need to intelligently pack all words
            int normalSpaces = remainingSpace / (length - 1);
            int extraSpaces = remainingSpace % (length - 1);

            for (int i = 0; i < length - 1; ++i)
            {
                for (int i = 0; i < normalSpaces; ++i)
                    ss << ' ';
                if (extraSpaces > 0)
                {
                    ss << ' ';
                    --extraSpaces;
                }
                ss << words[start + i + 1];
            }
        }

        result.push_back(ss.str());
    }

    void processLastRow(vector<string> &result, vector<string> &words, int start, int end, int remainingSpace)
    {
        // no words - don't add a row
        if (end == start)
            return;
        stringstream ss;
        ss << words[start];
        int length = end - start;

        for (int i = start + 1; i < end; ++i)
        {
            ss << ' ' << words[i];
            --remainingSpace;
        }

        for (int i = 0; i < remainingSpace; ++i)
            ss << ' ';

        result.push_back(ss.str());
    }
};