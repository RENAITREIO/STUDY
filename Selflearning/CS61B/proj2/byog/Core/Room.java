package byog.Core;

import byog.TileEngine.TETile;
import byog.TileEngine.Tileset;
import static byog.Core.Game.WIDTH;
import static byog.Core.Game.HEIGHT;

import java.util.ArrayList;
import java.util.Random;

public class Room {
    public Point p;
    private int W;
    private int H;
    private ArrayList<Point> roomPoints;

    private static final int MAXWIDTH = 9;
    private static final int MAXHEIGHT = 9;
    private static final int MINWIDTH = 2;
    private static final int MINHEIGHT = 2;

    public Room(int x, int y, int W, int H) {
        this.p = new Point(x, y);
        this.W = W;
        this.H = H;
    }

    public static void createRandomRooms(ArrayList<Room> rooms, Random r, int roomsNum) {
        for (int i = 0; i < roomsNum; i++) {
            Room newRoom = Room.createARoom(r);
            for (int j = 0; j < rooms.size(); j++) {
                if (newRoom.isCover(rooms.get(j))) {
                    newRoom = Room.createARoom(r);
                    j = -1;
                }
            }
            rooms.add(newRoom);
        }
    }

    private static Room createARoom(Random r) {
        int x = RandomUtils.uniform(r, WIDTH);
        int y = RandomUtils.uniform(r, HEIGHT);
        int W = RandomUtils.uniform(r, MINWIDTH, MAXWIDTH);
        int H = RandomUtils.uniform(r, MINHEIGHT, MAXHEIGHT);
        if (x + W + 1 >= WIDTH) {
            W = -W;
        }
        if (y + H + 1 >= HEIGHT) {
            H = -H;
        }
        Room newRoom = new Room(x, y, W, H);
        newRoom.standardize();
        return newRoom;
    }

    private void standardize() {
        if (this.W < 0) {
            this.W = -this.W;
            this.p.x = this.p.x - this.W - 1;
        }
        if (this.H < 0) {
            this.H = -this.H;
            this.p.y = this.p.y - this.H - 1;
        }
    }

    private boolean isCover(Room room) {
        int thisEndX = this.p.x + this.W + 1;
        int thisEndY = this.p.y + this.H + 1;

        int roomBeginX = room.p.x;
        int roomEndX = room.p.x + room.W + 1;
        int roomBeginY = room.p.y;
        int roomEndY = room.p.y + room.H + 1;

        boolean flag1 = false;
        boolean flag2 = false;

        for (int i = this.p.x; i <= thisEndX; i++) {
            if (i >= roomBeginX && i <= roomEndX) {
                flag1 = true;
                break;
            }
        }

        for (int i = this.p.y; i <= thisEndY; i++) {
            if (i >= roomBeginY && i <= roomEndY) {
                flag2 = true;
                break;
            }
        }

        return flag1 && flag2;
    }

    public static void addRooms(TETile[][] worldFrame, ArrayList<Room> rooms) {
        for (Room room: rooms) {
            room.addRoom(worldFrame);
        }
    }

    public void addRoom(TETile[][] worldFrame) {
        int endX = this.p.x + this.W + 1;
        int endY = this.p.y + this.H + 1;

        for (int i = this.p.x; i <= endX; i++) {
            for (int j = this.p.y; j <= endY; j++) {
                if (i == this.p.x || i == endX || j == this.p.y || j == endY) {
                    worldFrame[i][j] = Tileset.WALL;
                } else {
                    worldFrame[i][j] = Tileset.FLOOR;
                }
            }
        }
    }

    public static Room getNearestRoom(ArrayList<Room> needLinked,
                                      ArrayList<Room> hadLinked,
                                      ArrayList<Hallway> hwList) {
        Room nearestNLR = needLinked.getFirst();
        Room nearestHLR = hadLinked.getFirst();
        double minDistance = nearestNLR.calculateDistance(nearestHLR);

        for (Room need: needLinked) {
            for (Room had: hadLinked) {
                Double distance = need.calculateDistance(had);
                if (minDistance > distance) {
                    nearestNLR = need;
                    nearestHLR = had;
                    minDistance = distance;
                }
            }
        }

        // calculate point and add to hwList
        double dx;
        double dy;
        int endX1 = nearestNLR.p.x + nearestNLR.W + 1;
        int endY1 = nearestNLR.p.y + nearestNLR.H + 1;
        int endX2 = nearestHLR.p.x + nearestHLR.W + 1;
        int endY2 = nearestHLR.p.y + nearestHLR.H + 1;

        int pX1 = nearestNLR.p.x;
        int pY1 = nearestNLR.p.y;
        int pX2 = nearestHLR.p.x;
        int pY2 = nearestHLR.p.y;

        for (int i = nearestNLR.p.x; i <= endX1; i++) {
            for (int j = nearestNLR.p.y; j <= endY1; j++) {
                if (i == nearestNLR.p.x || i == endX1 || j == nearestNLR.p.y || j == endY1) {
                    for (int k = nearestHLR.p.x; k <= endX2; k++) {
                        for (int l = nearestHLR.p.y; l <= endY2; l++) {
                            if (k == nearestHLR.p.x || k == endX2
                                    || l == nearestHLR.p.y || l == endY2) {
                                if (!(((i == nearestNLR.p.x || i == endX1)
                                        && (j == nearestNLR.p.y || j == endY1))
                                        || ((k == nearestHLR.p.x || k == endX2)
                                        && (l == nearestHLR.p.y || l == endY2)))) {
                                    dx = i - k;
                                    dy = j - l;
                                    double distance = Math.sqrt(dx * dx + dy * dy);
                                    if (distance < minDistance) {
                                        minDistance = distance;
                                        pX1 = i;
                                        pY1 = j;
                                        pX2 = k;
                                        pY2 = l;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        hwList.add(new Hallway(pX1, pY1, pX2, pY2));

        return nearestNLR;
    }

    private double calculateDistance(Room room) {
        double dx = this.p.x - room.p.x;
        double dy = this.p.y - room.p.y;
        return Math.sqrt(dx * dx + dy * dy);
    }
}
