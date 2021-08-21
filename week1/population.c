#include <stdio.h>

int main(void)
{
    //Declare variables
    int start, end, years, result;
    //Prompt for start size
    do
    {
        printf("Start size: ");
        scanf("%i", &start);
        
    } 
    while (start < 9);
    //Prompt for end size
    do
    {
        printf("End size: ");
        scanf("%i", &end);
        
    } 
    while (end < start);
    //Calculate number of years until we reach threshold
    for (years = 0; start < end; years++)
    {
        start += (float)(start / 3) - (float)(start / 4);
    }
    //Print number of years
    printf("Years: %i\n", years);
}