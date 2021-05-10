#include <cs50.h>
#include <math.h>
#include <stdio.h>

// Define constants
const unsigned short QUARTER = 25;
const unsigned short DIME    = 10;
const unsigned short NICKEL  = 5;
const unsigned short PENNY   = 1;

double             get_change_owed(void);
unsigned long long get_min_coins(double change_owed);

int main(void)
{
    printf("%llu\n", get_min_coins(get_change_owed()));
}

/**
 * Gets the change owed from the user as a double. Returns a double
 */
double get_change_owed(void)
{
    double change_owed;
    do
    {
        change_owed = get_double("Change owed: ");
    }
    while (change_owed < 0);    // Don't allow negatives

    return change_owed;
}

/**
 * Takes the change owed as a double and returns minimum amount of coins
 * required to make up the total. This assumes the use of unlimited quarters,
 * dimes, nickels, and pennies.
 */
unsigned long long get_min_coins(double n)
{
    // Handle negative
    if (n < 0)
    {
        n *= -1;
    }

    // Convert change_owed to pennies and make long long
    unsigned long long change_owed = (long long)(round(n * 100));
    
    unsigned long long min_coins = 0;

    while (change_owed >= QUARTER)
    {
        change_owed -= QUARTER;
        min_coins++;
    }
    
    while (change_owed >= DIME)
    {
        change_owed -= DIME;
        min_coins++;
    }

    while (change_owed >= NICKEL)
    {
        change_owed -= NICKEL;
        min_coins++;
    }

    while (change_owed >= PENNY)
    {
        change_owed -= PENNY;
        min_coins++;
    }

    return min_coins;
}