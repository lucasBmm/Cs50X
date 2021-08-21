#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
    //Declare the variable to store the user text
    char text[2056];
    int letters, words, sentences;
    letters = words = sentences = 0;
    
    //Ask the user for the text
    printf("Text: ");
    fgets(text, 2056, stdin);

    //Pass all letters to uppercase to make easier to calculate
    for (int i = 0; i < strlen(text); i++)
    {
        text[i] = toupper(text[i]);
    }
    //Count the letters, words and sentences
    for (int i = 0; i < strlen(text); i++)
    {
        if ((text[i] >= 'A') && (text[i] <= 'Z'))
        {
            letters++;
        }
        if (text[i] == ' ')
        {
            words++;
        }
        if (text[i] == '!' || text[i] == '?' || text[i] == '.')
        {
           sentences++;
        }
    }
    words++;
    //Calculate using Coleman-Liau index
    float L = (float) letters /  words * 100;
    float S = (float) sentences / words * 100;
    float index = 0.0588 * L - 0.296 * S - 15.8;
    
    //Determine what should be the grade and print the result
    if (index < 0)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else if (index - (int) index > 0.5)
    {
        printf("Grade %i\n", (int) index+1);
    }
    else if (index - (int) index < 0.5)
    {
        printf("Grade %i\n", (int) index);
    }
   
}