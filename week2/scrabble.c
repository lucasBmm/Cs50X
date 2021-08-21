#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(char word[255]);

int main(void)
{
    //Create the array of characters
    char word1[255], word2[255];
    
    // Get input words from both players
    printf("Player 1: ");
    scanf("%s", word1);
    
    printf("Player 2: ");
    scanf("%s", word2);

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    //Print the winner
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

int compute_score(char word[])
{
    //Create a variable to return a int valor to score
    int point = 0;
    
    //Pass all the letters to upper to make the count easier
    for (int i = 0; i < strlen(word); i++)
    {
        word[i] = toupper(word[i]);  
    }
    //Compute the score based on the letter
    for (int i = 0; i < strlen(word); i++)
    {
        point += POINTS[word[i] - 65];
    }
    return point;
}