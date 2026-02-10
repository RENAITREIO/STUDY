public class ArrayDeque<T> {
    private T[] arr;
    private int size;
    private int firstIndex;
    private final int initalLength = 8;
    private final int limitLength = 16;

    public ArrayDeque() {
        arr = (T[]) new Object[initalLength];
        size = 0;
        firstIndex = 0;
    }

    private void extendArr() {
        T[] newArr = (T[]) new Object[arr.length * 2];
        System.arraycopy(arr, firstIndex, newArr, 0, arr.length - firstIndex);
        if (firstIndex != 0) {
            System.arraycopy(arr, 0, newArr, arr.length - firstIndex, firstIndex);
            firstIndex = 0;
        }
        arr = newArr;
    }

    public void addFirst(T item) {
        if (arr.length == size) {
            extendArr();
        }
        firstIndex = (firstIndex - 1 + arr.length) % arr.length;
        arr[firstIndex] = item;
        size++;
    }

    public void addLast(T item) {
        if (arr.length == size) {
            extendArr();
        }
        arr[(firstIndex + size) % arr.length] = item;
        size++;
    }

    public boolean isEmpty() {
        return size == 0;
    }

    public int size() {
        return size;
    }

    public void printDeque() {
        int end = firstIndex + size;
        for (int i = firstIndex; i < Math.min(end, arr.length); i++) {
            System.out.print(arr[i] + " ");
        }
        if (end > arr.length) {
            end = end % arr.length;
            for (int i = 0; i < end; i++) {
                System.out.print(arr[i] + " ");
            }
        }
        System.out.println();
    }

    private void contractArr() {
        T[] newArr = (T[]) new Object[arr.length / 2];
        int newFirstLength = Math.min(size, arr.length - firstIndex);
        System.arraycopy(arr, firstIndex, newArr, 0, newFirstLength);
        if (newFirstLength != size) {
            System.arraycopy(arr, 0, newArr, newFirstLength, size - arr.length + firstIndex);
        }
        firstIndex = 0;
        arr = newArr;
    }

    public T removeFirst() {
        if (size == 0) {
            return null;
        }
        if (arr.length >= limitLength) {
            double factor = (double) (size - 1) / arr.length;
            if (factor < 0.25) {
                contractArr();
            }
        }
        T res = arr[firstIndex];
        arr[firstIndex] = null;
        firstIndex = (firstIndex + 1) % arr.length;
        size--;
        return res;
    }

    public T removeLast() {
        if (size == 0) {
            return null;
        }
        if (arr.length >= limitLength) {
            double factor = (double) (size - 1) / arr.length;
            if (factor < 0.25) {
                contractArr();
            }
        }
        int toRemove = (firstIndex + size - 1) % arr.length;
        T res = arr[toRemove];
        arr[toRemove] = null;
        size--;
        return res;
    }

    public T get(int index) {
        if (index > size - 1 || index < 0) {
            return null;
        }
        return arr[(index + firstIndex) % arr.length];
    }
}
