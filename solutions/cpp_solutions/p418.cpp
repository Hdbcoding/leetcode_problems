#include <vector>
#include <string>

using namespace std;

// Sentence Screen Fitting - Medium

// Given a rows x cols screen and a sentence represented by a list of non-empty words, find how many times the given sentence can be fitted on the screen.

// Note:
// A word cannot be split into two lines.
// The order of words in the sentence must remain unchanged.
// Two consecutive words in a line must be separated by a single space.
// Total words in the sentence won't exceed 100.
// Length of each word is greater than 0 and won't exceed 10.
// 1 ≤ rows, cols ≤ 20,000.

class Solution
{
public:
    int wordsTyping(vector<string> &sentence, int rows, int cols)
    {
        for (auto &word : sentence)
            if (word.size() > cols)
                return 0;

        // repeating a sentence is going to result in a rotating period
        // "sometimes I go on a walk" in 20 char
        //  9 1 2 2 1 4 -> 19 chars total, 6 words,
        //  24 char to fit on a line with spaces
        //  ____________________
        //  sometimes I go on a
        //  walk sometimes I go <- offset by 5 char
        //  on a walk sometimes <- offset by 5 char
        //  I go on a walk <- offset by 5 char
        //  sometimes I go on a  <-- Repeat!
        //  4 line grouping, 3 repeats per 4 lines
        //  if rows % 4 == 0, return 3 * rows / 4
        //  otherwise, calculate remainder

        //  sometimes1 sometimes2 sometimes3 -> 32 char
        //  ____________________++++++++++++
        //  sometimes1
        //  sometimes2           <- offset by 11 char
        //  sometimes3           <- offset by 11 char

        int cycleHeight = 0;
        int count = 0;
        int wordI = 0;
        int colsLeft = cols;
        int rowsLeft = rows;
        colsLeft = cols;
        while (rowsLeft > 0)
        {
            // we have finished a full rotation, and calculated the cycle height
            if (wordI == 0 && count > 0 && colsLeft == cols)
            {
                break;
            }

            int wordSize = sentence[wordI].size();
            if (wordSize <= colsLeft)
            {
                // if there is room for this word, add this word to the current line
                // always take room for the space
                colsLeft -= wordSize + 1;
                ++wordI;

                // if we got to the end of the sentence, go back to the beginning of the sentence
                if (wordI == sentence.size())
                {
                    wordI = 0;
                    ++count;
                }
            }
            else
            {
                // if there is not room for this word, go to the next line and reset the amount of available space
                --rowsLeft;
                ++cycleHeight;
                colsLeft = cols;
            }
        }

        if (rowsLeft >= cycleHeight)
        {
            int totalCyclesLeft = rowsLeft / cycleHeight;
            rowsLeft -= totalCyclesLeft * cycleHeight;
            count += totalCyclesLeft * count;
        }

        while (rowsLeft > 0)
        {
            int wordSize = sentence[wordI].size();
            if (wordSize <= colsLeft)
            {
                // if there is room for this word, add this word to the current line
                // always take room for the space
                colsLeft -= wordSize + 1;
                ++wordI;

                // if we got to the end of the sentence, go back to the beginning of the sentence
                if (wordI == sentence.size())
                {
                    wordI = 0;
                    ++count;
                }
            }
            else
            {
                // if there is not room for this word, go to the next line and reset the amount of available space
                --rowsLeft;
                ++cycleHeight;
                colsLeft = cols;
            }
        }

        return count;
    }
};