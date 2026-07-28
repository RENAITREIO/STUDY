package lab11.graphs;

import java.util.HashMap;
import java.util.Map;

/**
 *  @author Josh Hug
 */
public class MazeCycles extends MazeExplorer {
    /* Inherits public fields:
    public int[] distTo;
    public int[] edgeTo;
    public boolean[] marked;
    */
    boolean circleFound = false;

    public MazeCycles(Maze m) {
        super(m);
    }

    @Override
    public void solve() {
        HashMap<Integer, Integer> map = new HashMap<>();
        distTo[0] = 0;
        dfs(0, map);
    }

    private void dfs(int v, Map map) {
        marked[v] = true;
        announce();

        for (int w : maze.adj(v)) {
            if (circleFound) {
                return;
            }
            if (!marked[w]) {
                map.put(w, v);
                distTo[w] = distTo[v] + 1;
                announce();
                dfs(w, map);
            } else {
                if (!map.get(v).equals(w)) {
                    addEdge(w, v, map);
                    circleFound = true;
                    return;
                }
            }
        }
    }

    private void addEdge(int v, int w, Map map) {
        edgeTo[w] = v;
        boolean found = false;
        int i = v;
        while (w != i) {
            int pre = (int) map.get(w);
            edgeTo[pre] = w;
            announce();
            while (map.containsKey(i)) {
                if (i == w) {
                    found = true;
                    break;
                }
                i = (int) map.get(i);
            }
            if (found) {
                break;
            }
            i = v;
            w = pre;
        }

        while (w != v) {
            int pre = (int) map.get(v);
            edgeTo[pre] = v;
            announce();
            v = pre;
        }
    }
}

