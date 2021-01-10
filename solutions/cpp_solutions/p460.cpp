#include <unordered_map>
#include <limits>
#include <vector>
#include <iostream>
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
        int usage{0};
        CacheNode *next{nullptr};
        CacheNode *prev{nullptr};
    };

    int capacity{0};
    // itemsByKey allows O(1) lookup of items for get/put operations
    unordered_map<int, CacheNode *> itemsByKey;
    // itemsByUsage contains the most recently used items in each usage class
    // when an item is promoted in its usage, it will jump to the end of its usage class using this map
    // this allows O(1) promotion of items when their usage increases
    unordered_map<int, CacheNode *> itemsByUsage;
    // head is the front of a doubly-linked-list of items
    // this list has items in order of increasing usage and recency (if recency is a word)
    // this allows O(1) lookup of the least frequently and least recently used item
    CacheNode *head{nullptr};

    void removeLeastUsedItem()
    {
        if (head == nullptr)
            return;

        // cout << "\tset full, deleting key" << head->key << " with usage" << head->usage << endl;
        auto old = head;

        // if an item is being removed, and it is the record in the usage map
        // then it is the last record of that usage value in the map
        // and we can remove that usage value from the map
        auto usage = itemsByUsage.find(old->usage);
        if (usage->second == old)
            itemsByUsage.erase(usage);

        // remove the value from the keymap
        itemsByKey.erase(head->key);

        // update the head of the list cache
        if (head->next != nullptr)
            head->next->prev = nullptr;
        head = head->next;

        // don't leak memory when we're done with this item
        delete old;
    }

    void addToCache(CacheNode *n)
    {
        itemsByKey[n->key] = n;

        // add the item to the head of the cache
        if (head != nullptr)
        {
            n->next = head;
            head->prev = n;
        }
        head = n;

        promote(n);
    }

    void promote(CacheNode *n)
    {
        // check if this was the most recently used item in this usage class
        // check if the item before this one has the same usage
        //   if it does, update the usage map to use the older value
        //   if it doesn't, remove this key from the usage map
        // at the end of this block, n must not be in the usage map
        auto oldUsage = itemsByUsage.find(n->usage);
        if (oldUsage != itemsByUsage.end() && oldUsage->second == n)
        {
            if (n->prev == nullptr || n->prev->usage != n->usage)
                itemsByUsage.erase(n->usage);
            else
                oldUsage->second = n->prev;
        }

        // cout << "\tpromoting key" << n->key << " with usage" << n->usage << " to " << n->usage + 1 << endl;

        // increase the usage of this item
        n->usage++;

        // if the item is less used than the next most used thing, or it's the most used thing
        // then we can't promote this item
        // make n the leader of its usage class
        if (n->next == nullptr || n->next->usage > n->usage){
            itemsByUsage[n->usage] = n;
            return;
        }

        // now we want to jump to the end of the current or the previous usage class.
        // if there is no record for itemsByUsage[n->usage], then n needs to move to the end of the usage class it was in previously
        // if there is no record for itemsByUsage[n->usage -1], then n is already in the correct position in the list
        auto usage = itemsByUsage.find(n->usage);
        if (usage == itemsByUsage.end())
            usage = itemsByUsage.find(n->usage - 1);

        if (usage != itemsByUsage.end())
        {
            auto here = usage->second;

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

            // add n after here
            n->next = here->next;
            if (here->next != nullptr)
                here->next->prev = n;
            here->next = n;
            n->prev = here;
        }

        // make n the leader of its usage class
        itemsByUsage[n->usage] = n;
    }

public:
    LFUCache(int capacity)
    {
        this->capacity = capacity;
        itemsByKey.reserve(capacity);
        itemsByUsage.reserve(capacity);
    }

    int get(int key)
    {
        if (capacity <= 0)
            return -1;

        // look for this value
        auto item = itemsByKey.find(key);
        if (item == itemsByKey.end())
            return -1;

        // increase the usage of this value
        promote(item->second);

        return item->second->value;
    }

    void put(int key, int value)
    {
        if (capacity <= 0)
            return;

        // if we already have this key, update its value and increase its usage
        auto item = itemsByKey.find(key);
        if (item != itemsByKey.end())
        {
            item->second->value = value;
            promote(item->second);
            return;
        }

        // if we are full, remove the least used item
        if (itemsByKey.size() == capacity)
            removeLeastUsedItem();

        addToCache(new CacheNode{key, value});
    }

    void printCache()
    {
        cout << "\tlist cache: ";
        auto ptr = head;
        while (ptr != nullptr)
        {
            cout << " { key" << ptr->key << " value" << ptr->value << " usage" << ptr->usage << " }";
            ptr = ptr->next;
        }
        cout << endl;

        cout << "\tusage cache: ";
        for (auto &pair : itemsByUsage){
            cout << " { usage" << pair.first << " key" << pair.second->key << " }";
        }
        cout << endl;
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

int main()
{
    vector<string> commands{"LFUCache", "put", "put", "put", "put", "put", "get", "put", "get", "get", "put", "get", "put", "put", "put", "get", "put", "get", "get", "get", "get", "put", "put", "get", "get", "get", "put", "put", "get", "put", "get", "put", "get", "get", "get", "put", "put", "put", "get", "put", "get", "get", "put", "put", "get", "put", "put", "put", "put", "get", "put", "put", "get", "put", "put", "get", "put", "put", "put", "put", "put", "get", "put", "put", "get", "put", "get", "get", "get", "put", "get", "get", "put", "put", "put", "put", "get", "put", "put", "put", "put", "get", "get", "get", "put", "put", "put", "get", "put", "put", "put", "get", "put", "put", "put", "get", "get", "get", "put", "put", "put", "put", "get", "put", "put", "put", "put", "put", "put", "put"};
    vector<vector<int>> args{{10}, {10, 13}, {3, 17}, {6, 11}, {10, 5}, {9, 10}, {13}, {2, 19}, {2}, {3}, {5, 25}, {8}, {9, 22}, {5, 5}, {1, 30}, {11}, {9, 12}, {7}, {5}, {8}, {9}, {4, 30}, {9, 3}, {9}, {10}, {10}, {6, 14}, {3, 1}, {3}, {10, 11}, {8}, {2, 14}, {1}, {5}, {4}, {11, 4}, {12, 24}, {5, 18}, {13}, {7, 23}, {8}, {12}, {3, 27}, {2, 12}, {5}, {2, 9}, {13, 4}, {8, 18}, {1, 7}, {6}, {9, 29}, {8, 21}, {5}, {6, 30}, {1, 12}, {10}, {4, 15}, {7, 22}, {11, 26}, {8, 17}, {9, 29}, {5}, {3, 4}, {11, 30}, {12}, {4, 29}, {3}, {9}, {6}, {3, 4}, {1}, {10}, {3, 29}, {10, 28}, {1, 20}, {11, 13}, {3}, {3, 12}, {3, 8}, {10, 9}, {3, 26}, {8}, {7}, {5}, {13, 17}, {2, 27}, {11, 15}, {12}, {9, 19}, {2, 15}, {3, 16}, {1}, {12, 17}, {9, 1}, {6, 19}, {4}, {5}, {5}, {8, 1}, {11, 7}, {5, 2}, {9, 28}, {1}, {2, 2}, {7, 4}, {4, 22}, {7, 24}, {9, 26}, {13, 28}, {11, 26}};
    vector<string> results{"null", "null", "null", "null", "null", "null", "-1", "null", "19", "17", "null", "-1", "null", "null", "null", "-1", "null", "-1", "5", "-1", "12", "null", "null", "3", "5", "5", "null", "null", "1", "null", "-1", "null", "30", "5", "30", "null", "null", "null", "-1", "null", "-1", "24", "null", "null", "18", "null", "null", "null", "null", "14", "null", "null", "18", "null", "null", "11", "null", "null", "null", "null", "null", "18", "null", "null", "-1", "null", "4", "29", "30", "null", "12", "11", "null", "null", "null", "null", "29", "null", "null", "null", "null", "17", "-1", "18", "null", "null", "null", "-1", "null", "null", "null", "20", "null", "null", "null", "29", "18", "18", "null", "null", "null", "null", "20", "null", "null", "null", "null", "null", "null", "null"};

    LFUCache *cache = nullptr;
    for (int i = 0; i < commands.size(); ++i)
    {
        string command = commands[i];
        vector<int> arg = args[i];
        string result = results[i];

        if (command == "LFUCache")
        {
            cout << i << ": instantiating cache with size " << arg[0] << endl;
            cache = new LFUCache(arg[0]);
        }
        else if (command == "put")
        {
            cout << i << ": putting: key" << arg[0] << ": value" << arg[1] << endl;
            cache->put(arg[0], arg[1]);
            cache->printCache();
        }
        else if (command == "get")
        {
            int ans = cache->get(arg[0]);
            cout << i << ": getting: key" << arg[0] << ": value" << ans;
            if (result != to_string(ans))
                cout << " !!! (expected: value" << result << ")";
            cout << endl;
            cache->printCache();
        }
    }
}