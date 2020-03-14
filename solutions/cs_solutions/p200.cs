using System.Linq;
public class p200
{
    // Given a 2d grid map of '1's (land) and '0's (water), count the number of 
    //  islands. An island is surrounded by water and is formed by connecting 
    //  adjacent lands horizontally or vertically. You may assume all four edges 
    //  of the grid are all surrounded by water.
    public class Solution
    {
        public int NumIslands(char[,] grid)
        {
            Width = grid.GetLength(0);
            Height = grid.GetLength(1);
            return DFS(grid);
        }

        private char[,] DFSGrid;

        private int DFS(char[,] grid)
        {
            DFSGrid = grid.Clone() as char[,];
            var count = 0;
            for (int i = 0; i < Width; i++)
            {
                for (int j = 0; j < Height; j++)
                {
                    if (DFSGrid[i, j] == '1')
                    {
                        DFSClearIsland(i, j);
                        count++;
                    }
                }
            }
            return count;
        }

        //possible O(WxH) space usage for stack management
        //possible O(WxH) time usage for clearing the board
        private void DFSClearIsland(int i, int j)
        {
            //Console.WriteLine($"Clearing out {i},{j}");
            DFSGrid[i, j] = 'X';
            if (i > 0 && DFSGrid[i - 1, j] == '1') DFSClearIsland(i - 1, j);
            if (i < Width - 1 && DFSGrid[i + 1, j] == '1') DFSClearIsland(i + 1, j);
            if (j > 0 && DFSGrid[i, j - 1] == '1') DFSClearIsland(i, j - 1);
            if (j < Height - 1 && DFSGrid[i, j + 1] == '1') DFSClearIsland(i, j + 1);
        }

        private int BruteForce(char[,] grid)
        {
            var clusters = new List<Cluster>();

            for (int i = 0; i < Width; i++)
            {
                for (int j = 0; j < Height; j++)
                {
                    if (grid[i, j] == '1')
                    {
                        //Console.WriteLine($"found land at {i},{j}");
                        var coord = new Coord(i, j);
                        var match = clusters.Where(n => n.Neighbors(coord)).ToList();
                        var count = match.Count();
                        if (count == 0)
                        {
                            //Console.WriteLine("--no neighboring clusters");
                            var cluster = new Cluster();
                            cluster.Add(coord);
                            clusters.Add(cluster);
                        }
                        else if (count == 1)
                        {
                            //Console.WriteLine("--one neighboring clusters");
                            var cluster = match.Single();
                            cluster.Add(coord);
                        }
                        else
                        {
                            //Console.WriteLine($"--{count} neighboring clusters");
                            var first = match.First();
                            first.Add(coord);
                            match.Remove(first);
                            match.ForEach(n =>
                            {
                                first.Merge(n);
                                clusters.Remove(n);
                            });
                        }
                    }
                }
            }

            return clusters.Count;
        }

        private static int Width { get; set; }
        private static int Height { get; set; }

        private class Cluster
        {
            public List<Coord> Coordinates { get; set; } = new List<Coord>();

            public void Add(Coord c) { Coordinates.Add(c); }

            public void Merge(Cluster other)
            {
                //Console.WriteLine($"----trying to merge... {Coordinates.Count} nodes with {other.Coordinates.Count}");
                Coordinates.AddRange(other.Coordinates);
                //Console.WriteLine($"----now I have {Coordinates.Count} coordinates");
            }

            public bool Neighbors(Coord other)
            {
                return Coordinates.Any(n => n.IsNeighborOf(other));
            }
        }

        private struct Coord
        {
            public int X { get; set; }
            public int Y { get; set; }

            public bool IsNeighborOf(Coord other)
            {
                if (X == other.X && (Y == other.Y + 1 || Y == other.Y - 1))
                {
                    //Console.WriteLine($"----{X},{Y} borders {other.X},{other.Y}");
                    return true;
                }
                if (Y == other.Y && (X == other.X + 1 || X == other.X - 1))
                {
                    //Console.WriteLine($"----{X},{Y} borders {other.X},{other.Y}");
                    return true;
                }
                //Console.WriteLine($"----{X},{Y} doesn't border {other.X},{other.Y}");
                return false;
            }

            public Coord(int x, int y) { X = x; Y = y; }
        }
    }
}