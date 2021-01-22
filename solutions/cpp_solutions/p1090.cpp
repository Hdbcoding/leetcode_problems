#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

// Largest Values from labels - Medium

// We have a set of items: the i-th item has value values[i] and label labels[i].

// Then, we choose a subset S of these items, such that:

// |S| <= num_wanted
// For every label L, the number of items in S with label L is <= use_limit.
// Return the largest possible sum of the subset S.

struct item {
  int label;
  int value;
};

struct itemComparator
{
    bool operator()(const item &a, const item &b){
        return a.value < b.value;
    }
};

class Solution {
public:
    int largestValsFromLabels(vector<int>& values, vector<int>& labels, int num_wanted, int use_limit) {
        priority_queue<item, vector<item>, itemComparator> pq;
        
        for (int i = 0; i < values.size(); ++i){
            pq.push({labels[i], values[i]});
        }
        
        int sum{0};
        // map from label -> num used
        unordered_map<int, int> usage;
        
        while (num_wanted > 0 && !pq.empty()){
            item current = pq.top();
            pq.pop();
            if (usage[current.label] < use_limit) 
            {
                sum += current.value;
                --num_wanted;
            }
            usage[current.label]++;
        }
        
        return sum;
    }
};