public class p23
{
    // Merge k sorted lists - Hard

    // Merge k sorted linked lists and return it as one sorted list. 
    // Analyze and describe its complexity.

    public class Solution
    {
        public ListNode MergeKLists(ListNode[] lists)
        {
            if (lists.Length == 0) return null;
            if (lists.Length == 1) return lists[0];

            return DivideAndConquer(lists);
        }


        private ListNode DivideAndConquer(ListNode[] lists)
        {
            int last = lists.Length - 1;
            while (last > 0)
            {
                int i = 0;
                int j = last;
                //for 0,1,2,3,4,5,6,7: 
                //  merge 07 -> 0, 16 -> 1, 25 -> 2, 34 -> 3
                //  for 0123 merge 03 -> 0, 12 -> 1
                //  for 01 merge 01 -> 0 ==> 0 is everything
                //ergo - O(log(k))
                while (i < j)
                {
                    //O(N) -> overall O(Nlog(k))
                    lists[i] = MergeNodes(lists[i], lists[j]);
                    i++;
                    j--;
                    if (i >= j) last = j;
                }
            }
            return lists[0];
        }

        //O(length(a) + length(b)) ~~ O(N)
        private ListNode MergeNodes(ListNode a, ListNode b)
        {
            if (a == null) return b;
            if (b == null) return a;

            ListNode result;
            if (a.val <= b.val)
            {
                result = a;
                result.next = MergeNodes(a.next, b);
            }
            else
            {
                result = b;
                result.next = MergeNodes(a, b.next);
            }
            return result;
        }

        private ListNode BruteForce(ListNode[] lists)
        {
            //space - O(N) to hold the numbers in a list
            var items = new List<int>();

            //time - O(N), where N is number of nodes
            foreach (var list in lists)
            {
                if (list == null) continue;
                var current = list;
                items.Add(current.val);
                while (current.next != null)
                {
                    current = current.next;
                    items.Add(current.val);
                }
            }

            if (items.Count == 0) return null;

            //time - O(NlogN) to sort
            items = items.OrderBy(n => n).ToList();

            //time - O(N) to dump items back onto a linked list
            //space - O(N) again to hold the items in a linked list again
            var returnNode = new ListNode(items[0]);
            var current2 = returnNode;
            for (int i = 1; i < items.Count; i++)
            {
                current2.next = new ListNode(items[i]);
                current2 = current2.next;
            }

            //overall NlogN
            return returnNode;
        }
    }

    public class ListNode
    {
        public int val;
        public ListNode next;
        public ListNode(int x) { val = x; }
    }
}