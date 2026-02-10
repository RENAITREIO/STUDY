package hw2;

import edu.princeton.cs.introcs.StdStats;
import edu.princeton.cs.introcs.StdRandom;

public class PercolationStats {
    private double[] valArr;

    // perform T independent experiments on an N-by-N grid
    public PercolationStats(int N, int T, PercolationFactory pf) {
        if (N <= 0 || T <= 0) {
            throw new java.lang.IllegalArgumentException();
        }
        valArr = new double[T];
        for (int i = 0; i < T; i++) {
            Percolation perc = pf.make(N);
            int col;
            int row;

            while (true) {
                do {
                    col = StdRandom.uniform(0, N);
                    row = StdRandom.uniform(0, N);
                } while (perc.isOpen(row, col));

                perc.open(row, col);

                if (perc.percolates()) {
                    break;
                }
            }
            valArr[i] = (double) perc.numberOfOpenSites() / (N * N);
        }
    }

    // sample mean of percolation threshold
    public double mean() {
        return StdStats.mean(valArr);
    }

    // sample standard deviation of percolation threshold
    public double stddev() {
        return StdStats.stddev(valArr);
    }

    // low endpoint of 95% confidence interval
    public double confidenceLow() {
        return mean() - 1.96 * stddev() / Math.sqrt(valArr.length);
    }

    // high endpoint of 95% confidence interval
    public double confidenceHigh() {
        return mean() + 1.96 * stddev() / Math.sqrt(valArr.length);
    }
}
