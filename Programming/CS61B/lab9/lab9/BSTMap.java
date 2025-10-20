package lab9;

import java.util.HashSet;
import java.util.Iterator;
import java.util.Set;

/**
 * Implementation of interface Map61B with BST as core data structure.
 *
 * @author Your name here
 */
public class BSTMap<K extends Comparable<K>, V> implements Map61B<K, V> {

    private class Node {
        /* (K, V) pair stored in this Node. */
        private K key;
        private V value;

        /* Children of this Node. */
        private Node left;
        private Node right;

        private Node(K k, V v) {
            key = k;
            value = v;
        }
    }

    private Node root;  /* Root node of the tree. */
    private int size; /* The number of key-value pairs in the tree */

    /* Creates an empty BSTMap. */
    public BSTMap() {
        this.clear();
    }

    /* Removes all of the mappings from this map. */
    @Override
    public void clear() {
        root = null;
        size = 0;
    }

    /** Returns the value mapped to by KEY in the subtree rooted in P.
     *  or null if this map contains no mapping for the key.
     */
    private V getHelper(K key, Node p) {
        if (p == null) {
            return null;
        }
        int cmp = key.compareTo(p.key);
        if (cmp < 0) {
            return getHelper(key, p.left);
        } else if (cmp > 0) {
            return getHelper(key, p.right);
        } else {
            return p.value;
        }
    }

    /** Returns the value to which the specified key is mapped, or null if this
     *  map contains no mapping for the key.
     */
    @Override
    public V get(K key) {
        if (key == null) {
            return null;
        }

        return getHelper(key, root);
    }

    /** Returns a BSTMap rooted in p with (KEY, VALUE) added as a key-value mapping.
      * Or if p is null, it returns a one node BSTMap containing (KEY, VALUE).
     */
    private Node putHelper(K key, V value, Node p) {
        int cmp = key.compareTo(p.key);
        if (cmp < 0) {
            if (p.left == null) {
                this.size++;
                p.left = new Node(key, value);
                return p.left;
            } else {
                return putHelper(key, value, p.left);
            }
        } else if (cmp > 0) {
            if (p.right == null) {
                this.size++;
                p.right = new Node(key, value);
                return p.right;
            } else {
                return putHelper(key, value, p.right);
            }
        } else {
            p.value = value;
            return p;
        }
    }

    /** Inserts the key KEY
     *  If it is already present, updates value to be VALUE.
     */
    @Override
    public void put(K key, V value) {
        if (key == null) {
            return;
        }

        if (this.root == null) {
            root = new Node(key, value);
            this.size++;
            return;
        }
        putHelper(key, value, root);
    }

    /* Returns the number of key-value mappings in this map. */
    @Override
    public int size() {
        return this.size;
    }

    //////////////// EVERYTHING BELOW THIS LINE IS OPTIONAL ////////////////

    /* Returns a Set view of the keys contained in this map. */
    @Override
    public Set<K> keySet() {
        HashSet<K> res = new HashSet<>();
        keySetHelper(root, res);
        return res;
    }

    private void keySetHelper(Node p, Set<K> res) {
        if (p != null) {
            res.add(p.key);
            keySetHelper(p.left, res);
            keySetHelper(p.right, res);
        }
    }

    /** Removes KEY from the tree if present
     *  returns VALUE removed,
     *  null on failed removal.
     */
    @Override
    public V remove(K key) {
        V res = get(key);
        if (res != null) {
            deleteNode(key, root, root);
            size--;
        }
        return res;
    }

    private void deleteNode(K key, Node p, Node preNode) {
        int cmp = key.compareTo(p.key);
        if (cmp < 0) {
            deleteNode(key, p.left, p);
        } else if (cmp > 0) {
            deleteNode(key, p.right, p);
        } else {
            int cmpNode = key.compareTo(preNode.key);
            if (p.left == null && p.right == null) {
                if (cmpNode < 0) {
                    preNode.left = null;
                } else if (cmpNode > 0) {
                    preNode.right = null;
                } else {
                    if (key.equals(root.key)) {
                        root = null;
                    } else {
                        preNode = null;
                    }
                }
            } else if (p.left == null) {
                if (cmpNode < 0) {
                    preNode.left = p.right;
                } else if (cmpNode > 0) {
                    preNode.right = p.right;
                } else {
                    if (key.equals(root.key)) {
                        root = p.right;
                    } else {
                        preNode = p.right;
                    }
                }
            } else if (p.right == null) {
                if (cmpNode < 0) {
                    preNode.left = p.left;
                } else if (cmpNode > 0) {
                    preNode.right = p.left;
                } else {
                    if (key.equals(root.key)) {
                        root = p.left;
                    } else {
                        preNode = p.left;
                    }
                }
            } else {
                if (p.left.right == null) {
                    p.key = p.left.key;
                    p.value = p.left.value;
                    p.left = p.left.left;
                } else {
                    Node tmp = p.left;
                    Node preTmp = tmp;
                    while (tmp.right != null) {
                        preTmp = tmp;
                        tmp = tmp.right;
                    }
                    p.key = tmp.key;
                    p.value = tmp.value;
                    preTmp.right = null;
                }
            }
        }
    }

    /** Removes the key-value entry for the specified key only if it is
     *  currently mapped to the specified value.  Returns the VALUE removed,
     *  null on failed removal.
     **/
    @Override
    public V remove(K key, V value) {
        V val = get(key);
        if (val.equals(value)) {
            remove(key);
            return val;
        } else {
            return null;
        }
    }

    @Override
    public Iterator<K> iterator() {
        throw new UnsupportedOperationException();
    }
}
