#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    // Prompt the user for a string
    string text = get_string("Text: ");
    int textLength = strlen(text);

    // Count the number of letters
    float letterCount = 0;
    for (int i = 0; i < textLength; i++)
    {
        if (text[i] >= 'A' && text[i] <= 'Z')
        {
            letterCount++;
        }
        else if (text[i] >= 'a' && text[i] <= 'z')
        {
            letterCount++;
        }
    }

    // Count the number of words
    float wordCount = 1;
    for (int i = 0; i < textLength; i++)
    {
        if (text[i] == ' ')
        {
            wordCount++;
        }
    }

    // Count the number of sentences
    float sentenceCount = 0;
    for (int i = 0; i < textLength; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentenceCount++;
        }
    }

    // Caclulate Letters per 100 words
    float l = (letterCount * 100) / wordCount;

    // Caclulate average number of sentences per 100 words
    float s = (sentenceCount * 100) / wordCount;

    // Calculate the Coleman-Liau index
    float gradeLevel = 0.0588 * l - 0.296 * s - 15.8;

    // return 'Grade Level'
    if (gradeLevel >= 16)
    {
        printf("Grade 16+");
    }
    else if (gradeLevel < 1)
    {
        printf("Before Grade 1");
    }
    else
    {
        printf("Grade %1.0f", gradeLevel);
    }

    printf("\n");
}