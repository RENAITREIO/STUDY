package byog.Core;

import byog.TileEngine.TETile;
import byog.TileEngine.Tileset;

import java.util.ArrayList;
import java.util.Random;
import static byog.Core.Game.WIDTH;
import static byog.Core.Game.HEIGHT;

public class Hallway {
    private Point p1;
    private Point p2;
    private ArrayList<Point> path;

    public Hallway(int x1, int y1, int x2, int y2) {
        this.p1 = new Point(x1, y1);
        this.p2 = new Point(x2, y2);
        path = new ArrayList<>();
    }

    public void connect(TETile[][] worldFrame, Random r) {
        int dx = p2.x - p1.x;
        int dy = p2.y - p1.y;

        if (dx > 0) {
            for (int i = p1.x; i <= p2.x; i++) {
                path.add(new Point(i, p1.y));
            }
        } else {
            for (int i = p1.x; i >= p2.x; i--) {
                path.add(new Point(i, p1.y));
            }
        }
        if (dy > 0) {
            for (int i = p1.y; i <= p2.y; i++) {
                path.add(new Point(p2.x, i));
            }
        } else {
            for (int i = p1.y; i >= p2.y; i--) {
                path.add(new Point(p2.x, i));
            }
        }

        for (Point p: path) {
            worldFrame[p.x][p.y] = Tileset.FLOOR;
        }

        for (Point p: path) {
            int x = p.x;
            int y = p.y;

            for (int i = x - 1; i <= x + 1; i++) {
                for (int j = y - 1; j <= y + 1; j++) {
                    if (i >= 0 && i < WIDTH && j >= 0 && j < HEIGHT) {
                        if (worldFrame[i][j].equals(Tileset.NOTHING)) {
                            worldFrame[i][j] = Tileset.WALL;
                        }
                    }
                }
            }
        }
    }
}
