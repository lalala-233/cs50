#include "cs50.h"
#include <stdio.h>

int get_nonnegative_int(string info);

int main(void) {
    int change = get_nonnegative_int("Change owed: ");
    int coin_count = 0;
    while (change != 0) {
        if (change >= 25) {
            change -= 25;
        } else if (change >= 10) {
            change -= 10;
        } else if (change >= 5) {
            change -= 5;
        } else {
            change -= 1;
        }
        coin_count++;
    }
    printf("%i\n", coin_count);
}

int get_nonnegative_int(string info) {
    int n = -1;
    while (n < 0) {
        n = get_int("%s", info);
    }
    return n;
}