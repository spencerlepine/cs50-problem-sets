#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int length_of_long(long card_num);

int main(void)
{
    // Store the card number.
    long card_number = get_long("What is your Credit Card Number?\n");

    int oddDigits = 0;
    int evenDigits = 0;

    int card_length = length_of_long(card_number);

    int firstTwoDigits = 0;

    // Start at tens place, where divider is equal to 100.
    for (int i = 0; i < card_length + 1; i++)
    {   
        int thisDigit = (card_number / (long) pow(10, i)) % 10;

        if (i == card_length - 1)
        {   
            printf("Len-1, %i\n", thisDigit);
            firstTwoDigits += thisDigit;
        }
        if (i == card_length)
        {
            printf("Len, %i --- Times 10?\n", thisDigit);
            firstTwoDigits += (thisDigit * 10);
        }

        if ((card_length - i) % 2 != (card_length % 2))
        {
            // Mutliply this digit by 2
            thisDigit *= 2;

            // Add the products' digits
            if (thisDigit > 9)
            {
                // Ones place
                oddDigits += (thisDigit % 10);
                // Tens place
                oddDigits += (thisDigit / 10);
            }
            else
            {
                oddDigits += thisDigit;
            }
        }
        else
        {
            // Add this to the sum of even digits
            evenDigits += thisDigit;
        }
    }

    // Add the sum of odd digits to the sum even digits
    int sumTheSums = evenDigits + oddDigits;

    if (sumTheSums % 10 == 0 && card_length >= 12)
    {
        if (firstTwoDigits == 34 || firstTwoDigits == 37)
        {
            printf("AMEX\n");
        }
        else
        {
            if (firstTwoDigits >= 51 && firstTwoDigits <= 55)
            {
                printf("MASTERCARD\n");
            }
            else
            {
                if (firstTwoDigits / 10 == 4)
                {
                    printf("VISA\n");
                }
                else
                {
                    printf("INVALID\n");
                }
            }
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

int length_of_long(long card_num)
{
    // Start at the 16th digit and work backwards.
    long divider = 10000000000000000;
    int zero_count = 16;

    // The credit card will always start with a NON zero value.
    while ((card_num / divider) % 10 == 0)
    {
        divider /= 10;
        zero_count -= 1;
    }

    return zero_count;
}
