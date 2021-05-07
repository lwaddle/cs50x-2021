#include <cs50.h>
#include <stdio.h>

/**
 * Function: print_pyramid
 * Args: int height
 * Prints a Mario style pyramid obstacle with a gap in the middle. For
 * example, a pyramid with a height of 3 would look like this:
 * 
 *       #  #
 *      ##  ##
 *     ###  ###
 *
 * The default gap width is 2 spaces
 */
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

    // TODO: Implement function to draw the pyramid
    print_pyramid(height);
}

/**
 * Function: print_pyramid
 * Args: int height
 * Prints a Mario style pyramid obstacle with a gap in the middle. For
 * example, a pyramid with a height of 3 would look like this:
 * 
 *       #  #
 *      ##  ##
 *     ###  ###
 *
 * The default gap width is 2 spaces
 */
void print_pyramid(int height)
{
    // Define the margin for the top of the pyramid
    int margin = height - 1;

    // Define the first row width - does not include margin
    int row_width_after_margin = height + 3 - margin;

    for (int row = 0; row < height; row++)
    {
        // Print the margin
        for (int i = 0; i < margin; i++)
        {
            printf(" ");
        }

        // Print the remaining row after margin
        for (int col = 0; col < row_width_after_margin; col++)
        {
            if ((col == (row_width_after_margin / 2) - 1) || (col == (row_width_after_margin / 2)))
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }
        margin -= 1;                    // Margin only on left side
        row_width_after_margin += 2;    // Add 2... It grows by 1 for each side
        printf("\n");
    }
}