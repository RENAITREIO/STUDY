import static org.junit.Assert.*;
import org.junit.Test;

public class RadixSortTester {
    @Test
    public void testSort() {
        String[] s = new String[3];
        s[0] = "ab";
        s[1] = "abc";
        s[2] = "a";
        String[] expect = new String[3];
        expect[0] = "a";
        expect[1] = "ab";
        expect[2] = "abc";
        s = RadixSort.sort(s);
        assertEquals(expect, s);
    }
}
