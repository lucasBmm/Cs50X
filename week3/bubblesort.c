#include <stdio.h>
#include <stdlib.h>

const int MAX = 50000;

void BubbleSort(int n[], int size);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./bubblesort filename.txt\n");
        return 1;
    }
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Cannot open file\n");
        return 1;
    }
    FILE *output = fopen("Bubblesorted.txt", "w");
    int numbers[MAX];
    int i = 0, j = 0;
    while(fscanf(input, "%i", &i) != EOF)
    {
        numbers[j] = i;
        j++;
    }
    BubbleSort(numbers, sizeof(numbers));
    
    for (i = 0; i < MAX; i++)
    {
        fprintf(output, "%i\n", numbers[i]);
    }
    return 0;
}
void BubbleSort(int n[], int size)
{
    size /= sizeof(int);
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            if (n[j] > n[j + 1])
            {
                int tmp = n[j];
                n[j] = n[j + 1];
                n[j + 1] = tmp;
            }
        }
    }
}