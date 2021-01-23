#include <vector>
#include <numeric>
#include <queue>
#include <algorithm>
using namespace std;
// Minimum cost to hire k workers

// There are N workers.  The i-th worker has a quality[i] and a minimum wage expectation wage[i].

// Now we want to hire exactly K workers to form a paid group.
// When hiring a group of K workers, we must pay them according to the following rules:

// Every worker in the paid group should be paid in the ratio of their quality compared to other workers in the paid group.
// Every worker in the paid group must be paid at least their minimum wage expectation.
// Return the least amount of money needed to form a paid group satisfying the above conditions.

class Solution
{
public:
    double mincostToHireWorkers(vector<int> &quality, vector<int> &wage, int K)
    {
        // ratio of wage/quality for each worker
        vector<pair<double, double>> workers;
        for (int i = 0; i < quality.size(); ++i)
            workers.push_back({(double)wage[i] / quality[i], (double)quality[i]});

        // sort workers by wage / quality. emphasize undervalued employees
        sort(workers.begin(), workers.end());
        double result{numeric_limits<double>::max()};
        // sum of the quality of the current group of employees
        double qualitySum{0};
        // queue of the employees in the group, emphasizing highest quality
        priority_queue<int> pq;
        for (auto &w : workers)
        {
            qualitySum += w.second;
            pq.push(w.second);
            // if we have too many employees in the group
            // reduce the group size by the highest quality member
            if (pq.size() > K)
            {
                qualitySum -= pq.top();
                pq.pop();
            }
            // if the group is size K, then this current employee has the highest wage/quality demand
            // their demand defines the wage for the entire group
            // so calculate the overall group wage now
            if (pq.size() == K)
            {
                result = min(result, qualitySum * w.first);
            }
        }
        return result;
    }
};