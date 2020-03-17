public class p79 {
    // Word Search - Medium

    // Given a 2D board and a word, find if the word exists in the grid.

    // The word can be constructed from letters of sequentially adjacent cell, where
    // "adjacent" cells are those horizontally or vertically neighboring. The same
    // letter cell may not be used more than once.

    public static void main(String[] args) {
        new Solution().exist(new char[][] { { 'A', 'B', 'C', 'E' }, { 'S', 'F', 'C', 'S' }, { 'A', 'D', 'E', 'E' } },
                "ABCB");
        new Solution().exist(
                new char[][] { 
            { 'A', 'B', 'C', 'E' }, 
            { 'S', 'F', 'C', 'S' }, 
            { 'A', 'D', 'E', 'E' } },
                "ABCCED");
    }

    static class Solution {
        public boolean exist(char[][] board, String word) {
            return dfs(board, word);
        }
        
        boolean dfs(char[][] board, String word){
            for (int i = 0; i < board.length; i++)
            for (int j = 0; j < board[0].length; j++) {
                if (dfsExplore(board, word, i, j, 0)) 
                    return true;
            }
            return false;
        }
        
        boolean dfsExplore(char[][] board, String word, int i, int j, int index){
            if (index == word.length()) return true;
            
            if (i < 0 || j < 0 
                || i == board.length 
                || j == board[0].length) return false;
    
            if (word.charAt(index) != board[i][j])
                return false;
            
            boolean found = false;
            board[i][j] = '*';
    
            for (int d = 0; d < 4; d++){
                int i2 = i + directions[d][0];
                int j2 = j + directions[d][1];
                found = dfsExplore(board, word, i2, j2, index + 1);
                if (found) break;
            }
            
            board[i][j] = word.charAt(index);
            return found;
        }
        
        int[][] directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    }
}