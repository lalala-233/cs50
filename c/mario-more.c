#include "cs50.h"
#include <stdio.h>

int get_nonnegative_int(void);
void print_times(int number, char c);

int main(void) {
    int n = get_nonnegative_int();
    for (int i = 1; i <= n; i++) {
        print_times(n - i, ' ');
        print_times(i, '#');
        printf(" ");
        print_times(i, '#');
        print_times(n - i, ' ');
        printf("\n");
    }
}

void print_times(int number, char c) {
    for (int i = 0; i < number; i++) {
        printf("%c", c);
    }
}

int get_nonnegative_int(void) {
    int n = 0;
    while (n <= 0) {
        n = get_int("Height: ");
    }
    return n;
}