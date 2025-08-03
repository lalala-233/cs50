#include "../cs50.h"
#include <ctype.h>
#include <stdio.h>

int get_score_from_string(string answer);
int get_score_from_char(char c);

int main(void) {
    string answer_1 = get_string("Player 1: ");
    string answer_2 = get_string("Player 2: ");
    int score_1 = get_score_from_string(answer_1);
    int score_2 = get_score_from_string(answer_2);
    if (score_1 > score_2) {
        printf("Player 1 wins!\n");
    } else if (score_2 > score_1) {
        printf("Player 2 wins!\n");
    } else {
        printf("Tie!\n");
    }
}
int get_score_from_char(char c) {
    const int TABLE[] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                         1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
    if (isupper(c)) {
        return TABLE[c - 'A'];
    } else if (islower(c)) {
        return TABLE[c - 'a'];
    }
    return 0;
}

int get_score_from_string(string answer) {
    int count = 0;
    int score = 0;
    while (answer[count] != '\0') {
        score += get_score_from_char(answer[count]);
        answer++;
    }
    return score;
}