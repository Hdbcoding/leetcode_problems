#include <vector>
#include <queue>
#include <algorithm>
#include <limits>
#include <cmath>

using namespace std;

// Campus Bikes II - Medium

// On a campus represented as a 2D grid, there are N workers and M bikes, with N <= M. Each worker and bike is a 2D coordinate on this grid.

// We assign one unique bike to each worker so that the sum of the Manhattan distances between each worker and their assigned bike is minimized.

// The Manhattan distance between two points p1 and p2 is Manhattan(p1, p2) = |p1.x - p2.x| + |p1.y - p2.y|.

// Return the minimum possible sum of Manhattan distances between each worker and their assigned bike.

// Constraints:

// N == workers.length
// M == bikes.length
// 1 <= N <= M <= 10
// workers[i].length == 2
// bikes[i].length == 2
// 0 <= workers[i][0], workers[i][1], bikes[i][0], bikes[i][1] < 1000
// All the workers and the bikes locations are unique.

typedef pair<int, int> pi;
typedef priority_queue<pi, vector<pi>, greater<pi>> dist_queue;
typedef vector<dist_queue> dist_map;
class Solution
{
public:
    int assignBikes(vector<vector<int>> &workers, vector<vector<int>> &bikes)
    {
        return topdown(workers, bikes);
    }

    // top-down memoization + pruning doesn't work because I still need to know the results of the later smaller subproblems to calculate later subproblems
    // pruning by pushing a variable down like this would cause me to miss out on real solutions later
    int topdown_prune(vector<vector<int>> &workers, vector<vector<int>> &bikes)
    {
        minOverall = numeric_limits<int>::max();
        int maxBits = pow(2, bikes.size());
        vector<vector<int>> memo(workers.size(), vector<int>(maxBits, -1));
        return topdown_prune_inner(workers, bikes, 0, 0, 0, memo);
    }

    int topdown_prune_inner(vector<vector<int>> &workers, vector<vector<int>> &bikes, int workerI, int bikeBits, int sum, vector<vector<int>> &memo)
    {
        if (workerI == workers.size())
        {
            minOverall = min(minOverall, sum);
            return 0;
        }

        if (minOverall < sum)
            return numeric_limits<int>::max();

        if (memo[workerI][bikeBits] == -1)
        {
            int minValue = numeric_limits<int>::max();
            for (int i = 0; i < bikes.size(); ++i)
            {
                int flag = 1 << i;
                // skip if already using this worker
                if (bikeBits & flag)
                    continue;

                int dist = distance(workers[workerI], bikes[i]);

                // if I haven't used this bike yet, try using them
                bikeBits |= flag;
                int rest = topdown_prune_inner(workers, bikes, workerI + 1, bikeBits, sum + dist, memo);
                // unuse this bike so the next worker can use them
                bikeBits ^= flag;

                if (rest != numeric_limits<int>::max())
                    minValue = min(minValue, rest + dist);
            }
            memo[workerI][bikeBits] = minValue;
        }

        return memo[workerI][bikeBits];
    }

    int topdown(vector<vector<int>> &workers, vector<vector<int>> &bikes)
    {
        int maxBits = pow(2, bikes.size());
        vector<vector<int>> memo(workers.size(), vector<int>(maxBits, -1));
        return topdownInner(workers, bikes, 0, 0, memo);
    }

    int topdownInner(vector<vector<int>> &workers, vector<vector<int>> &bikes, int workerI, int bikeBits, vector<vector<int>> &memo)
    {
        if (workerI == workers.size())
            return 0;

        if (memo[workerI][bikeBits] == -1)
        {
            int minValue = numeric_limits<int>::max();
            for (int i = 0; i < bikes.size(); ++i)
            {
                int flag = 1 << i;
                // skip if already using this worker
                if (bikeBits & flag)
                    continue;

                // if I haven't used this bike yet, try using them
                bikeBits |= flag;
                int rest = topdownInner(workers, bikes, workerI + 1, bikeBits, memo);
                // unuse this bike so the next worker can use them
                bikeBits ^= flag;

                if (rest != numeric_limits<int>::max())
                    minValue = min(minValue, rest + distance(workers[workerI], bikes[i]));
            }
            memo[workerI][bikeBits] = minValue;
        }

        return memo[workerI][bikeBits];
    }

    int minOverall;
    int prune(vector<vector<int>> &workers, vector<vector<int>> &bikes)
    {
        minOverall = numeric_limits<int>::max();
        return pruneInner(workers, bikes, 0, 0, 0);
    }

    int pruneInner(vector<vector<int>> &workers, vector<vector<int>> &bikes, int workerI, int bikeBits, int sum)
    {
        if (workerI == workers.size())
        {
            minOverall = min(minOverall, sum);
            return 0;
        }

        if (minOverall < sum)
            return numeric_limits<int>::max();

        int minValue = numeric_limits<int>::max();
        for (int i = 0; i < bikes.size(); ++i)
        {
            int flag = 1 << i;
            // skip if already using this worker
            if (bikeBits & flag)
                continue;

            int dist = distance(workers[workerI], bikes[i]);

            // if I haven't used this bike yet, try using them
            bikeBits |= flag;
            int rest = pruneInner(workers, bikes, workerI + 1, bikeBits, sum + dist);
            // unuse this bike so the next worker can use them
            bikeBits ^= flag;

            if (rest != numeric_limits<int>::max())
                minValue = min(minValue, rest + dist);
        }
        return minValue;
    }

    // naive recursive solution - try every possible combination
    int naive(vector<vector<int>> &workers, vector<vector<int>> &bikes)
    {
        return naiveInner(workers, bikes, 0, 0);
    }

    int naiveInner(vector<vector<int>> &workers, vector<vector<int>> &bikes, int workerI, int bikeBits)
    {
        if (workerI == workers.size())
            return 0;

        int minValue = numeric_limits<int>::max();
        for (int i = 0; i < bikes.size(); ++i)
        {
            int flag = 1 << i;
            // skip if already using this worker
            if (bikeBits & flag)
                continue;

            // if I haven't used this bike yet, try using them
            bikeBits |= flag;
            int rest = naiveInner(workers, bikes, workerI + 1, bikeBits);
            // unuse this bike so the next worker can use them
            bikeBits ^= flag;

            if (rest != numeric_limits<int>::max())
                minValue = min(minValue, rest + distance(workers[workerI], bikes[i]));
        }
        return minValue;
    }

    // a greedy solution doesn't even work here
    int greedy(vector<vector<int>> &workers, vector<vector<int>> &bikes)
    {
        int n = workers.size();
        int m = bikes.size();

        vector<vector<int>> allDist(n, vector<int>(m, 0));
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                allDist[i][j] = distance(workers[i], bikes[j]);
            }
        }

        dist_map workerDistances(n, dist_queue());
        for (int i = 0; i < n; ++i)
        {
            int best = numeric_limits<int>::max();
            int bestj = -1;
            for (int j = 0; j < m; ++j)
            {
                int dist = allDist[i][j];
                workerDistances[i].push({dist, j});
            }
        }

        dist_map bikeDistances(m, dist_queue());
        for (int j = 0; j < m; ++j)
        {
            int best = numeric_limits<int>::max();
            int bestj = -1;
            for (int i = 0; i < n; ++i)
            {
                int dist = allDist[i][j];
                bikeDistances[j].push({dist, i});
            }
        }

        vector<bool> assignedWorkers(n, false);
        vector<bool> assignedBikes(m, false);

        // // skip the worst bikes
        // if (m > n)
        // {
        //     dist_queue worstBikes;
        //     for (int j = 0; j < m; ++j)
        //     {
        //         // skip bike furthest from the group overall
        //         // int sum = 0;
        //         // for (int i = 0; i < n; ++i)
        //         //     sum += allDist[i][j];
        //         // worstBikes.push({sum, j});

        //         // skip the bike furthest from its closest rider
        //         worstBikes.push({bikeDistances[j].top().first, j});
        //     }

        //     for (int i = 0; i < m - n; ++i)
        //     {
        //         assignedBikes[worstBikes.top().second] = true;
        //         worstBikes.pop();
        //     }
        // }

        int totalDistance = 0;

        for (int i = 0; i < workers.size(); ++i)
        {
            int worstWorkerDist = 0;
            int ww{-1}, wb{-1};

            for (int j = 0; j < n; ++j)
            {
                if (assignedWorkers[j])
                    continue;

                dist_queue &q = workerDistances[j];
                while (q.size() > 0 && assignedBikes[q.top().second])
                    q.pop();

                if (q.size() > 0 && q.top().first > worstWorkerDist)
                {
                    worstWorkerDist = q.top().first;
                    ww = j;
                    wb = q.top().second;
                }
            }

            int worstBikeDist = 0;
            int bw{-1}, bb{-1};
            for (int j = 0; j < m; ++j)
            {
                if (assignedBikes[j])
                    continue;

                dist_queue &q = bikeDistances[j];
                while (q.size() > 0 && assignedWorkers[q.top().second])
                    q.pop();

                if (q.size() > 0 && q.top().first > worstBikeDist)
                {
                    worstBikeDist = q.top().first;
                    bb = j;
                    bw = q.top().second;
                }
            }

            if (worstWorkerDist > worstBikeDist)
            {
                assignedWorkers[ww] = true;
                assignedBikes[wb] = true;
                totalDistance += worstWorkerDist;
            }
            else
            {
                assignedWorkers[bw] = true;
                assignedBikes[bb] = true;
                totalDistance += worstBikeDist;
            }
        }

        return totalDistance;
    }

    int distance(vector<int> &from, vector<int> &to)
    {
        return abs(from[0] - to[0]) + abs(from[1] - to[1]);
    }
};