from cs50 import get_string
import re


def compute_index(text):
    letters_num = len(re.findall(r"[A-Za-z]", text))
    words_num = len(text.split())
    sentences_num = len(re.findall(r'[\.!?]', text))
    print(f"letters_num: {letters_num} words_num: {words_num} sentences_num: {sentences_num}")
    index = 0.0588 * letters_num / words_num * 100 - 0.296 * sentences_num / words_num * 100 - 15.8
    return index


text = get_string("Text: ")
index = compute_index(text)
grade = round(index)
print(index)
if index < 1.5:
    print("Before Grade 1")
elif index >= 15.5:
    print("Grade 16+")
else:
    print(f"Grade {grade}")
