#include <set>
#include <unordered_map>
#include <iostream>
#include <vector>

using namespace std;
// Exam Room - Medium

struct gap
{
    // index of person who defines this gap
    int start;
    // index of last space before the next person (or the end of the set)
    int end;
    // is full?
    bool full{false};

    // "pointers" to the next gap
    int prev{-1};
    int next{-1};

    const int length() const
    {
        return end - start + (full ? 0 : 1);
    }

    const int halfLength() const
    {
        return (length() + 1) / 2;
    }

    const int middle() const
    {
        return start + halfLength();
    }

    friend ostream &operator<<(ostream &s, const gap &g)
    {
        return s << "{ start:" << g.start << ", end:" << g.end << ", next:" << g.next << ", prev:" << g.prev << ", halfLength:" << g.halfLength() << " }";
    }
};

struct gapComparator
{
    bool operator()(const gap &a, const gap &b) const
    {
        if (a.start == b.start)
            return false;

        int ahl = a.halfLength(), bhl = b.halfLength();

        // special case - if the first gap is empty, the distance to the nearest seat is the entire length of the gap
        // another special case - if the gap has no following gap, the distance to the nearest seat is the entire length of the gap

        if (!a.full || a.next == -1)
            ahl = a.length();

        if (!b.full || b.next == -1)
            bhl = b.length();

        // if half lengths are equal, return the earlier gap
        // otherwise, return the bigger gap
        bool aBetter = (ahl == bhl && a.start < b.start) || ahl > bhl;

        // cout << "\t\tcomparing a: " << a << ", b: " << b << "  ---> " << aBetter << endl;

        return aBetter;
    }
};

class ExamRoom
{
    // ordered binary tree of gaps, ordered by the comparator above
    set<gap, gapComparator> gapSet;
    // map of starting index to gap object
    unordered_map<int, gap> startMap;

    void insert(gap &g)
    {
        // cout << "\tinserting gap: " << g << endl;
        startMap[g.start] = g;
        gapSet.insert(g);
    }

public:
    ExamRoom(int N)
    {
        gap initial{0, N - 1};
        insert(initial);
    }

    int seat()
    {
        // cout << "choosing a seat... " << endl;
        // choose the biggest gap
        auto it = gapSet.begin();
        gap biggest = *it;
        gapSet.erase(it);

        // cout << "biggest gap was: " << biggest << endl;

        // only the gap for the first index is ever empty
        if (!biggest.full)
        {
            biggest.full = true;
            insert(biggest);
            return 0;
        }

        // split the gap
        gap next{biggest.middle(), biggest.end, true, biggest.start};
        // if no one is sitting after me, add to the end of the gap
        if (biggest.next == -1)
        {
            // cout << "no gap after biggest, sitting at the end" << endl;
            next.start = biggest.end;
        }
        else
        {
            // update the old next to recognize the new prev
            auto nextIt = startMap.find(biggest.next);
            gap oldNext = nextIt->second;
            gapSet.erase(oldNext);

            // cout << "splitting the gap. old gap after biggest was: " << oldNext << endl;

            oldNext.prev = next.start;
            next.next = oldNext.start;
            insert(oldNext);
        }

        biggest.next = next.start;
        biggest.end = next.start - 1;

        insert(biggest);
        insert(next);

        return next.start;
    }

    void leave(int p)
    {
        // cout << "vacating seat " << p << endl;
        auto it = startMap.find(p);
        gap here = it->second;
        startMap.erase(it);
        gapSet.erase(here);

        // if this is the first slot, don't actually remove it, just mark it empty
        if (here.start == 0)
        {
            // cout << "special rule for first slot, just mark it empty" << endl;
            here.full = false;
            insert(here);
            return;
        }

        // if we have a prev ptr, update its length and re add it to the set
        if (here.prev != -1)
        {
            // need to also remove and re-add here->prev;
            auto prevIt = startMap.find(here.prev);
            gap prev = prevIt->second;
            gapSet.erase(prev);

            // cout << "updating previous gap to have the correct end: " << prev << endl;

            prev.end = here.end;
            prev.next = here.next;

            insert(prev);
        }

        // if we have a next ptr, make sure that knows its proper prev ptr
        if (here.next != -1)
        {
            auto nextIt = startMap.find(here.next);
            gap next = nextIt->second;
            gapSet.erase(next);

            // cout << "updating next gap to have the correct prev" << next << endl;

            next.prev = here.prev;
            insert(next);
        }
    }
};

/**
 * Your ExamRoom object will be instantiated and called as such:
 * ExamRoom* obj = new ExamRoom(N);
 * int param_1 = obj->seat();
 * obj->leave(p);
 */

void evaluateProblem(int seats, const vector<bool> &sits, const vector<int> &indices)
{
    cout << "Evaluating exam room with " << seats << " seats" << endl;
    ExamRoom room{seats};
    for (int i = 0; i < sits.size(); ++i)
    {
        if (sits[i])
        {
            cout << "choosing an empty seat" << endl;
            int sit = room.seat();
            cout << "seat " << sit << " was chosen" << endl;
        }
        else
        {
            cout << "clearing seat " << indices[i] << endl;
            room.leave(indices[i]);
            cout << "cleared seat " << indices[i] << endl;
        }
    }
}

int main()
{
    // ["ExamRoom","seat","seat","seat","leave","leave","seat","seat","seat","seat","seat","seat","seat","seat","seat","leave","leave","seat","seat","leave","seat","leave","seat","leave","seat","leave","seat","leave","leave","seat","seat","leave","leave","seat","seat","leave"]
    // [[10],[],[],[],0,4,[],[],[],[],[],[],[],[],[],0,4,[],[],7,[],3,[],3,[],9,[],0,8,[],[],0,8,[],[],2]
    // expected: [null,0,9,4,null,null,0,4,2,6,1,3,5,7,8,null,null,0,4,null,7,null,3,null,3,null,9,null,null,0,8,null,null,0,8,null]
    vector<bool> sits{true, true, true, false, false, true, true, true, true, true, true, true, true, true, false, false, true, true, false, true, false, true, false, true, false, true, false, false, true, true, false, false, true, true, false};
    vector<int> indices{-1, -1, -1, 0, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0, 4, -1, -1, 7, -1, 3, -1, 3, -1, 9, -1, 0, 8, -1, -1, 0, 8, -1, -1, 2};
    evaluateProblem(10, sits, indices);

    // ["ExamRoom","seat","seat","seat","leave","leave","seat","seat","seat","seat","seat","seat","seat"]
    // [[8],[],[],[],[0],[7],[],[],[],[],[],[],[]]
    vector<bool> sits2{true, true, true, false, false, true, true, true, true, true, true, true};
    vector<int> indices2{-1, -1, -1, 0, 7, -1, -1, -1, -1, -1, -1, -1};
    evaluateProblem(8, sits2, indices2);

    // ["ExamRoom","seat","seat","seat","seat","leave","leave","seat"]
    // [[4],[],[],[],[],[1],[3],[]]
    evaluateProblem(4, {true, true, true, true, false, false, true}, {0, 0, 0, 0, 1, 3, 0});
}