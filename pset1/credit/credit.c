#include <stdio.h>

unsigned int* digitize(long long number, unsigned int length);
unsigned int number_length(long long number);

int main(int argc, char *argv[])
{
    digitize(12345, 5);
    return 0;
}


unsigned int* digitize(long long number, unsigned int length)
{
    unsigned int digits[length];

    for (unsigned int i = length - 1; i >= 0; i--)
    {
        printf("%i\n", i);
    }

    return 0;    // TODO: Finish later
}

/**
 * Function: number_length
 * Takes a number and returns its length. For example:
 * 12,345 would return a length of 5
 * 
 * Arguments:
 * long long number
 * 
 * Returns unsigned int
 */
unsigned int number_length(long long number)
{
    long long number_copy = number;
    
    // Handle negative number
    if (number_copy < 0)
    {
        number_copy *= -1;
    }

    unsigned int number_length = 0;

    while (number_copy > 0)
    {
        number_copy = (long long)number_copy / 10;
        number_length++;
    }

    return number_length;
}