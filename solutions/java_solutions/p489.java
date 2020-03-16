
import java.util.HashSet;

public class p489 {
    // Robot Room Cleaner - Hard

    // Given a robot cleaner in a room modeled as a grid.

    // Each cell in the grid can be empty or blocked.

    // The robot cleaner with 4 given APIs can move forward, turn left or turn
    // right. Each turn it made is 90 degrees.

    // When it tries to move into a blocked cell, its bumper sensor detects the
    // obstacle and it stays on the current cell.

    class Solution {
        HashSet<Coord> cleaned = new HashSet<>();
        int[][] directionCoords = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
        Robot r;
        
        public void cleanRoom(Robot robot) {
            this.r = robot;
            Coord c = new Coord(0, 0);
            dfs(c, 0);
        }
        
        void dfs(Coord c, int d){
            r.clean();
            cleaned.add(c);
            
            for (int i = 0; i < 4; i++){
                // 0 -> 0,1,2,3
                // 1 -> 1,2,3,0
                // etc.
                int newd = (d + i) % 4;
                Coord newC = new Coord(
                    c.x + directionCoords[newd][0], 
                    c.y + directionCoords[newd][1]);
                
                if (!cleaned.contains(newC) && r.move()){
                    dfs(newC, newd);
                    backUp();
                }
                r.turnRight();
            }
        }
        
        void backUp(){
            r.turnRight();
            r.turnRight();
            r.move();
            r.turnRight();
            r.turnRight();
        }
        
        class Coord {
            int x;
            int y;
            
            Coord(int x, int y){
                this.x = x;
                this.y = y;
            }
            
            @Override
            public int hashCode(){
                int hash = 23;
                hash = hash * 37 + x;
                hash = hash * 37 + y;
                return hash;
            }
            
            @Override 
            public boolean equals(Object o){
                Coord c = (Coord)o;
                return x == c.x && y == c.y;
            }
        }
    }

    interface Robot {
        // returns true if next cell is open and robot moves into the cell.
        // returns false if next cell is obstacle and robot stays on the current cell.
        boolean move();
      
        // Robot will stay on the same cell after calling turnLeft/turnRight.
        // Each turn will be 90 degrees.
        void turnLeft();
        void turnRight();
      
        // Clean the current cell.
        void clean();
      }
}