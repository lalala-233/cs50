text = input("Text: ")

letter_count = 0
sentence_count = 0
word_count = 0
for word in text.split(" "):
    word_count += 1
    for c in word:
        if c.isalpha():
            letter_count += 1
        elif c in (".", "?", "!"):
            sentence_count += 1

L = 100 * letter_count / word_count
S = 100 * sentence_count / word_count
index = 0.0588 * L - 0.296 * S - 15.8
index = round(index)

if index >= 16:
    print("Grade 16+")
elif index <= 1:
    print("Before Grade 1")
else:
    print(f"Grade {index}")
