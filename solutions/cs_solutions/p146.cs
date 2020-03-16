public class p146
{
    // LRU Cache - Medium

    // Design and implement a data structure for Least Recently Used (LRU) cache. 
    // It should support the following operations: get and put.
    // get(key) - Get the value (will always be positive) of the key if the 
    //  key exists in the cache, otherwise return -1.
    // put(key, value) - Set or insert the value if the key is not already present. 
    //  When the cache reached its capacity, it should invalidate the least 
    //  recently used item before inserting a new item.
    // The cache is initialized with a positive capacity.
    public class LRUCache
    {

        public LRUCache(int capacity)
        {
            Capacity = capacity;
        }

        public int Get(int key)
        {
            if (!Data.ContainsKey(key)) return -1;
            var record = Data[key];
            SetMostRecent(key);
            return record;
        }

        public void Put(int key, int value)
        {
            if (Data.ContainsKey(key)) Data[key] = value;
            else
            {
                if (Data.Count == Capacity)
                {
                    var oldest = LeastRecent();
                    if (oldest != null)
                    {
                        Data.Remove(oldest.Value);
                        Accesses.Remove(oldest.Value);
                    }
                }
                Data.Add(key, value);
            }
            SetMostRecent(key);
        }

        private void SetMostRecent(int key)
        {
            //Console.WriteLine("Before most recent: " + string.Join(",", Accesses));
            Accesses.Remove(key);
            Accesses.Add(key);
            //Console.WriteLine("After most recent: " + string.Join(",", Accesses));
        }

        private int? LeastRecent() => Accesses.Any() ? Accesses.First() : (int?)null;

        private int Capacity { get; set; }

        private List<int> Accesses { get; set; } = new List<int>();
        private Dictionary<int, int> Data { get; set; } = new Dictionary<int, int>();
    }
}