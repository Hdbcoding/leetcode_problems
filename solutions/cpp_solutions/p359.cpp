#include <unordered_map>
#include <string>
using namespace std;

// Logger Rate Limiter - Easy

// Design a logger system that receives a stream of messages along with their timestamps.
// Each unique message should only be printed at most every 10 seconds
// (i.e. a message printed at timestamp t will prevent other identical messages from being printed until timestamp t + 10).

// All messages will come in chronological order. Several messages may arrive at the same timestamp.

// Implement the Logger class:

// Logger() Initializes the logger object.
// bool shouldPrintMessage(int timestamp, string message)
// Returns true if the message should be printed in the given timestamp, otherwise returns false.

class Logger
{
    unordered_map<string, int> map;

public:
    Logger() {}

    /** Returns true if the message should be printed in the given timestamp, otherwise returns false.
        If this method returns false, the message will not be printed.
        The timestamp is in seconds granularity. */
    bool shouldPrintMessage(int timestamp, string message)
    {
        bool success = true;
        // if we've seen this message before
        // and we saw it recently
        auto found = map.find(message);
        if (found != map.end() && found->second > timestamp)
            // it's too soon to send this message
            success = false;
        else
            map[message] = timestamp + 10;

        return success;
    }
};

/**
 * Your Logger object will be instantiated and called as such:
 * Logger* obj = new Logger();
 * bool param_1 = obj->shouldPrintMessage(timestamp,message);
 */