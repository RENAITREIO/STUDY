public class Palindrome {
    public Deque<Character> wordToDeque(String word) {
        int length = word.length();
        LinkedListDeque<Character> res = new LinkedListDeque<>();
        for (int i = 0; i < length; i++) {
            res.addLast(word.charAt(i));
        }
        return res;
    }

    private boolean isPalindromeHelper(Deque d) {
        if (d.size() < 2) {
            return true;
        }
        if (d.removeFirst() != d.removeLast()) {
            return false;
        } else {
            return isPalindromeHelper(d);
        }
    }

    public boolean isPalindrome(String word) {
        return isPalindromeHelper(wordToDeque(word));
    }

    private boolean isPalindromeHelper(Deque d, CharacterComparator cc) {
        if (d.size() < 2) {
            return true;
        }
        char first = (char) d.removeFirst();
        char last = (char) d.removeLast();
        if (!cc.equalChars(first, last)) {
            return false;
        } else {
            return isPalindromeHelper(d, cc);
        }
    }

    public boolean isPalindrome(String word, CharacterComparator cc) {
        return isPalindromeHelper(wordToDeque(word), cc);
    }
}
