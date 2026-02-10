package byog.Core;

import byog.TileEngine.TERenderer;
import byog.TileEngine.TETile;
import byog.TileEngine.Tileset;
import edu.princeton.cs.introcs.StdDraw;

import java.awt.Font;
import java.awt.Color;

import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.FileOutputStream;
import java.io.FileInputStream;
import java.io.IOException;

import java.util.ArrayList;
import java.util.Random;

public class Game {
    transient TERenderer ter = new TERenderer();
    /* Feel free to change the width and height. */
    public static final int WIDTH = 80;
    public static final int HEIGHT = 30;
    World world;

    /**
     * Method used for playing a fresh game. The game should start from the main menu.
     */
    public void playWithKeyboard() {
        StdDraw.setCanvasSize(WIDTH * 16, HEIGHT * 16);
        Font font = new Font("Monaco", Font.BOLD, 30);
        StdDraw.setFont(font);
        StdDraw.setXscale(0, WIDTH);
        StdDraw.setYscale(0, HEIGHT);
        StdDraw.clear(Color.WHITE);
        StdDraw.enableDoubleBuffering();

        int mode = 0;

        while (true) {
            switch (mode) {
                case 0:
                    startMenu();
                    char t = getInput();
                    if (t == 'n') {
                        mode = 1;
                    } else if (t == 'l') {
                        mode = 3;
                    }
                    break;
                case 1:
                    String seed = new String("");
                    char buffer = 0;
                    while (buffer != 's') {
                        StdDraw.clear();
                        StdDraw.text((double) WIDTH / 2, (double) HEIGHT / 2, "Seed: " + seed);
                        StdDraw.show();

                        buffer = getInput();
                        if (Character.isDigit(buffer)) {
                            seed += buffer;
                        }

                    }
                    playWithInputString("n" + seed + "s");

                    mode = 2;
                    break;
                case 2:
                    char command = getInput();
                    if (command == ':') {
                        char quit = getInput();
                        if (quit == 'q') {
                            saveWorld();
                            mode = 0;
                        }
                        break;
                    }
                    executeCommand(command);
                    ter.renderFrame(world.finalWorldFrame);
                    break;
                case 3:
                    if (playWithInputString("l") != null) {
                        mode = 2;
                    } else {
                        mode = 0;
                    }
                    break;
                default:
                    break;
            }
        }
    }

    private void startMenu() {
        Font font = new Font("Monaco", Font.BOLD, 30);
        StdDraw.setFont(font);
        StdDraw.clear();
        StdDraw.text((double) WIDTH / 2, (double) HEIGHT / 3 * 2, "Start(N)");
        StdDraw.text((double) WIDTH / 2, (double) HEIGHT / 3, "Load(L)");
        StdDraw.show();
    }

    private char getInput() {
        while (!StdDraw.hasNextKeyTyped());
        return StdDraw.nextKeyTyped();
    }

    private void saveWorld() {
        try {
            ObjectOutputStream out =
                    new ObjectOutputStream(new FileOutputStream("savedWorld.txt"));
            out.writeObject(this.world);
            out.close();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }


    /**
     * Method used for autograding and testing the game code. The input string will be a series
     * of characters (for example, "n123sswwdasdassadwas", "n123sss:q", "lwww". The game should
     * behave exactly as if the user typed these characters into the game after playing
     * playWithKeyboard. If the string ends in ":q", the same world should be returned as if the
     * string did not end with q. For example "n123sss" and "n123sss:q" should return the same
     * world. However, the behavior is slightly different. After playing with "n123sss:q", the game
     * should save, and thus if we then called playWithInputString with the string "l", we'd expect
     * to get the exact same world back again, since this corresponds to loading the saved game.
     * @param input the input string to feed to your program
     * @return the 2D TETile[][] representing the state of the world
     */
    public TETile[][] playWithInputString(String input) {
        world = new World();

        if (input.charAt(0) == 'n') {
            int sIndex = -1;
            for (int i = 1; i < input.length(); i++) {
                if (input.charAt(i) == 's') {
                    sIndex = i;
                    break;
                }
            }

            String seedStr = input.substring(1, sIndex);
            long seed = Long.parseLong(seedStr);
            world.r = new Random(seed);

            initEnv();
            input = input.substring(sIndex + 1);
        } else if (input.charAt(0) == 'l') {
            try {
                ObjectInputStream in = new ObjectInputStream(new FileInputStream("savedWorld.txt"));
                World tmp = (World) in.readObject();
                world.finalWorldFrame = tmp.finalWorldFrame;
                world.r = tmp.r;
                world.player = tmp.player;
            } catch (IOException | ClassNotFoundException e) {
                return null;
            }
            input = input.substring(1);
        }

        while (true) {
            if (input.isEmpty()) {
                break;
            } else if (input.charAt(0) == ':') {
                if (input.charAt(1) == 'q') {
                    saveWorld();
                    break;
                }
            } else {
                executeCommand(input.charAt(0));
                input = input.substring(1);
            }
        }

        // for easy test
        ter.initialize(WIDTH, HEIGHT);
        ter.renderFrame(world.finalWorldFrame);

        return world.finalWorldFrame;
    }

    public void initEnv() {
        final int minRoom = 20;
        final int maxRoom = 30;

        world.finalWorldFrame = new TETile[WIDTH][HEIGHT];
        for (int i = 0; i < WIDTH; i++) {
            for (int j = 0; j < HEIGHT; j++) {
                world.finalWorldFrame[i][j] = Tileset.NOTHING;
            }
        }

        // create rooms to world
        int roomsNum = RandomUtils.uniform(world.r, minRoom, maxRoom);
        ArrayList<Room> rooms = new ArrayList<>();
        Room.createRandomRooms(rooms, world.r, roomsNum);
        Room.addRooms(world.finalWorldFrame, rooms);

        ArrayList<Room> linkedRooms = new ArrayList<>();
        linkedRooms.add(rooms.removeFirst());
        ArrayList<Hallway> hwList = new ArrayList<>();

        while (!rooms.isEmpty()) {
            Room toBeLinked = Room.getNearestRoom(rooms, linkedRooms, hwList);
            linkedRooms.add(toBeLinked);
            rooms.remove(toBeLinked);
        }

        for (Hallway hw: hwList) {
            hw.connect(world.finalWorldFrame, world.r);
        }


        // add special points
        int idx = world.r.nextInt(WIDTH + HEIGHT);
        int idxP = world.r.nextInt(WIDTH + HEIGHT);
        for (int i = 1; i < WIDTH - 1; i++) {
            for (int j = 1; j < HEIGHT - 1; j++) {
                if (world.finalWorldFrame[i][j].equals(Tileset.WALL)) {
                    if (idx == 0 && ((world.finalWorldFrame[i - 1][j].equals(Tileset.FLOOR)
                            || world.finalWorldFrame[i + 1][j].equals(Tileset.FLOOR)
                            || world.finalWorldFrame[i][j - 1].equals(Tileset.FLOOR)
                            || world.finalWorldFrame[i][j + 1].equals(Tileset.FLOOR))
                            && (world.finalWorldFrame[i - 1][j].equals(Tileset.NOTHING)
                            || world.finalWorldFrame[i + 1][j].equals(Tileset.NOTHING)
                            || world.finalWorldFrame[i][j - 1].equals(Tileset.NOTHING)
                            || world.finalWorldFrame[i][j + 1].equals(Tileset.NOTHING)))) {
                        world.finalWorldFrame[i][j] = Tileset.LOCKED_DOOR;
                    }
                    idx--;
                }

                if (world.finalWorldFrame[i][j].equals(Tileset.FLOOR)) {
                    if (idxP == 0) {
                        world.finalWorldFrame[i][j] = Tileset.PLAYER;
                        world.player = new Point(i, j);
                    }
                    idxP--;
                }
            }
        }
    }

    public void executeCommand(char command) {
        int x = world.player.x;
        int y = world.player.y;
        switch (command) {
            case 'w':
                y += 1;
                break;
            case 's':
                y -= 1;
                break;
            case 'a':
                x -= 1;
                break;
            case 'd':
                x += 1;
                break;
            default:
                break;
        }
        if (world.finalWorldFrame[x][y].equals(Tileset.FLOOR)) {
            world.finalWorldFrame[world.player.x][world.player.y] = Tileset.FLOOR;
            world.finalWorldFrame[x][y] = Tileset.PLAYER;
            world.player.x = x;
            world.player.y = y;
        }
    }
}
