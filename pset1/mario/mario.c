#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int gap = 2;

    // Create height variable
    int pyramidHeight;

    // Get input until the input is positive integer (DO WHILE)
    do
    {
        // Ask for the height
        pyramidHeight = get_int("Height: ");

    }
    while (pyramidHeight < 1 || pyramidHeight > 8);

    int pyramidWidth = ((pyramidHeight * 2) + 1) + gap;

    // Create the pyramid based on rows
    for (int r = 0; r < pyramidHeight; r++)
    {
        int row = r + 1;

        for (int c = 0; c < pyramidWidth-1; c++)
        {
            int leftDistance = (pyramidHeight - c);
            int rightDistance = ((c - pyramidHeight+1) - gap);

            // Left side of the pyramid
            if (leftDistance <= row && leftDistance > 0)
            {
                printf("#");
            }
            else
            {
                // Right side of the pyramid
                if (rightDistance <= row && rightDistance > 0)
                {
                    printf("#");
                }
                else
                {
                    if (rightDistance > row && r != pyramidHeight)
                    {
                        // End of right side.
                        break;
                    }
                    else
                    {
                        printf(" ");
                    }
                }
            }
        }
        printf("\n");
    }
}