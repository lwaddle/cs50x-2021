#include <cs50.h>
#include <stdio.h>

/**
 * Function: split_digits
 * Returns a pointer to an array of individual digits of the number
 * that was passed
 */
int split_digits(long long number, int length);

/**
 * Function: is_valid_cc_number
 * Returns 1 if card number is valid, 2 if invalid
 */
int is_valid_cc_number(long long card_number);

/**
 * Function: number_length
 * Returns the length of a number
 */
int number_length(long long number);

int main(void)
{
    // Define min and max credit card values
    long long cc_min = 1000000000000;
    long long cc_max = 9999999999999999;

    // Get credit card number from user
    long long credit_card_number;
    do
    {
        credit_card_number = get_long_long("Number: ");
    }
    while ((credit_card_number < cc_min) || (credit_card_number > cc_max));
    
    // Test function
    int n = is_valid_cc_number(credit_card_number);

    return 0;
}


int split_digits(long long number, int length)
{
    int digits[length];
    long long number_copy = number;

    for (int i = length - 1; i >= 0; i--)
    {
        digits[i] = number_copy % 10;
        number_copy = (long long)number_copy / 10;
    }

    return digits;
}

int is_valid_cc_number(long long card_number)
{
    return 0;    // TODO: Return the actual value
}

int number_length(long long number)
{
    int digit_count = 1;
    long long number_copy = number;

    while ((long long)number_copy / 10 > 0)
    {
        number_copy = (long long)number_copy / 10;
        digit_count++;
    }

    return digit_count;
}