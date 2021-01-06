#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

// Minimum Number of Refueling Stops - Hard

// A car travels from a starting position to a destination which is target miles east of the starting position.

// Along the way, there are gas stations.
// Each station[i] represents a gas station that is station[i][0] miles east of the starting position, and has station[i][1] liters of gas.

// The car starts with an infinite tank of gas, which initially has startFuel liters of fuel in it.
// It uses 1 liter of gas per 1 mile that it drives.

// When the car reaches a gas station, it may stop and refuel, transferring all the gas from the station into the car.

// What is the least number of refueling stops the car must make in order to reach its destination?
// If it cannot reach the destination, return -1.

// Note that if the car reaches a gas station with 0 fuel left, the car can still refuel there.
// If the car reaches the destination with 0 fuel left, it is still considered to have arrived.

// Example 1:

// Input: target = 1, startFuel = 1, stations = []
// Output: 0
// Explanation: We can reach the target without refueling.
// Example 2:

// Input: target = 100, startFuel = 1, stations = [[10,100]]
// Output: -1
// Explanation: We can't reach the target (or even the first gas station).
// Example 3:

// Input: target = 100, startFuel = 10, stations = [[10,60],[20,30],[30,30],[60,40]]
// Output: 2
// Explanation:
// We start with 10 liters of fuel.
// We drive to position 10, expending 10 liters of fuel.  We refuel from 0 liters to 60 liters of gas.
// Then, we drive from position 10 to position 60 (expending 50 liters of fuel),
// and refuel from 10 liters to 50 liters of gas.  We then drive to and reach the target.
// We made 2 refueling stops along the way, so we return 2.

// Note:

// - 1 <= target, startFuel, stations[i][1] <= 10^9
// - 0 <= stations.length <= 500
// - 0 < stations[0][0] < stations[1][0] < ... < stations[stations.length-1][0] < target

class Solution
{
public:
    // this greedy algorithm is incorrect, though it does at least check for feasibility
    int superNaive(int target, int startFuel, vector<vector<int>> &stations)
    {
        int totalFuel = startFuel;
        for (int i = 0; i < stations.size(); ++i)
        {
            if (totalFuel < stations[i][0])
                return -1;
            totalFuel += stations[i][1];
            if (totalFuel >= target)
                return i + 1;
        }
        return -1;
    }

    // this dynamic programming algorith is effectively n^2 time
    // we set up a dp set, distancePossible, which tells us how far we could get in n stops
    // at each station, we reevaluate all previous stations to see if skipping intermediate stations could lead to a longer distance
    // ~124ms
    int dynamicProgramming(int target, int startFuel, vector<vector<int>> &stations)
    {
        int n = stations.size();
        vector<long> distancePossible{};
        distancePossible.assign(n + 1, 0);
        // at position 0, the furthest we can go is are starting fuel
        distancePossible[0] = startFuel;

        for (int here = 0; here < n; ++here)
            // for each station that we have passed
            for (int there = here; there >= 0; --there)
                // if we could get "here" from there
                // then we might be able to skip the next station after there
                if (distancePossible[there] >= stations[here][0])
                    distancePossible[there + 1] = max(distancePossible[there + 1], distancePossible[there] + stations[here][1]);

        // return the first station which would allow us to get to the target
        for (int i = 0; i <= n; ++i)
            if (distancePossible[i] >= target)
                return i;
        return -1;
    }

    // quite a bit easier to understand than the previous solution
    // as we pass by stations, add them to a max heap.
    // when we run out of fuel, retroactively choose the best stations to refuel at until we have enough gas to continue
    // heap operations are ~logn, so overall we get nlogn time
    // ~52ms
    int withHeap(int target, int startFuel, vector<vector<int>> &stations)
    {
        vector<int> bestStations;
        int currentFuel = startFuel;
        int prevLocation = 0;
        int stops = 0;
        for (int i = 0; i < stations.size(); ++i)
        {
            int location = stations[i][0];
            int capacity = stations[i][1];
            currentFuel = currentFuel - location + prevLocation;

            // now that we need fuel, retroactively refuel
            while (currentFuel < 0 && !bestStations.empty())
            {
                pop_heap(bestStations.begin(), bestStations.end());
                currentFuel += bestStations.back();
                bestStations.pop_back();
                ++stops;
            }

            if (currentFuel < 0)
                return -1;

            bestStations.push_back(capacity);
            push_heap(bestStations.begin(), bestStations.end());
            prevLocation = location;
        }

        // finally, check against target
        currentFuel = currentFuel - target + prevLocation;

        // now that we need fuel, retroactively refuel
        while (currentFuel < 0 && !bestStations.empty())
        {
            pop_heap(bestStations.begin(), bestStations.end());
            currentFuel += bestStations.back();
            bestStations.pop_back();
            ++stops;
        }

        if (currentFuel < 0)
            return -1;

        return stops;
    }

    // exact same algorithm as withHeap, just a different data structure
    // still nlogn
    // ~50ms, shouldn't actually be any faster than the max_heap implementation above, just nicer looking
    int withPriorityQueue(int target, int startFuel, vector<vector<int>> &stations)
    {        
        priority_queue<int> bestStations;
        int currentFuel = startFuel;
        int prevLocation = 0;
        int stops = 0;
        for (int i = 0; i < stations.size(); ++i)
        {
            int location = stations[i][0];
            int capacity = stations[i][1];
            currentFuel = currentFuel - location + prevLocation;

            // now that we need fuel, retroactively refuel
            while (currentFuel < 0 && !bestStations.empty())
            {
                currentFuel += bestStations.top();
                bestStations.pop();
                ++stops;
            }

            if (currentFuel < 0)
                return -1;

            bestStations.push(capacity);
            prevLocation = location;
        }

        // finally, check against target
        currentFuel = currentFuel - target + prevLocation;

        // now that we need fuel, retroactively refuel
        while (currentFuel < 0 && !bestStations.empty())
        {
            currentFuel += bestStations.top();
            bestStations.pop();
            ++stops;
        }

        if (currentFuel < 0)
            return -1;

        return stops;
    }

    int minRefuelStops(int target, int startFuel, vector<vector<int>> &stations)
    {
        // don't need gas
        if (startFuel >= target)
            return 0;

        // need gas, no stations
        if (stations.size() == 0)
            return -1;

        // need gas, first station too far away
        if (stations[0][0] > startFuel)
            return -1;

        return withPriorityQueue(target, startFuel, stations);
    }
};