import static org.junit.Assert.*;
import static org.junit.Assert.assertEquals;

import org.junit.Test;

public class TestArrayDequeGold {
    @Test
    public void testDeque() {
        StudentArrayDeque<Integer> sad1 = new StudentArrayDeque<>();
        ArrayDequeSolution<Integer> sad2 = new ArrayDequeSolution<>();
        String message = "";

        for (int i = 0; i < 10; i += 1) {
            double numberBetweenZeroAndOne = StdRandom.uniform();

            if (numberBetweenZeroAndOne < 0.5) {
                sad1.addLast(i);
                sad2.addLast(i);
                message += "addLast(" + i + ")\n";
            } else {
                sad1.addFirst(i);
                sad2.addFirst(i);
                message += "addFirst(" + i + ")\n";
            }
        }

        for (int i = 0; i < 10; i += 1) {
            double numberBetweenZeroAndOne = StdRandom.uniform();

            if (numberBetweenZeroAndOne < 0.5) {
                Integer s1 = sad1.removeLast();
                Integer s2 = sad2.removeLast();
                message += "removeLast()\n";
                assertEquals(message, s1, s2);
            } else {
                Integer s1 = sad1.removeFirst();
                Integer s2 = sad2.removeFirst();
                message += "removeFirst()\n";
                assertEquals(message, s1, s2);
            }
        }
    }
}
