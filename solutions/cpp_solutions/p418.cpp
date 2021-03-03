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
        return skipWordsFaster(sentence, rows, cols);
    }

private:
    int skipWordsFaster(vector<string> &sentence, int rows, int cols)
    {
        vector<int> wordCount(sentence.size(), 0);
        fillWordCounts(sentence, wordCount, cols);

        int totalWords = 0;
        int cycleHeight = 0;
        int wordI = 0;
        int row = 0;
        for (; row < rows; ++row)
        {
            // we have now calculated the cycle height
            if (row > 0 && wordI == 0)
                break;
            
            // we can only get this condition if a word doesn't fit on a whole row, so we can stop processing
            if (wordCount[wordI] == 0) 
                return 0;
            
            totalWords += wordCount[wordI];
            wordI = (wordI + wordCount[wordI]) % sentence.size();
            ++cycleHeight;
        }

        if (rows - row > cycleHeight)
        {
            int totalCyclesLeft = (rows - row) / cycleHeight;
            row += totalCyclesLeft * cycleHeight;
            totalWords += totalCyclesLeft * totalWords;
        }

        for (; row < rows; ++row)
        {            
            totalWords += wordCount[wordI];
            wordI = (wordI + wordCount[wordI]) % sentence.size();
        }

        return totalWords / sentence.size();
    }
    int skipWords(vector<string> &sentence, int rows, int cols)
    {
        // whenever a line starts with a word, we will be able to fit a certain nummber of words on the line
        // so, we don't need to loop through every word as we fill the screen
        // we can jump to the next line on the correct next word
        vector<int> wordCount(sentence.size(), 0);
        fillWordCounts(sentence, wordCount, cols);

        int totalWords = 0;
        int wordI = 0;
        for (int i = 0; i < rows; ++i)
        {
            if (wordCount[wordI] == 0) 
                return 0;
            totalWords += wordCount[wordI];
            wordI = (wordI + wordCount[wordI]) % sentence.size();
        }
        return totalWords / sentence.size();
    }

    void fillWordCounts(vector<string> &sentence, vector<int> &wordCount, int cols)
    {
        for (size_t i = 0; i < sentence.size(); ++i)
        {
            if (sentence[i].size() > cols)
                continue;

            int width = sentence[i].size();
            int count = 1;
            int j = (i + 1) % sentence.size();
            while (true)
            {
                int wordSize = sentence[j].size();
                width += 1 + wordSize;
                if (width > cols)
                    break;
                ++count;
                j = (j + 1) % sentence.size();
            }

            wordCount[i] = count;
        }
    }

    // this solution is incredibly slow, taking about 1500ms
    int naive(vector<string> &sentence, int rows, int cols)
    {
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
                break;

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
                // if a word is longer than the width of the screen, we can't fit this sentence at all
                if (colsLeft == cols)
                    return 0;
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
                // if a word is longer than the width of the screen, we can't fit this sentence at all
                if (colsLeft == cols)
                    return 0;
                // if there is not room for this word, go to the next line and reset the amount of available space
                --rowsLeft;
                ++cycleHeight;
                colsLeft = cols;
            }
        }

        return count;
    }
};