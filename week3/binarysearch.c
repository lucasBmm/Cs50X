#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

int binarySearch(int array[], int min, int max, int target);

int middle;

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: ./binarysearch filename.txt number of elements\n");
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    //Return a error if cannot open file
    if (file == NULL)
    {
        printf("Failed");
        return 1;
    }
    int max = atoi(argv[2]);
    int numbers[max];
    int i = 0, j = 0, target;
    printf("Number: ");
    scanf("%i", &target);
    while(fscanf(file, "%i", &i) != EOF)
    {
        numbers[j] = i;
        j++;
    }
    int result = binarySearch(numbers, 0, max-1, target);
    if (result == 0)
    {
        printf("found in line: %i\n", middle+1);
        return 0;
    }
    else
    {
        printf("Not found \n");
        return 1;
    }
}
int binarySearch(int array[],int min, int max, int target)
{
    middle = round((min + max) / 2);
    if (min > max)
        return 1;
    if (target < array[middle])
        return binarySearch(array, min, middle-1, target);
    else if (target > array[middle])
        return binarySearch(array, middle+1, max, target);
    else
        return 0;
}