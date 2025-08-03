#include "../cs50.h"
#include <stdio.h>

bool is_valid_checksum(long number);
bool is_master_card(long number);
bool is_visa_card(long number);
bool is_american_express_card(long number);
bool starts_with(long number, int digit);
void assert(bool value, string info);
int length(long number);

int main(void) {
    assert(starts_with(114514, 1), "starts with 1 digit");
    assert(starts_with(114514, 11), "starts with 2 digit");
    assert(starts_with(114514, 114), "starts with 3 digit");
    assert(length(114514) == 6, "length");
    assert(is_valid_checksum(4003600000000014), "checksum");

    long card_number = get_long("Number: ");
    if (is_valid_checksum(card_number)) {
        if (is_master_card(card_number)) {
            printf("MASTERCARD\n");
        } else if (is_american_express_card(card_number)) {
            printf("AMEX\n");
        } else if (is_visa_card(card_number)) {
            printf("VISA\n");
        } else {
            printf("INVALID\n");
        }
    } else {
        printf("INVALID\n");
    }
}
bool is_visa_card(long number) {
    if (starts_with(number, 4)) {
        if (length(number) == 16 || length(number) == 13) {
            return true;
        }
    }
    return false;
}
bool is_american_express_card(long number) {
    if (starts_with(number, 34) || starts_with(number, 37)) {
        if (length(number) == 15) {
            return true;
        }
    }
    return false;
}
int length(long number) {
    int length = 0;
    for (long i = 1; i < number; i *= 10) {
        length++;
    }
    return length;
}
bool is_master_card(long number) {
    if (starts_with(number, 51) || starts_with(number, 52) ||
        starts_with(number, 53) || starts_with(number, 54) ||
        starts_with(number, 55)) {
        if (length(number) == 16) {
            return true;
        }
    }
    return false;
}
void assert(bool value, string info) {
    if (!value) {
        printf("failed: %s\n", info);
    }
}
bool starts_with(long number, int digit) {
    bool starts_with = false;
    for (long i = 1; i < number; i *= 10) {
        if (number / i == digit) {
            starts_with = true;
        }
    }
    return starts_with;
}
bool is_valid_checksum(long number) {
    int odd_sum = 0;
    int even_sum = 0;
    for (int i = 0; i < 8; i++) // credit card must be 13, 15 or 16-digit number
    {
        odd_sum += number % 10;
        number /= 10;
        int even_number = ((number % 10) * 2);
        even_sum += even_number / 10;
        even_sum += even_number % 10;
        number /= 10;
    }
    int last_digit = (odd_sum + even_sum) % 10;
    return last_digit == 0;
}