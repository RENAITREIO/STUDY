package hw2;

import edu.princeton.cs.algs4.WeightedQuickUnionUF;

import static org.junit.Assert.*;

public class Percolation {
    private static final int BLOCKED = 0;
    private static final int OPEN = 1;

    private int[][] grid;
    private WeightedQuickUnionUF sites;
    private WeightedQuickUnionUF fullSites;
    private int nOfOpenSites;
    private final int N;


    // create N-by-N grid, with all sites initially blocked
    public Percolation(int N) {
        if (N <= 0) {
            throw new java.lang.IllegalArgumentException();
        }

        this.sites = new WeightedQuickUnionUF(N * N + 2);
        this.fullSites = new WeightedQuickUnionUF(N * N + 1);
        this.grid = new int[N][N];
        this.nOfOpenSites = 0;
        this.N = N;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                this.grid[i][j] = BLOCKED;
            }
        }
    }

    // open the site (row, col) if it is not open already
    public void open(int row, int col) {
        checkBounds(row, col);

        if (isOpen(row, col)) {
            return;
        }

        this.grid[col][row] = OPEN;
        nOfOpenSites++;
        unionSite(row, col);
    }

    // is the site (row, col) open?
    public boolean isOpen(int row, int col) {
        checkBounds(row, col);
        return this.grid[col][row] == OPEN;
    }

    // is the site (row, col) full?
    public boolean isFull(int row, int col) {
        checkBounds(row, col);
        return fullSites.connected(gridToIdx(row, col), N * N);
    }

    // number of open sites
    public int numberOfOpenSites() {
        return this.nOfOpenSites;
    }

    // does the system percolate?
    public boolean percolates() {
        return sites.connected(N * N, N * N + 1);
    }


    private int gridToIdx(int row, int col) {
        return row * N + col;
    }

    private void checkBounds(int row, int col) {
        if (row < 0 || row >= N || col < 0 || col >= N) {
            throw new java.lang.IndexOutOfBoundsException();
        }
    }

    private void unionSite(int row, int col) {
        if (row == 0) {
            sites.union(gridToIdx(row, col), N * N);
            fullSites.union(gridToIdx(row, col), N * N);
        }
        if (row == N - 1) {
            sites.union(gridToIdx(row, col), N * N + 1);
        }

        int i = row - 1;
        int j = col;
        if (i >= 0 && isOpen(i, j)) {
            sites.union(gridToIdx(row, col), gridToIdx(i, j));
            fullSites.union(gridToIdx(row, col), gridToIdx(i, j));
        }

        i = row;
        j = col - 1;
        if (j >= 0 && isOpen(i, j)) {
            sites.union(gridToIdx(row, col), gridToIdx(i, j));
            fullSites.union(gridToIdx(row, col), gridToIdx(i, j));
        }

        i = row;
        j = col + 1;
        if (j < N && isOpen(i, j)) {
            sites.union(gridToIdx(row, col), gridToIdx(i, j));
            fullSites.union(gridToIdx(row, col), gridToIdx(i, j));
        }

        i = row + 1;
        j = col;
        if (i < N && isOpen(i, j)) {
            sites.union(gridToIdx(row, col), gridToIdx(i, j));
            fullSites.union(gridToIdx(row, col), gridToIdx(i, j));
        }
    }

    // use for unit testing (not required)
    public static void main(String[] args) {
        int N = 4;
        Percolation p = new Percolation(N);
        for (int i = 0; i < N; i++) {
            p.open(i, 1);
        }
        assertTrue(p.percolates());
    }
}
