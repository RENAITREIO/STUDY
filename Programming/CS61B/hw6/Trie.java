import java.util.HashMap;
import java.util.Map;

public class Trie {
    private Node root;

    public Trie() {
        this.root = new Node();
    }

    public void addString(String s) {
        Node p = root;
        int length = s.length();
        for (int i = 0; i < length; i++) {
            char c = Character.toLowerCase(s.charAt(i));
            if (!p.next.containsKey(c)) {
                p.next.put(c, new Node());
            }
            p = p.next.get(c);

            if (i == length - 1) {
                p.endState = true;
            }
        }
    }

    public Node getRoot() {
        return root;
    }


    public static class Node {
        private boolean endState;
        private Map<Character, Node> next;

        public Node() {
            this.endState = false;
            next = new HashMap<>();
        }

        public Map<Character, Node> getNext() {
            return this.next;
        }

        public boolean isEnd() {
            return endState;
        }
    }
}
