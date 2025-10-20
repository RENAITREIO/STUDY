package lab11.graphs;

import java.util.ArrayDeque;
import java.util.Queue;

/**
 *  @author Josh Hug
 */
public class MazeBreadthFirstPaths extends MazeExplorer {
    /* Inherits public fields:
    public int[] distTo;
    public int[] edgeTo;
    public boolean[] marked;
    */
    private int s;
    private int t;
    private boolean targetFound = false;

    public MazeBreadthFirstPaths(Maze m, int sourceX, int sourceY, int targetX, int targetY) {
        super(m);
        // Add more variables here!
        s = maze.xyTo1D(sourceX, sourceY);
        t = maze.xyTo1D(targetX, targetY);
        distTo[s] = 0;
        edgeTo[s] = s;
    }

    /** Conducts a breadth first search of the maze starting at the source. */
    private void bfs() {
        Queue<Integer> q = new ArrayDeque<>();
        q.add(s);

        while (!q.isEmpty()) {
            int v = q.remove();
            marked[v] = true;
            announce();
            if (v == t) {
                targetFound = true;
            }
            if (targetFound) {
                break;
            }

            for (int n: maze.adj(v)) {
                if (!marked[n] && !q.contains(n)) {
                    edgeTo[n] = v;
                    announce();
                    distTo[n] = distTo[v] + 1;
                    q.add(n);
                }
            }
        }
    }


    @Override
    public void solve() {
        bfs();
    }
}

