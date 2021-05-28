#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    bool is_valid_key;
    char error_msg[256];
} key_status;

// Function Prototypes

void       cipher(char plaintext[], const char key[]);
int        get_alphabetical_index(char c);
key_status get_key_status(int argc, const char *argv[]);
void       print_char_array(char array[]);

int main(int argc, const char *argv[])
{
    // Get status of the CL arg key
    key_status key_status = get_key_status(argc, argv);

    // Either continue or stop program based on key_status. Print error
    // message if required.
    if (key_status.is_valid_key == false)
    {
        print_char_array(key_status.error_msg);
        return 1;
    }

    // Get the key - not using strcpy to avoid the null character. Buffer 26
    // bytes for a standard English alphabet
    char key[26];
    for (int i = 0; i < 26; i++)
    {
        key[i] = toupper(argv[1][i]);
    }

    // Get the plaintext
    string plaintext = get_string("plaintext: ");

    // Cipher the plaintext
    cipher(plaintext, key);

    // Print the ciphertext output to console
    printf("ciphertext: ");
    print_char_array(plaintext);

    return 0;
}


// Function Implementations

/**
 * Takes some plaintext and converts it to ciphertext. It preserves case and
 * punctuation.
 */
void cipher(char plaintext[], const char key[])
{
    for (int i = 0, length = strlen(plaintext); i < length; i++)
    {
        if (isalpha(plaintext[i]))
        {
            int alphabetical_index = get_alphabetical_index(plaintext[i]);

            if (isupper(plaintext[i]))
            {
                plaintext[i] = key[alphabetical_index];
            }
            else    // Lowercase
            {
                plaintext[i] = tolower(key[alphabetical_index]);
            }
        }
    }
}

/**
 * Returns the alphabetical index of a char from the English alphabet. For
 * example, index of 'a' or 'A' is 0. Index of 'z' or 'Z' is 25. It doesn't
 * matter what the character's case is. Characters that are not part of the
 * English alphabet will return an error code of -1 with a message.
 */
int get_alphabetical_index(char c)
{
    const char ALPHABET[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
                             'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
                             'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
                            };

    for (int i = 0, length = strlen(ALPHABET); i < length; i++)
    {
        if (toupper(c) == ALPHABET[i])
        {
            return i;
        }
    }

    // Not found
    fprintf(stderr, "char not found in alphabet\n");
    return -1;
}

/**
 * This function returns a struct that contains a boolean of the status of a
 * user's command line argument. The user needs to enter a 26-character char
 * string in any case (upper or lower). The function's return struct contains
 * an error message. It will print the correct message depending upon what
 * the user entered.
 */
key_status get_key_status(int argc, const char *argv[])
{
    const int VALID_SUM_OF_ASCII = 2015;    // sum of A-Z ASCII
    const int LETTERS_IN_ALPHABET = 26;

    key_status key_status;
    key_status.is_valid_key = true;
    strcpy(key_status.error_msg, "None");

    // Check for valid number of command line arguments. Should be 2.
    if (argc != 2)
    {
        key_status.is_valid_key = false;
        strcpy(key_status.error_msg, "Usage: ./substitution key");
        return key_status;
    }

    // User must enter 26 characters
    if (strlen(argv[1]) != LETTERS_IN_ALPHABET)
    {
        key_status.is_valid_key = false;

        // Determine correct error message. If the user entered valid ASCII
        // alpha, but not enough characters, display "Key must contain 26
        // characters." Else standard error message.

        for (int i = 0, length = strlen(argv[1]); i < length; i++)
        {
            if (!isalpha(argv[1][i]))
            {
                strcpy(key_status.error_msg, "Usage: ./substitution key");
                return key_status;
            }
        }

        strcpy(key_status.error_msg, "Key must contain 26 characters.");
        return key_status;
    }

    /**
     * An easy way to determine if the user entered a valid key is to get the
     * sum of the ASCII values. Make sure to convert all the values entered
     * to the same case - uppercase in this function. The ASCII range of A-Z
     * is 65-90. That equals a sum of 2015.
     */

    int sum_of_ascii = 0;
    for (int i = 0, length = strlen(argv[1]); i < length; i++)
    {
        sum_of_ascii += (int) toupper(argv[1][i]);
    }

    if (sum_of_ascii != VALID_SUM_OF_ASCII)
    {
        key_status.is_valid_key = false;
        strcpy(key_status.error_msg, "Key must contain 26 characters.");
        return key_status;
    }

    return key_status;
}

/**
 * Simply prints out the contents of a char array to the console
 */
void print_char_array(char array[])
{
    for (int i = 0, length = strlen(array); i < length; i++)
    {
        printf("%c", array[i]);
    }
    printf("\n");
}
