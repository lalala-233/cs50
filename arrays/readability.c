#include "../cs50.h"
#include <ctype.h>
#include <stdio.h>

float get_grade(string text);
float calculate_index(int letters, int words, int sentences);
void assert(bool value, string info);
void tests(void);
int main(void) {
    tests();
    string text = get_string("Text: ");
    float grade = get_grade(text);
    if (grade < 1) {
        printf("Before Grade 1\n");
    } else if (grade > 16) {
        printf("Grade 16+\n");
    } else {
        printf("Grade %i\n", (int)(grade + 0.5));
    }
}
void assert(bool value, string info) {
    if (!value) {
        printf("%s", info);
    }
}
float get_grade(string text) {
    int words = 0;
    int letters = 0;
    int sentences = 0;
    bool last_is_whitespace = true;
    for (int i = 0;; i++) {
        char current = text[i];
        if (current == '\0') {
            break;
        }
        if (current == ' ') {
            last_is_whitespace = true;
        } else {
            if (last_is_whitespace) {
                words++;
            }
            last_is_whitespace = false;
            if (isupper(current) || islower(current)) {
                letters++;
            } else if (current == '.' || current == '!' || current == '?') {
                sentences++;
            }
        }
    }
    return calculate_index(letters, words, sentences);
}
float calculate_index(int letters, int words, int sentences) {
    const float COEFFICIENT_OF_LETTER = 0.0588;
    const float COEFFICIENT_OF_SENTENCE = -0.296;
    const float INTERCEPT = -15.8;
    float letters_per_100_words = 100.0 * letters / words;
    float sentences_per_100_words = 100.0 * sentences / words;
    return COEFFICIENT_OF_LETTER * letters_per_100_words +
           COEFFICIENT_OF_SENTENCE * sentences_per_100_words + INTERCEPT;
}
void tests(void) {
    assert((get_grade("One fish. Two fish. Red fish. Blue fish.") < 1),
           "Line ");
    assert(
        (int)(get_grade("Would you like them here or there? I would not like "
                        "them here or there. I would not like them anywhere.") +
              0.5) == 2,
        "Line ");
    assert((int)(get_grade("Congratulations! Today is your day. You're off to "
                           "Great Places! You're off and away!") +
                 0.5) == 3,
           "Line ");
    assert(
        (int)(get_grade(
                  "Harry Potter was a highly unusual boy in many ways. For one "
                  "thing, he hated the summer holidays more than any other "
                  "time of year. For another, he really wanted to do his "
                  "homework, but was forced to do it in secret, in the dead of "
                  "the night. And he also happened to be a wizard.") +
              0.5) == 5,
        "Line ");
    assert((int)(get_grade("In my younger and more vulnerable years my father "
                           "gave me some advice that I've been turning over in "
                           "my mind ever since.") +
                 0.5) == 7,
           "Line ");
    assert(
        (int)(get_grade("Alice was beginning to get very tired of sitting by "
                        "her sister on the bank, and of having nothing to do: "
                        "once or twice she had peeped into the book her sister "
                        "was reading, but it had no pictures or conversations "
                        "in it, \"and what is the use of a book,\" thought "
                        "Alice \"without pictures or conversation?\"") +
              0.5) == 8,
        "Line ");
    assert((int)(get_grade(
                     "When he was nearly thirteen, my brother Jem got his arm "
                     "badly broken at the elbow. When it healed, and Jem's "
                     "fears of never being able to play football were "
                     "assuaged, he was seldom self-conscious about his injury. "
                     "His left arm was somewhat shorter than his right; when "
                     "he stood or walked, the back of his hand was at right "
                     "angles to his body, his thumb parallel to his thigh.") +
                 0.5) == 8,
           "Line ");
    assert((int)(get_grade("There are more things in Heaven and Earth, "
                           "Horatio, than are dreamt of in your philosophy.") +
                 0.5) == 9,
           "Line ");
    assert((int)(get_grade(
                     "It was a bright cold day in April, and the clocks were "
                     "striking thirteen. Winston Smith, his chin nuzzled into "
                     "his breast in an effort to escape the vile wind, slipped "
                     "quickly through the glass doors of Victory Mansions, "
                     "though not quickly enough to prevent a swirl of gritty "
                     "dust from entering along with him.") +
                 0.5) == 10,
           "Line ");
    assert((get_grade(
                "A large class of computational problems involve the "
                "determination of properties of graphs, digraphs, integers, "
                "arrays of integers, finite families of finite sets, boolean "
                "formulas and elements of other countable domains.") > 16),
           "Line ");
}