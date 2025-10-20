package byog.lab6;

import edu.princeton.cs.introcs.StdDraw;

import java.awt.Color;
import java.awt.Font;
import java.util.Random;
import java.util.TreeMap;

public class MemoryGame {
    private int width;
    private int height;
    private int round;
    private Random rand;
    private boolean gameOver;
    private boolean playerTurn;
    private static final char[] CHARACTERS = "abcdefghijklmnopqrstuvwxyz".toCharArray();
    private static final String[] ENCOURAGEMENT = {"You can do this!", "I believe in you!",
                                                   "You got this!", "You're a star!", "Go Bears!",
                                                   "Too easy for you!", "Wow, so impressive!"};

    public static void main(String[] args) throws InterruptedException {
        if (args.length < 1) {
            System.out.println("Please enter a seed");
            return;
        }

        int seed = Integer.parseInt(args[0]);
        MemoryGame game = new MemoryGame(40, 40, seed);
        game.startGame();
    }

    public MemoryGame(int width, int height, int seed) {
        /* Sets up StdDraw so that it has a width by height grid of 16 by 16 squares as its canvas
         * Also sets up the scale so the top left is (0,0) and the bottom right is (width, height)
         */
        this.width = width;
        this.height = height;
        StdDraw.setCanvasSize(this.width * 16, this.height * 16);
        Font font = new Font("Monaco", Font.BOLD, 30);
        StdDraw.setFont(font);
        StdDraw.setXscale(0, this.width);
        StdDraw.setYscale(0, this.height);
        StdDraw.clear(Color.BLACK);
        StdDraw.enableDoubleBuffering();

        this.rand = new Random(seed);
        round = 0;
        gameOver = false;
        playerTurn = false;
    }

    public String generateRandomString(int n) {
        String res = "";
        int length = CHARACTERS.length;
        while (n > 0) {
            res += CHARACTERS[rand.nextInt(length)];
            n--;
        }
        return res;
    }

    public void drawFrame(String s) {
        StdDraw.clear();

        Font font = new Font("Monaco", Font.PLAIN, 25);
        StdDraw.setFont(font);
        if (playerTurn) {
            StdDraw.text((double) width / 2, height - 1, "Type!");
        } else {
            StdDraw.text((double) width / 2, height - 1, "Watch!");
        }

        StdDraw.textRight(width, height - 1, ENCOURAGEMENT[0]);
        StdDraw.textLeft(0, height - 1, "Round: " + round);
        StdDraw.line((double) 0, height - 2, width, height - 2);

        font = new Font("Monaco", Font.BOLD, 30);
        StdDraw.setFont(font);
        StdDraw.text((double) width / 2, (double) height / 2, s);
        StdDraw.show();
    }

    public void flashSequence(String letters) throws InterruptedException {
        int length = letters.length();
        for (int i = 0; i < length; i++) {
            String letter = "" + letters.charAt(i);
            Thread.sleep(500);
            drawFrame(letter);
            Thread.sleep(1000);
            drawFrame("");
        }
    }

    public String solicitNCharsInput(int n) throws InterruptedException {
        String s = "";
        while (n > 0) {
            while (!StdDraw.hasNextKeyTyped()) {
                drawFrame(s + "|");
            };
            s += StdDraw.nextKeyTyped();
            drawFrame(s);
            n--;
        }
        Thread.sleep(500);
        return s;
    }

    public void startGame() throws InterruptedException {
        while (!gameOver) {
            playerTurn = false;
            round++;
            drawFrame("Round: " + round + " Good luck!");
            Thread.sleep(500);
            String ans = generateRandomString(round);
            flashSequence(ans);
            playerTurn = true;
            String input = solicitNCharsInput(round);
            if (!ans.equals(input)) {
                gameOver = true;
            } else {
                drawFrame("Right!");
                Thread.sleep(1000);
            }
        }
        drawFrame("Game Over! You made it to round:" + round);
    }
}
