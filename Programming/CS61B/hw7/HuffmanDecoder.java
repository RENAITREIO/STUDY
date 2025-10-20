public class HuffmanDecoder {
    public static void main(String[] args) {
        ObjectReader or = new ObjectReader(args[0]);
        String fileName = args[1];

        Object x = or.readObject();
        Object y = or.readObject();
        Object z = or.readObject();

        BinaryTrie bt = (BinaryTrie) x;
        BitSequence bs = (BitSequence) y;
        int length = (Integer) z;
        char[] file = new char[length];

        for (int i = 0; i < length; i++) {
            Match m = bt.longestPrefixMatch(bs);
            bs = bs.allButFirstNBits(m.getSequence().length());
            file[i] = m.getSymbol();
        }

        FileUtils.writeCharArray(fileName, file);
    }
}
