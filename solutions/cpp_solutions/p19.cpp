
// given this definition of listnode
struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// Remove Nth Node From End of List - Medium
// Given the head of a linked list, remove the nth node from the end of the list and return its head.
// Follow up: Could you do this in one pass?

// Constraints:

// The number of nodes in the list is sz.
// 1 <= sz <= 30
// 0 <= Node.val <= 100
// 1 <= n <= sz

class Solution
{
public:
    int size(ListNode *head)
    {
        int s{0};
        ListNode *that = head;
        while (that != nullptr)
        {
            that = that->next;
            s++;
        }
        return s;
    }

    ListNode *twoPass(ListNode *head, int n)
    {
        int length = size(head);

        if (n == length)
            return head->next;

        ListNode *that = head;
        for (int i = 0; i < length - n - 1; ++i)
            that = that->next;

        if (that->next != nullptr)
            that->next = that->next->next;

        return head;
    }

    ListNode *removeNthFromEnd(ListNode *head, int n)
    {
        return twoPass(head, n);
    }
};