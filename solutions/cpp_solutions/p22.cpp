
// Swap Nodes in Pairs - Medium

// Given a linked list, swap every two adjacent nodes and return its head.

 struct ListNode {
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
 };

class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if (head == nullptr)
            return nullptr;
        if (head->next == nullptr)
            return head;

        ListNode dummy;
        dummy.next = head;
        ListNode *prev = &dummy;
        do {
            ListNode *next = head->next;
            head->next = next->next;
            next->next = head;
            prev->next = next;
            prev = head;
            head = head->next;
        } while (head != nullptr && head->next != nullptr);

        return dummy.next;
    }
};