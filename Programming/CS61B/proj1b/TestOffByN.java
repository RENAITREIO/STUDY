import org.junit.Test;
import static org.junit.Assert.*;

public class TestOffByN {
    @Test
    public void testOffByN() {
        OffByN offByN = new OffByN(3);
        assertTrue(offByN.equalChars('a', 'd'));
        assertTrue(offByN.equalChars('d', 'a'));
        assertFalse(offByN.equalChars('A', 'd'));
    }
}
