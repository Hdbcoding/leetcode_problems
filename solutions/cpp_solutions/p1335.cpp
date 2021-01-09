#include <vector>
#include <numeric>
#include <limits>
#include <unordered_map>
#include <stack>
using namespace std;

// Minimum Difficulty of a Job Schedule - Hard

// You want to schedule a list of jobs in d days.
// Jobs are dependent (i.e To work on the i-th job, you have to finish all the jobs j where 0 <= j < i).

// You have to finish at least one task every day.
// The difficulty of a job schedule is the sum of difficulties of each day of the d days.
// The difficulty of a day is the maximum difficulty of a job done in that day.

// Given an array of integers jobDifficulty and an integer d.
// The difficulty of the i-th job is jobDifficulty[i].

// Return the minimum difficulty of a job schedule.
// If you cannot find a schedule for the jobs return -1.

// Input: jobDifficulty = [6,5,4,3,2,1], d = 2
// Result: [6,5,4,3,2] [1] -> 6 + 1 = 7
// Output: 7
// Explanation: First day you can finish the first 5 jobs, total difficulty = 6.
// Second day you can finish the last job, total difficulty = 1.
// The difficulty of the schedule = 6 + 1 = 7

// Input: jobDifficulty = [9,9,9], d = 4
// Result: [9] [9] [9] [] -> illegal schedule, -1
// Output: -1
// Explanation: If you finish a job per day you will still have a free day. you cannot find a schedule for the given jobs.

// Input: jobDifficulty = [1,1,1], d = 3
// Result: [1] [1] [1] -> 1 + 1 + 1 = 3
// Output: 3
// Explanation: The schedule is one job per day. total difficulty will be 3.

// Input: jobDifficulty = [7,1,7,1,7,1], d = 3
// Result: [7,1,7,1] [7] [1] -> 7 + 7 + 1 = 15
// Output: 15

// Input: jobDifficulty = [11,111,22,222,33,333,44,444], d = 6
// Result: [11] [111] [22] [222] [33] [333, 44, 444] 11 + 111 + 22 + 222 + 33 + 444 = 843
// Output: 843

class Solution
{
public:
    // vector<int> cuts;
    // int result{numeric_limits<int>::max()};

    // int evaluateDays(vector<int> &jobDifficulty)
    // {
    //     int total = 0;
    //     int lastCut = 0;
    //     for (int cut : cuts)
    //     {
    //         int maxDifficulty = 0;

    //         for (int job = lastCut; job <= cut; job++)
    //         {
    //             maxDifficulty = max(maxDifficulty, jobDifficulty[job]);
    //         }
    //         total += maxDifficulty;
    //         lastCut = cut + 1;
    //     }

    //     return total;
    // }

    // void naiveRecursiveInner(vector<int> &jobDifficulty, int d, int start)
    // {
    //     if (start >= jobDifficulty.size() - d + 1)
    //         return;

    //     if (d == 1)
    //     {
    //         cuts.push_back(jobDifficulty.size() - 1);
    //         int difficulty = evaluateDays(jobDifficulty);
    //         cuts.pop_back();
    //         result = min(result, difficulty);
    //         return;
    //     }

    //     int i = cuts.size() == 0 ? 0 : (cuts[cuts.size() - 1] + 1);
    //     for (; i < jobDifficulty.size() - 1; ++i)
    //     {
    //         cuts.push_back(i);
    //         naiveRecursiveInner(jobDifficulty, d - 1, i + 1);
    //         cuts.pop_back();
    //     }
    // }

    // // naive recursive is very very slow - essentially O(N choose d) runtime, which is exponential in general
    // // this one times out
    // int naiveRecursive(vector<int> &jobDifficulty, int d)
    // {
    //     naiveRecursiveInner(jobDifficulty, d, 0);
    //     return result;
    // }

    // O(dn^2) people in forums keep calling this O(dn), but that's a double for loop on n
    // the idea is to build up solutions from solutions for smaller numbers of days
    // for each number of days
    //   for each starting index (ignoring the array left of the index)
    //      for each proposed spot for a cut
    //         the best solution at the starting index either has a cut here or not
    //         not having a cut here would mean using the old solution for the starting index
    //         having a cut here would mean using the max difficulty found so far after the starting index + the solution for the right hand side of this cut
    // ~80ms
    int dynamicProgramming(vector<int> &jobDifficulty, int totalDays)
    {
        int n = jobDifficulty.size();
        int big = numeric_limits<int>::max() - 1000;
        vector<int> dp;
        dp.assign(n + 1, big);
        dp[n] = 0;
        //building up the best possible result for smaller to larger numbers of days
        for (int days = 1; days <= totalDays; ++days)
        {
            // at the end of this loop, dp[0] will have the correct solution for d = days
            for (int i = 0; i <= n - days; ++i)
            {
                // at the end of this iteration, dp[i] will have the correct solution for jobs[i::end] and d = days
                int maxDifficulty = 0;
                dp[i] = big;

                for (int j = i; j <= n - days; ++j)
                {
                    // maxDifficulty is the biggest job in the range jobs[i::j]
                    maxDifficulty = max(maxDifficulty, jobDifficulty[j]);
                    // for dp[i], the best solution to jobs[i::end] is either:
                    //    dp[i] (a solution found in a previous iteration of this loop)
                    //    maxDifficulty (the biggest job found so far) + dp[j + 1] (the solution for jobs[j + 1::end] && days - 1)
                    //       (in other words, put a cut at j. the left side of the cut is just maxDifficulty, the right side is a previously calculated solution for the rest of the array)
                    dp[i] = min(dp[i], maxDifficulty + dp[j + 1]);
                }
            }
        }

        return dp[0];
    }

    struct jobSegment
    {
        int imaxDifficultyjob;
        int minSolutionDifficulty;
    };

    // uses a monotonic stack to track the best solutions so far, instead of a 2d loop
    // O(d*n)
    // ~12ms - quite fast!
    int monotonicStack(vector<int> &jobDifficulty, int totalDays)
    {
        int n = jobDifficulty.size();
        // for this dp table, dp[n - 1] will have the best solution for cuts into totalDays
        vector<int> dp{jobDifficulty[0]};
        // at 0 days, the only solution is the max value in the entire array
        //   for dp[i] where i < n, dp[i] is the max difficulty to the left of i
        for (int j = 1; j < n; ++j)
            dp.push_back(max(dp[j - 1], jobDifficulty[j]));

        // for each number of days, we want to find the cut that reduces the total difficulty the least
        for (int days = 1; days < totalDays; ++days)
        {
            // this will be a monotonic stack
            stack<jobSegment> s;
            int solutionLeftOfI = dp[days - 1];

            for (int i = days; i < n; ++i)
            {
                int oldMinSolutionDifficulty = solutionLeftOfI;
                solutionLeftOfI = dp[i];

                // discard jobs on the stack that are less difficult than this one
                // this is almost like a double loop, but I think because the stack shrinks when looped over 
                //   it's more like O(2n) instead of O(n^2)
                while (!s.empty() && jobDifficulty[s.top().imaxDifficultyjob] <= jobDifficulty[i])
                {
                    // keep track of the easiest job seen so far
                    oldMinSolutionDifficulty = min(oldMinSolutionDifficulty, s.top().minSolutionDifficulty);
                    s.pop();
                }
                
                // somehow isolate the minimum seen in the current segment, and select a segment where this job difficulty is the max?
                dp[i] = oldMinSolutionDifficulty + jobDifficulty[i];
                // if there is still anything left in the monotonic stack (i.e., there was a more difficult job in there than this one)
                // then see if the solution for that job is better than the solution we just calculated
                if (!s.empty())
                    dp[i] = min(dp[s.top().imaxDifficultyjob], dp[i]);

                // i don't know if the name "iMaxDifficultyJob" is accurate exactly. 
                // it's just the index of the latest job explored
                // so, this is a monotonically decreasing stack, showing you the minimum solution difficulty seen to the left of index i
                s.push({i, oldMinSolutionDifficulty});
            }
        }
        return dp[n - 1];
    }

    int minDifficulty(vector<int> &jobDifficulty, int d)
    {
        if (jobDifficulty.size() < d)
            return -1;
        if (jobDifficulty.size() == d)
            return accumulate(jobDifficulty.begin(), jobDifficulty.end(), 0);

        return monotonicStack(jobDifficulty, d);
    }
};