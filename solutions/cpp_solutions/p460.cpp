#include <unordered_map>
#include <limits>
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
        CacheNode *next{nullptr};
        CacheNode *prev{nullptr};
    };

    int capacity{0};
    unordered_map<int, CacheNode*> items;
    CacheNode *head{nullptr};

    void removeLeastUsedItem()
    {
        if (head == nullptr)
            return;

        auto old = head;

        items.erase(head->key);

        head->next->prev = nullptr;
        head = head->next;

        delete old;
    }

    void addToCache(CacheNode *n)
    {
        items[n->key] = n;

        // add the item to the front of the cache
        if (head == nullptr)
        {
            head = n;
        }
        else
        {
            n->next = head;
            head->prev = n;
        }

        promote(n);
    }

    void promote(CacheNode *n)
    {
        // couldn't possibly promote it more
        if (n->next == nullptr)
            return;

        // find the next element in the cache more used than this item
        auto here = n->next;
        while (here->next != nullptr && n->usage >= here->usage)
            here = here->next;

        // remove n from where it is

        if (n->prev == nullptr)
        {
            head = n->next;
            head->prev = nullptr;
        }
        else
        {
            n->prev->next = n->next;
            n->next->prev = n->prev;
        }
        n->next = nullptr;
        n->prev = nullptr;

        // add n after here
        n->next = here->next;
        if (here->next != nullptr)
            here->next->prev = n;
        here->next = n;
        n->prev = here;
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
        item->second->usage++;
        promote(item->second);

        return item->second->value;
    }

    void put(int key, int value)
    {
        if (capacity <= 0)
            return;

        // if we already have this key, update its value and increase its usage
        auto item = items.find(key);
        if (item != items.end())
        {
            item->second->value = value;
            item->second->usage++;
            promote(item->second);
            return;
        }

        if (items.size() == capacity)
            removeLeastUsedItem();

        addToCache(new CacheNode{key, value});
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */