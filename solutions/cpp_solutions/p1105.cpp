#include <vector>
using namespace std;

// Filling Bookcase Shelves - Medium

// We have a sequence of books: the i-th book has thickness books[i][0] and height books[i][1].

// We want to place these books in order onto bookcase shelves that have total width shelf_width.

// We choose some of the books to place on this shelf (such that the sum of their thickness is <= shelf_width), 
// then build another level of shelf of the bookcase so that the total height of the bookcase has increased by 
// the maximum height of the books we just put down.  
// We repeat this process until there are no more books to place.

// Note again that at each step of the above process, the order of the books we place is the same order 
// as the given sequence of books.  For example, if we have an ordered list of 5 books, we might place the 
// first and second book onto the first shelf, the third book on the second shelf, and the fourth and fifth 
// book on the last shelf.

// Return the minimum possible height that the total bookshelf can be after placing shelves in this manner.

class Solution {
public:
    int minHeightShelves(vector<vector<int>>& books, int shelf_width) {
        vector<int> dp(books.size() + 1, 0);
        dp[0] = 0;
        
        // consider each book
        for (int i = 1; i <= books.size(); ++i){
            int w = books[i - 1][0];
            int h = books[i - 1][1];
            // pretend we started a new row with this book
            dp[i] = dp[i - 1] + h;
            
            // for each book before this one, what if we grouped it into this row instead?
            for (int j = i - 1; j > 0 && w + books[j - 1][0] <= shelf_width; --j){
                // the height of this row may increase if that book is taller
                h = max(h, books[j - 1][1]);
                w += books[j - 1][0];
                // but we might save height if it makes the overall shelf shorter
                dp[i] = min(dp[i], dp[j - 1] + h);
            }
        }
        
        return dp[books.size()];
    }
};