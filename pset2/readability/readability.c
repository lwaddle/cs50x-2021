#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

unsigned long long count_letters(const char *text);
unsigned long long count_sentences(const char *text);
unsigned long long count_words(const char *text);
void print_text_grade(const char *text);
int readability(const char *text);

int main(int argc, const char *argv[])
{
    string text = get_string("Text: ");

    print_text_grade(text);

    return 0;
}

/**
 * Returns the count of letters from input text. Only characters A-B in
 * upper and lower case will be counted. Punctuation and spaces are not
 * counted.
 */
unsigned long long count_letters(const char *text)
{
    unsigned long long length = strlen(text);
    unsigned long long letter_count = 0;

    for (unsigned long long i = 0; i < length; i++)
    {
        if (isalpha(text[i]))
        {
            letter_count++;
        }
    }

    return letter_count;
}

/**
 * Returns the count of sentences from input text. Consider any sequence of
 * characters that ends with a . or a ! or a ? to be a sentence. For this
 * exercise, words like Mr. and Mrs. will be considered the end of a
 * sentence.
 */
unsigned long long count_sentences(const char *text)
{
    unsigned long long length = strlen(text);
    unsigned long long sentence_count = 0;

    int sentence_started = 0;    // int as bool

    for (unsigned long long i = 0; i < length; ++i)
    {
        if (isalpha(text[i]) && !sentence_started)
        {
            sentence_count++;
            sentence_started = 1;
        }

        if (text[i] ==  '.' || text[i] ==  '!' || text[i] ==  '?')
        {
            sentence_started = 0;
        }
    }

    return sentence_count;
}

/**
 * Returns the count of words from input text. Consider any sequence of
 * characters separated by a space to be a word (so a hyphenated word like
 * "sister-in-law" should be considered one word, not three). Assume that a
 * sentence will not start or end with a space, and you may assume that a
 * sentence will not have multiple spaces in a row.
 */
unsigned long long count_words(const char *text)
{
    unsigned long long length = strlen(text);
    unsigned long long word_count = 0;
    int word_detected = 0;

    for (unsigned long long i = 0; i < length; ++i)
    {
        if (isalpha(text[i]) && !word_detected)
        {
            word_detected = 1;
            word_count++;
        }

        if (!isalpha(text[i]) && word_detected)
        {
            // Hyphenated words count as one. Consider ' and "
            if (text[i] != '-' && text[i] != '\'' && text[i] != '\"')
            {
                word_detected = 0;
            }
        }
    }

    return word_count;
}

/**
 * Prints the readability grade to the console.
 */
void print_text_grade(const char *text)
{
    int grade = readability(text);

    if (grade < 1)
    {
        printf("Before Grade 1\n");
        return;
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
        return;
    }
    else
    {
        printf("Grade %i\n", grade);
    }

}

/**
 * Returns the readability index of input text using the Coleman-Liau
 * index. Formula: index = 0.0588 * l - 0.296 * s - 15.8
 * Here, 'l' is the average number of letters per 100 words in the text,
 * and 's' is the average number of sentences per 100 words in the text.
 */
int readability(const char *text)
{
    unsigned long long total_letters = count_letters(text);
    unsigned long long total_words = count_words(text);
    unsigned long long total_sentences = count_sentences(text);
    double l = (total_letters / (double) total_words) * 100.0;
    double s = (total_sentences / (double) total_words) * 100.0;
    int index = round(0.0588 * l - 0.296 * s - 15.8);

    return index;
}