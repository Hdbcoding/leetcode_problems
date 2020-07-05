
// Add Two Numbers - Medium
// You are given two non-empty linked lists representing two non-negative integers. 
// The digits are stored in reverse order and each of their nodes contain a single digit. 
// Add the two numbers and return it as a linked list.
// You may assume the two numbers do not contain any leading zero, except the number 0 itself.

 struct ListNode {
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
 };
 
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* ret{nullptr};
        ListNode* next{nullptr};
        bool carryOne{false};
        
        while (l1 || l2){
            int left = l1 ? l1->val : 0;
            int right = l2 ? l2 -> val : 0;
            int nextVal = left + right + (carryOne ? 1 : 0);
            carryOne = nextVal >= 10;
            if (carryOne) nextVal -= 10;
            
            if (next == nullptr){
                ret = next = new ListNode(nextVal);            
            } else {
                next->next = new ListNode(nextVal);
                next = next->next;
            }
            
            l1 = l1 ? l1->next : l1;
            l2 = l2 ? l2->next : l2;
        }
        
        if (carryOne){
            next->next = new ListNode(1);
        }
        
        return ret;
    }
};