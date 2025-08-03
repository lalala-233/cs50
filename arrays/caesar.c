#include "../cs50.h"
#include <ctype.h>
#include <stdio.h>

int parse_positive_int(string s);
void print_ciphertext(string plaintext, int key);
const int ERROR_CODE = -1;

int main(int argc, string argv[]) {
    if (argc != 2) {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }
    int key = parse_positive_int(argv[1]);
    if (key == ERROR_CODE) {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }
    string plaintext = get_string("plaintext:  ");
    print_ciphertext(plaintext, key);
}
void print_ciphertext(string plaintext, int key) {
    printf("ciphertext: ");
    for (int i = 0; plaintext[i] != '\0'; i++) {
        char current = plaintext[i];
        if (isupper(current)) {
            current = (current - 'A' + key) % 26 + 'A';
        } else if (islower(current)) {
            current = (current - 'a' + key) % 26 + 'a';
        }
        printf("%c", current);
    }
    printf("\n");
}

int parse_positive_int(string s) {
    int integer = 0;
    for (int i = 0; s[i] != 0; i++) {
        char current = s[i];
        if (isdigit(current)) {
            // I can assume that if it is digit, it will always be a digit.
            integer *= 10;
            integer += current - '0';
        } else {
            return ERROR_CODE;
        }
    }
    return integer;
}
