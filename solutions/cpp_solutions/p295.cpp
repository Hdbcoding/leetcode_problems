#include <vector>
#include <queue>
using namespace std;
// Find Median from Data Stream - Hard

// Median is the middle value in an ordered integer list.
// If the size of the list is even, there is no middle value. So the median is the mean of the two middle value.

// For example,
// [2,3,4], the median is 3

// [2,3], the median is (2 + 3) / 2 = 2.5

// Design a data structure that supports the following two operations:

// void addNum(int num) - Add a integer number from the data stream to the data structure.
// double findMedian() - Return the median of all elements so far.

class MedianFinder
{
    priority_queue<int, vector<int>, greater<int>> topHeap;
    priority_queue<int> bottomHeap;

public:
    void addNum(int num)
    {
        if (topHeap.empty() || num >= topHeap.top())
            topHeap.push(num);
        else
            bottomHeap.push(num);

        // if there's too much stuff on top, pull it down
        while (topHeap.size() > bottomHeap.size() + 1)
        {
            bottomHeap.push(topHeap.top());
            topHeap.pop();
        }

        // if there's too much stuff on the bottom, pull it up
        while (bottomHeap.size() > topHeap.size())
        {
            topHeap.push(bottomHeap.top());
            bottomHeap.pop();
        }
    }

    double findMedian()
    {
        if (topHeap.size() == bottomHeap.size())
            return (topHeap.top() + bottomHeap.top()) / 2.0;
        return topHeap.top();
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */