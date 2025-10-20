package hw3.hash;

import java.util.List;

public class OomageTestUtility {
    public static boolean haveNiceHashCodeSpread(List<Oomage> oomages, int M) {
        int[] bucket = new int[M];
        double min = (double) oomages.size() / 50;
        double max = (double) oomages.size() / 2.5;
        for (Oomage o: oomages) {
            int bucketNum = (o.hashCode() & 0x7FFFFFFF) % M;
            bucket[bucketNum]++;
        }

        for (int i = 0; i < M; i++) {
            if (bucket[i] > max || bucket[i] < min) {
                return false;
            }
        }
        return true;
    }
}
