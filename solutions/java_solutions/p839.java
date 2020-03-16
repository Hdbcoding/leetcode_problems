import java.util.Arrays;

public class p839 {
    // Similar String Groups - Hard

    // Two strings X and Y are similar if we can swap two letters (in different
    // positions) of X, so that it equals Y. Also two strings X and Y are similar if
    // they are equal.

    // For example, "tars" and "rats" are similar (swapping at positions 0 and 2),
    // and "rats" and "arts" are similar, but "star" is not similar to "tars",
    // "rats", or "arts".

    // Together, these form two connected groups by similarity: {"tars", "rats",
    // "arts"} and {"star"}. Notice that "tars" and "arts" are in the same group
    // even though they are not similar. Formally, each group is such that a word is
    // in the group if and only if it is similar to at least one other word in the
    // group.

    // We are given a list A of strings. Every string in A is an anagram of every
    // other string in A. How many groups are there?

    class Solution {
        public int numSimilarGroups(String[] A) {
            UnionFind set = new UnionFind(A.length);

            for (int i = 0; i < A.length; i++) {
                for (int j = i + 1; j < A.length; j++) {
                    if (areSimilar(A[i], A[j]))
                        set.union(i, j);
                }
            }

            return set.s;
        }

        boolean areSimilar(String a, String b) {
            int missed = 0;

            for (int i = 0; i < a.length(); i++)
                if (a.charAt(i) != b.charAt(i))
                    if (++missed == 3)
                        return false;

            return true;
        }

        class UnionFind {
            int[] p;
            int[] r;
            int s;

            UnionFind(int s) {
                this.s = s;
                r = new int[s];
                Arrays.fill(r, 1);
                p = new int[s];
                for (int i = 0; i < s; i++)
                    p[i] = i;
            }

            int find(int u) {
                if (p[u] != u)
                    p[u] = find(p[u]);
                return p[u];
            }

            void union(int u, int v) {
                u = find(u);
                v = find(v);
                if (u == v)
                    return;
                s--;
                if (r[u] > r[v]) {
                    setParent(u, v);
                } else {
                    setParent(v, u);
                    if (r[u] == r[v])
                        r[v]++;
                }
            }

            void setParent(int u, int v) {
                p[v] = u;
            }
        }
    }
}