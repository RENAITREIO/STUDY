import java.util.List;
import java.util.ArrayList;
import java.util.Map;
import java.util.HashMap;

public class HuffmanEncoder {
    public static Map<Character, Integer> buildFrequencyTable(char[] inputSymbols) {
        Map<Character, Integer> frequencyTable = new HashMap<>();
        for (char ch: inputSymbols) {
            if (!frequencyTable.containsKey(ch)) {
                frequencyTable.put(ch, 1);
            } else {
                frequencyTable.put(ch, frequencyTable.get(ch) + 1);
            }
        }
        return frequencyTable;
    }

    public static void main(String[] args) {
        char[] file = FileUtils.readFile(args[0]);
        Map<Character, Integer> frequencyTable = buildFrequencyTable(file);
        BinaryTrie huffTrie = new BinaryTrie(frequencyTable);

        ObjectWriter ow = new ObjectWriter(args[0] + ".huf");
        ow.writeObject(huffTrie);

        Map<Character, BitSequence> queryMap = huffTrie.buildLookupTable();

        List<BitSequence> list = new ArrayList<>();
        for (char ch: file) {
            list.add(queryMap.get(ch));
        }

        BitSequence encoded = BitSequence.assemble(list);

        ow.writeObject(encoded);
        ow.writeObject(file.length);
    }
}
