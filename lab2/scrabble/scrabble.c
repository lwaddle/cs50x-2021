#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

/**
 * Array that will hold 26 letters of the alphabet (uppercase)
 * Uses populate_ascii_upper_alpha() to populate itself.
 */
int ASCII_UPPER_ALPHA[26];

int compute_score(string word);
int get_char_index(char c, int array[]);
void populate_ascii_upper_alpha(int array[]);

int main(void)
{
    // Populate ASCII_UPPER_ALPHA
    populate_ascii_upper_alpha(ASCII_UPPER_ALPHA);

    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

/**
 * Computes the score of a scrabble word
 */
int compute_score(string word)
{
    // Compute and return score for string
    int score = 0;

    /**
     * Check each character in word and determine if it is alpha. If so, make
     * it uppercase if not so already. ASCII values of A-Z are 65-90.
     */
    for (int i = 0, length = strlen(word); i < length; i++)
    {
        if (isalpha(word[i]))
        {
            word[i] = toupper(word[i]);

            score += POINTS[get_char_index(word[i], ASCII_UPPER_ALPHA)];

        }
    }

    return score;
}

/**
 * Gets the index of an uppercase letter in the alphabet
 */
int get_char_index(char c, int array[])
{
    int index = 0;

    for (int i = 0; i < 26; i++)
    {
        if ((int) c == array[i])
        {
            index = i;
        }
    }

    if ((index < 0) || (index > 25))    // An error occurred
    {
        fprintf(stderr, "Error has occurred\n");
        return -1;
    }

    return index;
}

/**
 * Populates an all uppercase array of the alphabet
 */
void populate_ascii_upper_alpha(int array[])
{
    for (int i = 0, ascii = 65; i < 26; i++, ascii++)
    {
        array[i] = ascii;
    }
}