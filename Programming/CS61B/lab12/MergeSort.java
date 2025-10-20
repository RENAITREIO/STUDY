import edu.princeton.cs.algs4.Queue;
import edu.princeton.cs.algs4.StdRandom;

public class MergeSort {
    /**
     * Removes and returns the smallest item that is in q1 or q2.
     *
     * The method assumes that both q1 and q2 are in sorted order, with the smallest item first. At
     * most one of q1 or q2 can be empty (but both cannot be empty).
     *
     * @param   q1  A Queue in sorted order from least to greatest.
     * @param   q2  A Queue in sorted order from least to greatest.
     * @return      The smallest item that is in q1 or q2.
     */
    private static <Item extends Comparable> Item getMin(
            Queue<Item> q1, Queue<Item> q2) {
        if (q1.isEmpty()) {
            return q2.dequeue();
        } else if (q2.isEmpty()) {
            return q1.dequeue();
        } else {
            // Peek at the minimum item in each queue (which will be at the front, since the
            // queues are sorted) to determine which is smaller.
            Comparable q1Min = q1.peek();
            Comparable q2Min = q2.peek();
            if (q1Min.compareTo(q2Min) <= 0) {
                // Make sure to call dequeue, so that the minimum item gets removed.
                return q1.dequeue();
            } else {
                return q2.dequeue();
            }
        }
    }

    /** Returns a queue of queues that each contain one item from items. */
    private static <Item extends Comparable> Queue<Queue<Item>>
            makeSingleItemQueues(Queue<Item> items) {
        Queue<Queue<Item>> res = new Queue<>();
        for (Item item: items) {
            Queue<Item> singleItem = new Queue<>();
            singleItem.enqueue(item);
            res.enqueue(singleItem);
        }
        return res;
    }

    /**
     * Returns a new queue that contains the items in q1 and q2 in sorted order.
     *
     * This method should take time linear in the total number of items in q1 and q2.  After
     * running this method, q1 and q2 will be empty, and all of their items will be in the
     * returned queue.
     *
     * @param   q1  A Queue in sorted order from least to greatest.
     * @param   q2  A Queue in sorted order from least to greatest.
     * @return      A Queue containing all of the q1 and q2 in sorted order, from least to
     *              greatest.
     *
     */
    private static <Item extends Comparable> Queue<Item> mergeSortedQueues(
            Queue<Item> q1, Queue<Item> q2) {
        Queue<Item> sortedQ = new Queue<>();
        while (!q1.isEmpty() || !q2.isEmpty()) {
            if (q1.isEmpty()) {
                sortedQ.enqueue(q2.dequeue());
            } else if (q2.isEmpty()) {
                sortedQ.enqueue(q1.dequeue());
            } else {
                int cmp = q1.peek().compareTo(q2.peek());
                if (cmp < 0) {
                    sortedQ.enqueue(q1.dequeue());
                } else if (cmp > 0) {
                    sortedQ.enqueue(q2.dequeue());
                } else {
                    sortedQ.enqueue(q1.dequeue());
                    sortedQ.enqueue(q2.dequeue());
                }
            }
        }
        return sortedQ;
    }

    /** Returns a Queue that contains the given items sorted from least to greatest. */
    public static <Item extends Comparable> Queue<Item> mergeSort(
            Queue<Item> items) {
        Queue<Queue<Item>> singleItemQueues = makeSingleItemQueues(items);
        if (singleItemQueues.isEmpty()) {
            return new Queue<>();
        } else if (singleItemQueues.size() == 1) {
            return singleItemQueues.dequeue();
        }

        Queue<Item> left = new Queue<>();
        Queue<Item> right = new Queue<>();
        int size = singleItemQueues.size() / 2;
        for (int i = 0; i < size; i++) {
            left.enqueue(singleItemQueues.dequeue().dequeue());
        }
        while (!singleItemQueues.isEmpty()) {
            right.enqueue(singleItemQueues.dequeue().dequeue());
        }

        left = mergeSort(left);
        right = mergeSort(right);

        return mergeSortedQueues(left, right);
    }


    public static void main(String[] args) {
        Queue<Integer> q = new Queue<>();
        for (int i = 10000; i > 0; i--) {
            q.enqueue(StdRandom.uniform(10000));
        }

        System.out.println("Sorted:  " + MergeSort.mergeSort(q));
        System.out.println("Initial: " + q);
    }
}
