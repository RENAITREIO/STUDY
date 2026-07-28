package byog.lab5;
import org.junit.Test;
import static org.junit.Assert.*;

import byog.TileEngine.TERenderer;
import byog.TileEngine.TETile;
import byog.TileEngine.Tileset;

import java.util.Random;

/**
 * Draws a world consisting of hexagonal regions.
 */
public class HexWorld {
    public static class Position {
        private int x;
        private int y;

        public Position(int x, int y) {
            this.x = x;
            this.y = y;
        }
    }

    private static void addHexagon(TETile[][] world, Position p, int size, TETile tile) {
        for (int i = 0; i < size; i++) {
            for (int j = size - i; j < size; j++) {
                world[j - 1 + p.x][i + p.y] = tile;
            }

            for (int j = 0; j < size; j++) {
                world[j + size - 1 + p.x][i + p.y] = tile;
            }

            for (int j = size - i; j < size; j++) {
                world[j + i + size - 1  + p.x][i + p.y] = tile;
            }
        }

        for (int i = 0; i < size; i++) {
            for (int j = i + 1; j < size; j++) {
                world[j - 1 + p.x][i + size + p.y] = tile;
            }

            for (int j = 0; j < size; j++) {
                world[j + size - 1 + p.x][i + size + p.y] = tile;
            }

            for (int j = i + 1; j < size; j++) {
                world[j - i + 2 * size - 2 + p.x][i + size + p.y] = tile;
            }
        }
    }

    public static void createHexagonWorld(TETile[][] world, int size, TERenderer ter) {
        Position[] flowerP = new Position[3];
        flowerP[0] = new Position(5, 3);
        flowerP[1] = new Position(15, 21);
        flowerP[2] = new Position(20, 18);
        for (Position p: flowerP) {
            addHexagon(world, p, size, Tileset.FLOWER);
        }

        Position[] grassP = new Position[3];
        grassP[0] = new Position(0, 6);
        grassP[1] = new Position(0, 12);
        grassP[2] = new Position(5, 21);
        for (Position p: grassP) {
            addHexagon(world, p, size, Tileset.GRASS);
        }

        Position[] treeP = new Position[3];
        treeP[0] = new Position(15, 9);
        treeP[1] = new Position(20, 12);
        treeP[2] = new Position(10, 24);
        for (Position p: treeP) {
            addHexagon(world, p, size, Tileset.TREE);
        }

        Position[] sendP = new Position[2];
        sendP[0] = new Position(15, 15);
        sendP[1] = new Position(20, 6);
        for (Position p: sendP) {
            addHexagon(world, p, size, Tileset.SAND);
        }

        Position[] mountainP = new Position[8];
        mountainP[0] = new Position(10, 0);
        mountainP[1] = new Position(10, 6);
        mountainP[2] = new Position(10, 12);
        mountainP[3] = new Position(10, 18);
        mountainP[4] = new Position(15, 3);
        mountainP[5] = new Position(5, 9);
        mountainP[6] = new Position(5, 15);
        mountainP[7] = new Position(0, 18);
        for (Position p: mountainP) {
            addHexagon(world, p, size, Tileset.MOUNTAIN);
        }

        ter.renderFrame(world);
    }

    public static void main(String[] args) {
        int width = 27;
        int height = 30;
        TERenderer ter = new TERenderer();
        ter.initialize(width, height);
        TETile[][] world = new TETile[width][height];
        Position p = new Position(0, 0);

        for (int x = 0; x <width; x += 1) {
            for (int y = 0; y <height; y += 1) {
                world[x][y] = Tileset.NOTHING;
            }
        }

        createHexagonWorld(world, 3, ter);
    }
}
