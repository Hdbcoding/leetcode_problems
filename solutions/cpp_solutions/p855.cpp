#include <set> 
#include <unordered_map> 
#include <iostream> 

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
    
    gap *prev{nullptr};
    gap *next{nullptr};
    
    const int length() const {
        return end - start + 1;
    }
    
    const int middle() const {
        return start + length() / 2;
    }
};

struct gapComparator
{
    bool operator()(gap *a, gap *b) const
    {
        if (a->start == b->start) 
            return false;
        
        // cout << "\t\ta: { start:" << a->start << ", end:" << a->end << ", length:" << a->length() << ", middle: " << a->middle() << " }" << endl;
        // cout << "\t\tb: { start:" << b->start << ", end:" << b->end << ", length:" << b->length() << ", middle: " << b->middle() << " }" << endl;

        int al = a->length(), bl = b->length();
        // same length? return the earlier one
        if (al == bl) {
            // cout << "\t\tlength equal, return earlier gap" << endl;
            return a->start < b->start;
        }
        
        // different length? 
        // different by one?
        // choose the bigger one if it's even, 
        // otherwise choose the earlier one
        int diff = al - bl;
        if (diff > 1) 
        {
            // cout << "\t\ta much bigger" << endl;
            return true;
        }
        if (diff < -1) 
        {
            // cout << "\t\tb much bigger" << endl;
            return false;
        }
        
        if (diff == 1 && al % 2 == 0) 
        {
            // cout << "\t\ta slightly bigger, and even" << endl;
            return true;
        }
        if (diff == -1 && bl % 2 == 0) 
        {
            // cout << "\t\tb slightly bigger, and even" << endl;
            return false;
        }
        
        // cout << "\t\tbigger is not even, return earlier" << endl;
        return a->start < b->start;   
    }
};

class ExamRoom {
    // ordered binary tree of gaps, ordered by the comparator above
    set<gap*, gapComparator> gapSet;
    // set<gap*> gapSet;
    unordered_map<int, gap*> gapMap;
    
    void removeFromSet(gap *a){
        auto it = gapSet.find(a);
        gapSet.erase(it);
    }
    
public:
    ExamRoom(int N) {
        gap* initial = new gap{ 0, N - 1 };
        gapSet.insert(initial);
        gapMap[0] = initial;
    }
    
    int seat() {
        // choose the biggest gap
        auto it = gapSet.begin();
        gap *biggest = *it;
        
        // only the gap for the first index is ever empty
        if (!biggest->full){
            biggest->full = true;
            return 0;
        }
        
        // remove the biggest from the gapSet
        gapSet.erase(it);
        
        // if no one is sitting after me, add to the end of the gap
        if (biggest->next == nullptr) 
        {
            int end = biggest->end;
            gap *next = new gap{end, end, true};
            
            // update ptrs
            next->prev = biggest;
            biggest->next = next;
            
            // update bounds of biggest
            biggest->end = end - 1;
            
            // update gapMap
            gapMap[end] = next;

            // update gapSet
            gapSet.insert(next);
            gapSet.insert(biggest);
            
            return end;
        } 
        else 
        {
            // otherwise, split the gap
            int middle = biggest->middle();
            gap *next = new gap{middle, biggest->end, true};
            
            // update ptrs
            if (biggest->next != nullptr){
                biggest->next->prev = next;
                next->next = biggest->next;
            }
            biggest->next = next;
            next->prev = biggest;
            
            // update bounds of biggest
            biggest->end = middle - 1;

            // update gapMap
            gapMap[middle] = next;

            // update gapSet
            gapSet.insert(next);
            gapSet.insert(biggest);

            return middle;
        }
    }
    
    void leave(int p) {
        auto it = gapMap.find(p);
        gap* here = it->second;
        
        // if this is the first slot, don't actually remove it, just mark it empty
        if (here->start == 0){
            here->full = false;
            return;
        }
        
        // if we have a prev ptr, update its length and re add it to the set
        if (here->prev != nullptr)
        {
            // need to also remove and re-add here->prev;
            here->prev->end = here->end;
            gapSet.erase(here->prev);
            gapSet.insert(here->prev);
        }
        
        // if we have a next ptr, make sure that knows its proper prev ptr
        if (here->next != nullptr) {
            here->next->prev = here->prev;
        }
        
        // remove this location from the set
        gapSet.erase(here);
        gapMap.erase(it);
        delete here;
    }
};

/**
 * Your ExamRoom object will be instantiated and called as such:
 * ExamRoom* obj = new ExamRoom(N);
 * int param_1 = obj->seat();
 * obj->leave(p);
 */

int main(){
    ExamRoom room(10);

    cout << "taking a seat..." << endl;
    int seat = room.seat();
    cout << "took seat: " << seat << endl;

    cout << "taking a seat..." << endl;
    seat = room.seat();
    cout << "seating: " << seat << endl;

    cout << "taking a seat..." << endl;
    seat = room.seat();
    cout << "seating: " << seat << endl;;

    cout << "taking a seat..." << endl;
    seat = room.seat();
    cout << "seating: " << seat << endl;;

    cout << "booting 4" << endl;
    room.leave(4);

    cout << "taking a seat..." << endl;
    seat = room.seat();
    cout << "seating: " << seat << endl;;
}