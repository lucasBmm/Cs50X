#include <stdio.h>

int main(void)
{
    int height, pyr;
    //Asks the user for a pyramid height
    do
    {
        printf("Height: ");
        scanf("%i", &height);
    }
    while (height < 1 || height > 8);

    pyr = height;

   // write the pyramids
    for (int i = 0; i < height; i++)
    {
        int space = 0;
        int a = -1;

        //space between then
        for (space = height - 1; space > i; space--)
        {
            printf(" ");
        }
        //First pyramid
        do
        {
            printf("#");
            a++;

        }
        while (a < i);

        printf("  ");
        a = -1;

        //Second pyramid
        do
        {
            printf("#");
            a++;

        }
        while (a < i);

        printf("\n");
    }
}
