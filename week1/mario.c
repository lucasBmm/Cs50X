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

    //Draw the pyramid
    for (int i = 0; i < height; i++)
    {
        //Draw the blank spaces
        for (int j = 1; j < pyr; j++)
        {
            printf(" ");
        }
        //Draw the #
        for (int y = pyr - 1; y < height; y++)
        {
            printf("#");
        }
        printf("\n");
        pyr--;
    }
}
