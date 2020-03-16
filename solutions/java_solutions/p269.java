import java.util.HashMap;
import java.util.HashSet;

public class p269 {
    // Alien Dictionary - Hard

    // There is a new alien language which uses the latin alphabet. However, the
    // order among letters are unknown to you. You receive a list of non-empty words
    // from the dictionary, where words are sorted lexicographically by the rules of
    // this new language. Derive the order of letters in this language.
    // You may assume all letters are in lowercase.
    // You may assume that if a is a prefix of b, then a must appear before b in the
    // given dictionary.
    // If the order is invalid, return an empty string.
    // There may be multiple valid order of letters, return any one of them is fine.
    class Solution {
        public String alienOrder(String[] words) {
            HashMap<Character, Node> graph = new HashMap<Character, Node>();

            for (int i = 0; i < words.length; i++) {
                String word = words[i];
                String lastWord = i > 0 ? words[i - 1] : null;

                for (int j = 0; j < word.length(); j++) {
                    char c = word.charAt(j);
                    Character boxed = new Character(c);
                    // make sure the current letter is in the graph
                    if (!graph.containsKey(boxed))
                        graph.put(boxed, new Node(c));

                    if (lastWord != null && lastWord.length() > j) {
                        String prefix = word.substring(0, j);
                        String lastPrefix = lastWord.substring(0, j);
                        char lastC = lastWord.charAt(j);
                        Character lastBoxed = new Character(lastC);
                        if (prefix.equals(lastPrefix) && !boxed.equals(lastBoxed)) {
                            graph.get(lastBoxed).children.add(graph.get(boxed));
                        }
                    }

                }
            }

            StringBuilder s = new StringBuilder(graph.size());
            try {
                for (Character key : graph.keySet()) {
                    Node n = graph.get(key);
                    visit(n, s);
                }
            } catch (Exception e) {
                System.out.println(e.getMessage());
                return "";
            }

            return s.reverse().toString();
        }

        public void visit(Node n, StringBuilder s) throws Exception {
            if (n.visited)
                return;
            if (n.visiting)
                throw new Exception("Cycle detected!");
            n.visiting = true;
            for (Node c : n.children)
                visit(c, s);
            n.visited = true;
            s.append(n.value);
        }
    }

    public class Node {
        public char value;
        public HashSet<Node> children;
        public boolean visited;
        public boolean visiting;

        public Node(char value) {
            this.value = value;
            children = new HashSet<Node>();
            visited = false;
            visiting = false;
        }
    }
}