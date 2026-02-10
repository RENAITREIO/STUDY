import org.junit.Test;

import static junit.framework.Assert.*;

public class TrieTester {
    @Test
    public void testAdd() {
        Trie t = new Trie();
        t.addString("AB");
        t.addString("a");

        Trie.Node p = t.getRoot();
        assertTrue(p.getNext().containsKey('a'));
        p = p.getNext().get('a');
        assertTrue(p.isEnd());
        assertTrue(p.getNext().containsKey('b'));
        p = p.getNext().get('b');
        assertTrue(p.isEnd());

        t.addString("ba");

        p = t.getRoot();
        assertTrue(p.getNext().containsKey('b'));
        p = p.getNext().get('b');
        assertTrue(p.getNext().containsKey('a'));
        p = p.getNext().get('a');
        assertTrue(p.isEnd());
    }
}
