package byog.Core;

import byog.TileEngine.TETile;

import java.io.Serializable;
import java.util.Random;

public class World implements Serializable {
    private static final long serialVersionUID = 1L;
    public Random r;
    public Point player;
    public TETile[][] finalWorldFrame;
}
