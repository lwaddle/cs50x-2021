#include <cs50.h>
#include <stdio.h>

void           drop_last_digit(long long *n);
unsigned short first_digit(long long n);
unsigned short first_two_digits(long long n);
long long      get_card_number(void);
short          is_valid_cc_number(long long n);
unsigned short last_digit(long long n);
unsigned short number_length(long long n);
short          prefix_is_amex(long long n);
short          prefix_is_mastercard(long long n);
short          prefix_is_visa(long long n);
void           print_card_type(long long n);
unsigned short sum_of_digits(long long n);

int main(int argc, char *argv[])
{
    print_card_type(get_card_number());

    return 0;
}


/**
 * Function: drop_last_digit
 * drops the last digit of n
 * 
 * Arguments:
 * long long *n
 * 
 * Returns void
 */
void drop_last_digit(long long *n)
{
    *n = (long long)*n / 10;
}

/**
 * Function: first_digit
 * 
 * Arguments:
 * long long n
 * 
 * Returns the first digit of n. Example: if n = 12345, the function
 * will return 1.
 */
unsigned short first_digit(long long n)
{
    // Handle negative n
    if (n < 0)
    {
        n *= -1;
    }

    // Handle single digit input
    if (number_length(n) == 1)
    {
        return (long long)n;
    }

    n = first_two_digits(n);

    return (long long)n / 10;
}

/**
 * Function: first_two_digits
 * 
 * Arguments:
 * long long n
 * 
 * Returns the first two digits of n. Example: if n = 12345, the function
 * will return 12.
 */
unsigned short first_two_digits(long long n)
{
    // Handle negative n
    if (n < 0)
    {
        n *= -1;
    }

    // Handle 2 digit input
    if (number_length(n) == 2)
    {
        return (unsigned short)n;
    }

    unsigned short length = number_length(n);
    for (int i = length - 1; i > 1; i--)
    {
        n = (long long)n / 10;
    }

    return (unsigned short)n;
}

/**
 * Function: get_card_number
 * 
 * Arguments: void
 * 
 * Returns and acceptable cc number as entered by the user
 */
long long get_card_number(void)
{
    long long n = get_long_long("Number: ");

    return n;
}

/**
 * Function: is_valid_cc_number
 * 
 * Arguments:
 * long long n
 * 
 * Returns 1 if the checksum algorithm confirms a valid card number.
 */
short is_valid_cc_number(long long n)
{
    /**
     * Luhn’s Algorithm
     * So what’s the secret formula? Well, most cards use an algorithm
     * invented by Hans Peter Luhn of IBM. According to Luhn’s algorithm, you
     * can determine if a credit card number is (syntactically) valid as
     * follows:
     *   
     * 1. Multiply every other digit by 2, starting with the number’s
     *    second-to-last digit, and then add those products’ digits together.
     * 2. Add the sum to the sum of the digits that weren’t multiplied by 2.
     * 3. If the total’s last digit is 0 (or, put more formally, if the total
     *    modulo 10 is congruent to 0), the number is valid!
     * 
     * American Express uses 15-digit numbers, MasterCard uses 16-digit
     * numbers, and Visa uses 13- and 16-digit numbers.
     * 
     * All American Express numbers start with 34 or 37; most MasterCard
     * numbers start with 51, 52, 53, 54, or 55 (they also have some other
     * potential starting numbers which we won’t concern ourselves with for
     * this problem); and all Visa numbers start with 4.
     */

    long long n_copy = n;
    unsigned short length = number_length(n);
    unsigned int sum_of_product_digits = 0;
    int is_valid_cc_number = 0;    // int used as bool.

    // Perform Luhn's Algorithm step 1
    for (int i = length - 1; i >= 0; i--)
    {
        if (number_length(n_copy) == 1)
        {
            break;
        }
        drop_last_digit(&n_copy);

        unsigned short digit = last_digit(n_copy);
        digit *= 2;

        sum_of_product_digits += sum_of_digits(digit);

        if (number_length(n_copy) > 1)
        {
            drop_last_digit(&n_copy);
        }
        else
        {
            break;
        }
    }

    // Reset n_copy back to the full cc number
    n_copy = n;
    length = number_length(n);

    // Perform Luhn's Algorithm step 2
    if (number_length(n_copy) > 1)
    {
        for (int i = length - 1; i >= 0; i--)
        {
            sum_of_product_digits += last_digit(n_copy);
            drop_last_digit(&n_copy);

            if (number_length(n_copy > 1))
            {
                drop_last_digit(&n_copy);
            }
            else
            {
                break;
            }
        }
    }
        
    if (sum_of_product_digits % 10 == 0)    // Valid card number
    {
        is_valid_cc_number = 1;
    }

    
    return is_valid_cc_number;
}

/**
 * Function: last_digit
 * 
 * Arguments:
 * long long n
 * 
 * Returns the last digit of n
 */
unsigned short last_digit(long long n)
{
    return n % 10;
}

/**
 * Function: number_length
 * Takes a number and returns its length. For example:
 * 12,345 would return a length of 5
 * 
 * Arguments:
 * long long number
 * 
 * Returns the length of n
 */
unsigned short number_length(long long n)
{    
    // Handle negative n
    if (n < 0)
    {
        n *= -1;
    }

    unsigned short number_length = 0;

    while (n > 0)
    {
        n = (long long)n / 10;
        number_length++;
    }

    return number_length;
}

/**
 * Function: prefix_is_amex
 * 
 * Arguments:
 * long long n
 * 
 * Returns 1 if the card appears to be Amex
 */
short prefix_is_amex(long long n)
{
    short is_amex = 0;

    unsigned short first_two = first_two_digits(n);
    if ((number_length(n) == 15) && ((first_two == 34) || (first_two == 37)))
    {
        is_amex = 1;
    }
    return is_amex;
}

/**
 * Function: prefix_is_mastercard
 * 
 * Arguments:
 * long long n
 * 
 * Returns 1 if the card appears to be MasterCard
 */
short prefix_is_mastercard(long long n)
{
    short is_mastercard = 0;

    unsigned short first_two = first_two_digits(n);
    if ((number_length(n) == 16) && (first_two == 51 || first_two == 52 || first_two == 53 || first_two == 54 || first_two == 55))
    {
        is_mastercard = 1;
    }

    return is_mastercard;
}

/**
 * Function: prefix_is_visa
 * 
 * Arguments:
 * long long n
 * 
 * Returns 1 if the card appears to be Visa
 */
short prefix_is_visa(long long n)
{
    short is_visa = 0;

    unsigned short first = first_digit(n);
    unsigned short length = number_length(n);

    if ((length == 13 || length == 16) && (first == 4))
    {
        is_visa = 1;
    }

    return is_visa;
}

/**
 * Function: print_card_type
 * 
 * Arguments: long long n
 * 
 * Returns void. Prints the card type
 */
void print_card_type(long long n)
{
    char *amex = "AMEX\n";
    char *invalid = "INVALID\n";
    char *mastercard = "MASTERCARD\n";
    char *visa = "VISA\n";

    if (is_valid_cc_number(n))
    {
        if (prefix_is_amex(n))
        {
            printf("%s", amex);
            return;
        }

        if (prefix_is_mastercard(n))
        {
            printf("%s", mastercard);
            return;
        }

        if (prefix_is_visa(n))
        {
            printf("%s", visa);
            return;
        }

        printf("INVALID\n");
        return;
    }
    else
    {
        printf("%s", invalid);
    }
}

/**
 * Function: sum_of_digits
 * 
 * Arguments:
 * n
 * 
 * Returns the sum of each individial digit of n
 */
unsigned short sum_of_digits(long long n)
{
    // Handle negative n
    if (n < 0)
    {
        n *= -1;
    }
    
    unsigned short sum_of_digits = 0;

    while (n > 0)
    {
        sum_of_digits += last_digit(n);
        n = (long long)n / 10;
    }

    return sum_of_digits;
}