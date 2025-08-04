#include "../cs50.h"
#include <ctype.h>
#include <stdio.h>

bool is_invalid_key(string key);
void print_ciphertext(string plaintext, string key);

int main(int argc, string argv[]) {
    if (argc != 2) {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    } else if (is_invalid_key(argv[1])) {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    string plaintext = get_string("plaintext:  ");
    print_ciphertext(plaintext, argv[1]);
}
void print_ciphertext(string plaintext, string key) {
    printf("ciphertext: ");
    for (int i = 0; plaintext[i] != '\0'; i++) {
        char current = plaintext[i];
        if (isupper(current)) {
            current = toupper(key[current - 'A']);
        } else if (islower(current)) {
            current = tolower(key[current - 'a']);
        }
        printf("%c", current);
    }
    printf("\n");
}
bool is_invalid_key(string key) {
    bool lower_count[26] = {false};
    bool upper_count[26] = {false};
    for (int i = 0;; i++) {
        char current = key[i];
        if (current == '\0') {
            if (i == 26) {
                break;
            }
            return true;
        }
        if (islower(current)) {
            if (lower_count[current - 'a'] == false) {
                lower_count[current - 'a'] = true;
            } else {
                return true;
            }
        } else if (isupper(current)) {
            if (upper_count[current - 'A'] == false) {
                upper_count[current - 'A'] = true;
            } else {
                return true;
            }
        } else {
            return true;
        }
    }
    return false;
}
