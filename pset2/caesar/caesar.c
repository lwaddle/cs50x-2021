#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void encrypt(char *plaintext);
int  get_index(int c, const char array[], int length);
int  get_valid_key(const int argc, const char *argv[]);
void print_cipher_output(char *cipher);
int  shift_cipher(char cipher[], int key);

const char ALPHABET_LOWER[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
                               'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
                               's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

const char ALPHABET_UPPER[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
                               'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
                               'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

char cipher_lower[] =         {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
                               'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
                               's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

char cipher_upper[] =         {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
                               'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
                               'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

int main(const int argc, const char *argv[])
{
    // Get the key from CL arg
    int key = get_valid_key(argc, argv);

    // Populate the cipher text (lower and upper)
    shift_cipher(cipher_lower, key);
    shift_cipher(cipher_upper, key);

    // Get the plaintext
    char *plaintext = get_string("plaintext: ");

    // Encrypt the plaintext
    encrypt(plaintext);

    // Print the cyphertext
    print_cipher_output(plaintext);
}


/**
 * Encrypts the plaintext into a ciphertext by shifting the letters by 'key'
 * positions.
 */
void encrypt(char *plaintext)
{
    for (int i = 0, length = strlen(plaintext); i < length; i++)
    {
        int index;
        if (isalpha(plaintext[i]))
        {
            // Get the char's index from the normal alphabet
            // Upper or lower doesn't matter so use lower here.
            index = get_index(tolower(plaintext[i]), ALPHABET_LOWER, 26);

            // Replace the char with the appropriate cipher value using the
            // index from the normal alphabet. Consider case.
            if (isupper(plaintext[i]))
            {
                plaintext[i] = cipher_upper[index];
                //printf("%c", plaintext[i]);
            }
            else
            {
                // It's lowercase
                plaintext[i] = cipher_lower[index];
                //printf("%c", plaintext[i]);
            }
        }
    }

    return;
}

/**
 * Returns the index of a char from an alphabet char array. For example:
 * char 'c' is located at index 2 of the alphabet. Returns -1 if an
 * error has occurred.
 */
int get_index(int c, const char array[], int length)
{
    int index = -1;
    
    for (int i = 0; i < length; i++)
    {
        if (c == array[i])
        {
            index = i;
        }
    }

    return index;
}

/**
 * Returns the key from the user's command line argument. In the event that
 * the argument is invalid, it will display a message providing instructions.
 * An invalid argument will return a value of -1.
 */
int get_valid_key(const int argc, const char *argv[])
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

/**
 * Prints the final ciphertext output to the console.
 */
void print_cipher_output(char *cipher)
{
    printf("ciphertext: ");
    for (int i = 0, length = strlen(cipher); i < length; i++)
    {
        printf("%c", cipher[i]);
    }
    printf("\n");
}

/**
 * Shifts an alphabet 'key' number of positions to the right. The last char
 * gets moved to the beginning at each pass.
 */
int shift_cipher(char cipher[], int key)
{
    int length = strlen(cipher);

    // Shift characters to the right. Last char becomes first. Do this key
    // number of times.
    while (key > 0)
    {
        char last_char = cipher[length - 1];
        for (int i = length - 1; i > 0; i--)
        {
            cipher[i] = cipher[i - 1];
        }
        cipher[0] = last_char;
        key--;
    }

    return 1;
}

