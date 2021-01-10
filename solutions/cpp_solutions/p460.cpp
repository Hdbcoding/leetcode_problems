#include <unordered_map>
#include <limits>
#include <list>
using namespace std;
// LFU Cache - Hard

// Design and implement a data structure for Least Frequently Used (LFU) cache.

// Implement the LFUCache class:

// LFUCache(int capacity) Initializes the object with the capacity of the data structure.
// int get(int key) Gets the value of the key if the key exists in the cache. Otherwise, returns -1.
// void put(int key, int value) Sets or inserts the value if the key is not already present.
// When the cache reaches its capacity, it should invalidate the least frequently used item before inserting a new item.
// For this problem, when there is a tie (i.e., two or more keys with the same frequency), the least recently used key would be evicted.
// Notice that the number of times an item is used is the number of calls to the get and put functions for that item since it was inserted.
// This number is set to zero when the item is removed.

class LFUCache
{
    struct CacheNode
    {
        int key;
        int value;
        int usage{1};
        list<CacheNode>::iterator it;
    };

    int capacity;
    unordered_map<int, CacheNode> items;
    list<CacheNode> cache;

    void removeLeastUsedItem()
    {
        auto leastUsed = cache.front();
        items.erase(leastUsed.key);
        cache.pop_front();
    }

    void addToCache(CacheNode n)
    {
        items[n.key] = n;

        // add the item to the front of the cache
        cache.push_front(n);
        n.it = cache.begin();

        promote(n);
    }

    void promote(CacheNode n)
    {
        // couldn't possibly promote it more
        if (n.key == cache.back().key)
            return;

        auto iter = n.it;
        // find the next element in the cache more used than this item
        while (iter != cache.end() && n.usage >= iter->usage)
            ++iter;
        // pull this item out of wherever it is
        cache.erase(n.it);
        // add this item back to the cache before the more used item
        cache.insert(iter, n);
        // make sure the item knows where it is
        n.it = iter;
    }

public:
    LFUCache(int capacity)
    {
        this->capacity = capacity;
        items.reserve(capacity);
    }

    int get(int key)
    {
        if (capacity <= 0)
            return -1;

        // look for this value
        auto item = items.find(key);
        if (item == items.end())
            return -1;

        // increase the usage of this value
        item->second.usage++;
        promote(item->second);

        return item->second.value;
    }

    void put(int key, int value)
    {
        if (capacity <= 0)
            return;

        // if we already have this key, update its value and increase its usage
        auto item = items.find(key);
        if (item != items.end())
        {
            item->second.value = value;
            item->second.usage++;
            promote(item->second);
            return;
        }

        if (items.size() == capacity)
            removeLeastUsedItem();

        addToCache({key, value});
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */