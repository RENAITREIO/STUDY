package lab11.graphs;

import java.util.HashMap;
import java.util.HashSet;
import java.util.PriorityQueue;
/**
 *  @author Josh Hug
 */
public class MazeAStarPath extends MazeExplorer {
    private int s;
    private int t;
    private boolean targetFound = false;
    private Maze maze;

    public MazeAStarPath(Maze m, int sourceX, int sourceY, int targetX, int targetY) {
        super(m);
        maze = m;
        s = maze.xyTo1D(sourceX, sourceY);
        t = maze.xyTo1D(targetX, targetY);
        distTo[s] = 0;
        edgeTo[s] = s;
    }

    /** Estimate of the distance from v to the target. */
    private int h(int v) {
        return -1;
    }

    /** Finds vertex estimated to be closest to target. */
    private int findMinimumUnmarked() {
        return -1;
        /* You do not have to use this method. */
    }

    /** Performs an A star search from vertex s. */
    private void astar(int s) {
        PriorityQueue<PQNode> opened = new PriorityQueue<>();
        HashSet<Integer> closed = new HashSet<>();
        HashMap<Integer, Integer> gVal = new HashMap<>();
        HashMap<Integer, PQNode> openMap = new HashMap<>();


        opened.add(new PQNode(s, 0));
        while (!opened.isEmpty()) {
            PQNode current = opened.poll();
            marked[current.id] = true;
            distTo[current.id] = current.sumCost;
            announce();
            if (current.id == t) {
                targetFound = true;
                break;
            }
            closed.add(current.id);
            for (int n: maze.adj(current.id)) {
                int cost = current.sumCost + 1;
                int gValue = gVal.getOrDefault(n, Integer.MAX_VALUE);
                if (openMap.containsKey(n) && cost < gValue) {
                    opened.remove(openMap.remove(n));
                }
                if (closed.contains(n) && cost < gValue) {
                    closed.remove(n);
                }
                if (!openMap.containsKey(n) && !closed.contains(n)) {
                    PQNode newNode = new PQNode(n, cost);
                    opened.add(newNode);
                    edgeTo[n] = current.id;
                    gVal.put(n, cost);
                    openMap.put(n, newNode);
                }
            }
        }
    }

    @Override
    public void solve() {
        astar(s);
    }

    private class PQNode implements Comparable<PQNode> {
        int id;
        int sumCost;

        public PQNode(int id, int cost) {
            this.id = id;
            this.sumCost = cost;
        }

        private int manhattan() {
            return Math.abs(maze.toX(this.id) - maze.toX(t))
                    + Math.abs(maze.toY(this.id) - maze.toY(t));
        }

        @Override
        public int compareTo(PQNode node) {
            return Double.compare(this.sumCost + this.manhattan(),
                    node.sumCost + node.manhattan());
        }

        @Override
        public boolean equals(Object obj) {
            if (obj.getClass() != this.getClass()) {
                return false;
            }
            return this.id == ((PQNode) obj).id;
        }

        @Override
        public int hashCode() {
            return Integer.hashCode(id);
        }
    }

}

