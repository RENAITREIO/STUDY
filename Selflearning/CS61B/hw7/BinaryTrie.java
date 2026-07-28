import java.io.Serializable;
import java.util.HashMap;
import java.util.Map;
import java.util.PriorityQueue;
import java.util.Queue;

public class BinaryTrie implements Serializable {
    private Node root;

    public BinaryTrie(Map<Character, Integer> frequencyTable) {
        Queue<Node> pq = new PriorityQueue<>();
        for (char ch: frequencyTable.keySet()) {
            pq.add(new Node(ch, frequencyTable.get(ch), null, null));
        }

        while (pq.size() > 1) {
            Node left = pq.poll();
            Node right = pq.poll();
            pq.add(new Node('\0', left.freq + right.freq, left, right));
        }

        root = pq.poll();
    }

    public Match longestPrefixMatch(BitSequence querySequence) {
        Node p = root;
        StringBuilder seq = new StringBuilder();
        for (int i = 0; i < querySequence.length(); i++) {
            if (p == null) {
                return null;
            }
            int bit = querySequence.bitAt(i);
            seq.append(bit);
            if (bit == 0) {
                p = p.left;
            } else {
                p = p.right;
            }
            if (p.isLeaf()) {
                return new Match(new BitSequence(seq.toString()), p.ch);
            }
        }
        return null;
    }

    public Map<Character, BitSequence> buildLookupTable() {
        Map<Character, BitSequence> res = new HashMap<Character, BitSequence>();
        exploreTrie(root, res, new StringBuilder());
        return res;
    }

    private void exploreTrie(Node p, Map<Character, BitSequence> map, StringBuilder bits) {
        if (p == null) {
            return;
        }
        if (p.isLeaf()) {
            map.put(p.ch, new BitSequence(bits.toString()));
            return;
        }

        bits.append(0);
        exploreTrie(p.left, map, bits);
        bits.deleteCharAt(bits.length() - 1);

        bits.append(1);
        exploreTrie(p.right, map, bits);
        bits.deleteCharAt(bits.length() - 1);
    }




    private static class Node implements Comparable<Node>, Serializable {
        private final char ch;
        private final int freq;
        // left: 0, right: 1
        private final Node left, right;

        Node(char ch, int freq, Node left, Node right) {
            this.ch    = ch;
            this.freq  = freq;
            this.left  = left;
            this.right = right;
        }

        // is the node a leaf node?
        private boolean isLeaf() {
            assert ((left == null) && (right == null)) || ((left != null) && (right != null));
            return (left == null) && (right == null);
        }

        // compare, based on frequency
        public int compareTo(Node that) {
            return this.freq - that.freq;
        }
    }
}
