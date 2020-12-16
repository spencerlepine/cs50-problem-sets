#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

bool isLetter(char character);

int main(int argc, string argv[])
{
    const string KEY = argv[1];

    if (!KEY)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (argv[2])
    {
        printf("Too many command line arguments passed\n");
        return 1;
    }
    else if (strlen(KEY) < 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    int alphabet[26] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    // Contains JUST the alphabet
    for (int i = 0, n = strlen(KEY); i < n; i++)
    {
        // Mark that this was used
        int thisCharCode = ((int) KEY[i]) - 65;

        // If this number is in the alphabet
        if (isLetter(thisCharCode + 65))
        {
            // Mark that this letter was used (UPPER OR LOWER case)
            if (thisCharCode >= 32)
            {
                if (!alphabet[thisCharCode] - 32)
                {
                    alphabet[thisCharCode - 32] = 1;
                }
            }
            else if (alphabet[thisCharCode] == 0)
            {
                alphabet[thisCharCode] = 1;
            }
            else
            {
                printf("Something went wrong");
                return 1;
            }
        }
        else
        {
            printf("Found repeating letters\n");
            return 1;
        }
    }

    // Receive plaintext input
    string plainText = get_string("plaintext: ");

    printf("ciphertext: ");
    for (int i = 0, n = strlen(plainText); i < n; i++)
    {
        // Get a 1 through 26 index
        if (isLetter(plainText[i]))
        {
            int alphabetIndex = ((int) plainText[i] - 65);
            //printf("\nAlphabet Index is: %i\n", alphabetIndex);

            if (alphabetIndex >= 32)
            {
                //printf("Indx - 65 is: %i\n", alphabetIndex - 65);
                //printf("In KEY,This letter is: %c\n", KEY[alphabetIndex-32]);
                printf("%c", tolower(KEY[alphabetIndex - 32]));
            }
            else if (alphabetIndex <= 26)
            {

                //printf("In KEY,This letter is: %c\n", KEY[alphabetIndex]);
                printf("%c", toupper(KEY[alphabetIndex]));
            }
        }
        else
        {
            printf("%c", plainText[i]);
        }
    }

    printf("\n");

    // Exit program
    return 0;
}

bool isLetter(char character)
{
    const int thisChar = (int) character - 65;

    if ((thisChar >= 0 && thisChar <= 26) || (thisChar >= 32 && thisChar <= 57))
    {
        return true;
    }

    return false;
}