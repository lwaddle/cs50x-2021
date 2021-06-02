#include <cs50.h>
#include <stdio.h>

void print_pyramid(int height);

int main(void)
{
    // Define min and max values for pyramid height
    const int min_height = 1;
    const int max_height = 8;

    // Ask user for desired pyramid height
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while ((height < min_height) || (height > max_height));

    // Print out the pyramid
    print_pyramid(height);
}

/**
 * Asks user for a height and then prints a pyramid like this:
 * 
 * ---#
 * --##
 * -###
 * ####
 */
void print_pyramid(int height)
{
    char BLOCK = '#';
    char MARGIN_SPACE = ' ';

    // The spaces leading up to the #. Top of the pyramid has a margin of the
    // height - 1
    int margin = height - 1;
    
    while (margin >= 0)
    {
        for (int i = 0; i < margin; i++)
        {
            printf("%c", MARGIN_SPACE);    // Margin
        }

        int remaining_chars = height - margin;
        for (int i = 0; i < remaining_chars; i++)
        {
            printf("%c", BLOCK);
        }
        printf("\n");
        margin--;
    }
    
    return;
}