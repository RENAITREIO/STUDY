import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.TreeSet;

public class Boggle {
    
    // File path of dictionary file
    static String dictPath = "words.txt";
    static char[] board;
    static Set<String> wordSet;
    static int width;
    static int height;

    /**
     * Solves a Boggle puzzle.
     * 
     * @param k The maximum number of words to return.
     * @param boardFilePath The file path to Boggle board file.
     * @return a list of words found in given Boggle board.
     *         The Strings are sorted in descending order of length.
     *         If multiple words have the same length,
     *         have them in ascending alphabetical order.
     */
    public static List<String> solve(int k, String boardFilePath) {
        if (k <= 0) {
            throw new IllegalArgumentException();
        }

        Trie dict = buildDict();
        board = buildBoard(boardFilePath);
        wordSet = new TreeSet<>((a, b) -> {
            if (a.length() != b.length()) {
                return Integer.compare(b.length(), a.length());
            }
            return a.compareTo(b);
        });

        Map<Character, Trie.Node> nodeMap = dict.getRoot().getNext();
        boolean[] marked = new boolean[width * height];
        for (int i = 0; i < board.length; i++) {
            char ch = board[i];
            StringBuffer sf = new StringBuffer();
            sf.append(ch);
            if (nodeMap.containsKey(ch)) {
                foundWords(nodeMap.get(ch), i, sf, marked);
            }
        }

        List<String> wordList = new ArrayList<>(wordSet);
        return wordList.size() <= k ? wordList : wordList.subList(0, k);
    }


    private static void foundWords(Trie.Node p, int idx,
                                   StringBuffer word, boolean[] marked) {
        if (p.isEnd()) {
            wordSet.add(word.toString());
        }

        Map<Character, Trie.Node> next = p.getNext();

        if (next.isEmpty()) {
            return;
        }

        marked[idx] = true;
        for (int neighbour: getNeighbour(idx)) {
            char ch = board[neighbour];
            if (next.containsKey(ch) && !marked[neighbour]) {
                word.append(ch);
                foundWords(next.get(ch), neighbour, word, marked);
                word.deleteCharAt(word.length() - 1);
            }
        }
        marked[idx] = false;
    }

    private static Iterable<Integer> getNeighbour(int idx) {
        ArrayList<Integer> res = new ArrayList<>();
        int x = idxToX(idx);
        int y = idxToY(idx);
        for (int i = y - 1; i <= y + 1; i++) {
            for (int j = x - 1; j <= x + 1; j++) {
                if (!(i == y && j == x)) {
                    int nIdx = xyToIdx(j, i);
                    if (nIdx >= 0) {
                        res.add(nIdx);
                    }
                }
            }
        }
        return res;
    }

    private static int idxToX(int idx) {
        return idx % width;
    }

    private static int idxToY(int idx) {
        return idx / width;
    }

    private static int xyToIdx(int x, int y) {
        return (x >= width || y >= height || x < 0 || y < 0) ? -1 : x + y * width;
    }

    private static Trie buildDict() {
        In dictIn = new In(dictPath);
        if (!dictIn.exists()) {
            throw new IllegalArgumentException();
        }

        Trie dict = new Trie();
        while (dictIn.hasNextLine()) {
            dict.addString(dictIn.readLine());
        }
        return dict;
    }

    private static char[] buildBoard(String boardFilePath) {
        In boardIn = new In(boardFilePath);
        String[] tmp = boardIn.readAllStrings();

        width = tmp[0].length();
        height = tmp.length;
        char[] res = new char[width * height];

        for (int i = 0; i < height; i++) {
            if (tmp[i].length() != width) {
                throw new IllegalArgumentException();
            }
            for (int j = 0; j < width; j++) {
                res[xyToIdx(j, i)] = tmp[i].charAt(j);
            }
        }
        return res;
    }

    public static void main(String[] args) {
        System.out.println(solve(7, "exampleBoard.txt"));
    }
}
