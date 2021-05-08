#include <cs50.h>
#include <stdio.h>

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

int is_valid_cc_number(long long card_number)
{   
    // Put the card number into an array so each digit
    // can be accessed easily
    int length = number_length(card_number);
    int digits[length];
    long long card_number_copy = card_number;

    for (int i = length - 1; i >= 0; i--)
    {
        digits[i] = card_number_copy % 10;
        card_number_copy = (long long)card_number_copy / 10;
    }

    // Split the digits into 2 sets as required by Luhn’s Algorithm
    // The first set is the digits that will be multiplied by 2
    // The second set is the remaining digits
    
    // First set:
    int set1[10];                      // Buffer of 10, will not always be full
    card_number_copy = card_number;    // Reset card_number_copy
    








    

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