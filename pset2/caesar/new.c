#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void encipher(char *plaintext, int key);
int  get_alphabetical_index(char c);
int  get_valid_key(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    // Get key
    int key = get_valid_key(argc, argv);
    if (key == -1)    // Invalid CL arg
    {
        return 1;
    }

    // Get plaintext
    char *plaintext = get_string("plaintext: ");

    // Encipher and print output
    encipher(plaintext, key);

    return 0;
}

/**
 * This function enciphers (encrypts?) plaintext by offsetting the plaintext
 * by 'key' positions. For example: plaintext 'ABC' with a key of 1 would
 * equal 'BCD'. 'Z' with a key of 2 would equal 'B'. If the key ofsets the
 * character over the boundaries of the English alphabet, they overflow back
 * to the 0 index. The function also prints the output.
 */
void encipher(char *plaintext, int key)
{
    /**
     * The algorithm (i.e., cipher) encrypts messages by “rotating” each
     * letter by k positions. More formally, if p is some plaintext
     * (i.e., an unencrypted message), p sub i is the ith character in p, and
     * k is a secret key (i.e., a non-negative integer), then each letter,
     * c sub i, in the ciphertext, c, is computed as:
     * 
     * c sub i = (p sub i + k) % 26
     */

    const char ALPHABET[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
                             'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
                             'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    
    int plaintext_length = strlen(plaintext);

    printf("ciphertext: ");

    for (int i = 0; i < plaintext_length; i++)
    {
        if (isalpha(plaintext[i]))
        {
            // Handle upper/lower case events
            if (isupper(plaintext[i]))    // Uppercase detected
            {
                int alphabetical_index = get_alphabetical_index(plaintext[i]);
                int cipher_index = (get_alphabetical_index(plaintext[i]) + key) % 26;
                printf("%c", ALPHABET[cipher_index]);
            }
            else                          // Lowercase detected
            {
                int alphabetical_index = get_alphabetical_index(plaintext[i]);
                int cipher_index = (get_alphabetical_index(plaintext[i]) + key) % 26;
                printf("%c", tolower(ALPHABET[cipher_index]));
            }
        }
        else                              // Not alpha
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");

    return;
}

/**
 * Returns the alphabetical index of a character. For example: 'A' is index
 * 0, 'B' is index 1, and 'Z' is index 25. If the function is supplied
 * anything other than an English alphabet character, it will return an error
 * code of -1.
 */
int get_alphabetical_index(char c)
{
    const char ALPHABET[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
                             'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
                             'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    
    int index = -1;

    for (int i = 0; i < 26; i++)
    {
        if (toupper(c) == ALPHABET[i])
        {
            index = i;
        }
    }

    // Error handling
    if (index == -1)
    {
        fprintf(stderr, "Error -1. Index out of English alphabet range.\n");
        return index;
    }

    return index;
}

/**
 * Returns the key from the user's command line argument. In the event that
 * the argument is invalid, it will display a message providing instructions.
 * An invalid argument will return a value of -1.
 */
int get_valid_key(int argc, char *argv[])
{
    // Standard error message
    char *error_message = "Usage: ./caesar key";

    // Start by assuming the user's argument is valid
    int valid_argument = 1;

    // Did the user actually provide an argument?
    if (argc != 2)
    {
        valid_argument = 0;
        // No reason to continue
        printf("%s\n", error_message);
        return -1;    // This is an error code
    }

    // Check that each character is a valid digit
    for (int i = 0, length = strlen(argv[1]); i < length; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            valid_argument = 0;
        }
    }

    // Is the first element a negative sign? If so, invalid
    if (argv[1][0] == '-')
    {
        valid_argument = 0;
    }

    // Ensure no leading zeros
    if (valid_argument && (strlen(argv[1]) > 1) && argv[1][0] == '0')
    {
        valid_argument = 0;
    }

    // Convert valid argument to int
    int key = 0;
    if (valid_argument)
    {
        key = atoi(argv[1]);
        return key;
    }
    else
    {
        printf("%s\n", error_message);
        return -1;    // This is an error code
    }
}

