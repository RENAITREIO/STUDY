package hw4.puzzle;

import edu.princeton.cs.algs4.MinPQ;

import java.util.ArrayList;

public class Solver {
    private MinPQ<Node> pq;
    private int minMoves;
    private ArrayList<WorldState> solution;

    public Solver(WorldState initial) {
        // initialize
        pq = new MinPQ<>();
        solution = new ArrayList<>();
        pq.insert(new Node(initial));
        Node result = null;

        // begin to solve
        while (!pq.isEmpty()) {
            Node nowState = pq.delMin();
            if (nowState.ws.isGoal()) {
                result = nowState;
                break;
            }
            for (WorldState n: nowState.ws.neighbors()) {
                if (nowState.pre != null && n.equals(nowState.pre.ws)) {
                    continue;
                }
                pq.insert(new Node(n, nowState));
            }
        }

        ArrayList<WorldState> tmp = new ArrayList<>();
        while (result != null) {
            tmp.add(result.ws);
            result = result.pre;
        }
        for (int i = tmp.size() - 1; i >= 0; i--) {
            solution.add(tmp.get(i));
        }
        minMoves = solution.size() - 1;
    }

    public int moves() {
        return minMoves;
    }

    public Iterable<WorldState> solution() {
        return solution;
    }


    private class Node implements Comparable<Node> {
        private WorldState ws;
        private int steps;
        private Node pre;
        private int edtVal;

        public Node(WorldState ws) {
            this.ws = ws;
            this.steps = 0;
            this.pre = null;
            this.edtVal = ws.estimatedDistanceToGoal();
        }

        public Node(WorldState ws, Node pre) {
            this.ws = ws;
            this.pre = pre;
            this.steps = this.pre.steps + 1;
            this.edtVal = ws.estimatedDistanceToGoal();
        }

        @Override
        public int compareTo(Node node) {
            return Integer.compare(this.edtVal + this.steps,
                    node.edtVal + node.steps);
        }
    }
}
