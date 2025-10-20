public class LinkedListDeque<Item> implements Deque<Item> {
    private class DequeNode {
        private Item value;
        private DequeNode pre;
        private DequeNode next;

        public DequeNode() {
            this.value = null;
            this.pre = this;
            this.next = this;
        }

        public DequeNode(Item val, DequeNode pre, DequeNode next) {
            this.value = val;
            this.pre = pre;
            this.next = next;
        }
    }


    private DequeNode sentinel;
    private int size;

    public LinkedListDeque() {
        this.sentinel = new DequeNode();
        this.size = 0;
    }

    @Override
    public void addFirst(Item item) {
        DequeNode newNode = new DequeNode(item, sentinel, sentinel.next);
        sentinel.next.pre = newNode;
        sentinel.next = newNode;
        size++;
    }

    @Override
    public void addLast(Item item) {
        DequeNode newNode = new DequeNode(item, sentinel.pre, sentinel);
        sentinel.pre.next = newNode;
        sentinel.pre = newNode;
        size++;
    }

    @Override
    public boolean isEmpty() {
        return size == 0;
    }

    @Override
    public int size() {
        return size;
    }

    @Override
    public void printDeque() {
        DequeNode node = sentinel.next;
        while (node != sentinel) {
            System.out.print(node.value + " ");
            node = node.next;
        }
        System.out.println();

    }

    @Override
    public Item removeFirst() {
        Item res = sentinel.next.value;
        sentinel.next.next.pre = sentinel;
        sentinel.next = sentinel.next.next;
        if (size > 0) {
            size--;
        }
        return res;
    }

    @Override
    public Item removeLast() {
        Item res = sentinel.pre.value;
        sentinel.pre.pre.next = sentinel;
        sentinel.pre = sentinel.pre.pre;
        if (size > 0) {
            size--;
        }
        return res;
    }

    @Override
    public Item get(int index) {
        if (index > size - 1 || index < 0) {
            return null;
        }
        DequeNode node = sentinel.next;
        while (index > 0) {
            node = node.next;
            index--;
        }
        return node.value;
    }

    private Item getHelper(int index, DequeNode node) {
        if (index == 0) {
            return node.value;
        }
        return getHelper(index - 1, node.next);
    }

    public Item getRecursive(int index) {
        if (index > size - 1 || index < 0) {
            return null;
        }
        return getHelper(index, sentinel.next);
    }
}
