#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    //Declare variables and open txt file
    int c, n, d;
    FILE *file = fopen(argv[1], "r");
    //Return a error if cannot open file
    if (file == NULL)
    {
        printf("Failed");
        return 1;
    }
    //Ask the user for a input
    printf("Number: ");
    scanf("%i", &n);
    //Start a line and begin to search for the number
    int line = 1;
    int i = 0;
    fscanf(file, "%d", &i);    
    while (!feof(file))
    {
        if (i == n)
        {
            printf("Found %i in line %i\n", i, line);
            fclose(file);
            return 0;
        }
        line++;    
        fscanf(file, "%d", &i);      
    }
    //Print error message if doesn't found number and close file
    printf("Not found\n");
    fclose(file);  
    return 1;
}