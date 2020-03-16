// Add Two Numbers - Medium

// You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.

// You may assume the two numbers do not contain any leading zero, except the number 0 itself.

/**
 * Definition for singly-linked list.
 * function ListNode(val) {
 *     this.val = val;
 *     this.next = null;
 * }
 */
/**
 * @param {ListNode} l1
 * @param {ListNode} l2
 * @return {ListNode}
 */
var addTwoNumbers = function(l1, l2) {
    let carry = 0;
    let cur1 = l1;
    let cur2 = l2;
    let ret = new ListNode(0);
    let retCur = ret;
    while (cur1 || cur2){
        let val = (cur1 ? cur1.val : 0) 
            + (cur2 ? cur2.val : 0)
            + retCur.val;
        if (val >= 10){
            val = val % 10;
            carry = 1;
        }
        else{
            carry = 0;
        }
        retCur.val = val;
        
        if (cur1) cur1 = cur1.next;
        if (cur2) cur2 = cur2.next;
        if (cur1 || cur2 || carry) retCur = retCur.next = new ListNode(carry);
    }
    return ret;
};

function ListNode(val) {
    this.val = val;
    this.next = null;
}