#include <stdio.h>
#include <stdlib.h>

void selectionSort(int array[], int size);
//Define a const to be th array length
const int SIZE = 50000;

int main(int argc, char *argv[])
{
    //Check for correct usage
    if (argc != 2)
    {
        printf("Usage: ./selsort file.txt");
    }
    //Open file and check if isn't null 
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("File not found\n");
        return 1;
    }
    //Create a sorted.txt file
    FILE *sorted = fopen("sorted.txt", "w");
    int n[SIZE], i = 0, j = 0;
    //Scan every number in the file
    while (fscanf(file, "%i", &i) != EOF)
    {
        n[j] = i;
        j++;
    }
    //Calls selection sort function
    selectionSort(n, sizeof(n));
    
    //Printf the sorted numbers ins the output file
    for (i = 0; i < SIZE; i++)
    {
        fprintf(sorted, "%i\n", n[i]);
    }
    //Close files and return 0
    fclose(file);
    fclose(sorted);
    return 0;
}
//Function that uses selection sort to sort the file numbers
void selectionSort(int array[], int size)
{
    size /= sizeof(int);
    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (array[i] > array[j])
            {
                int tmp = array[i];
                array[i] = array[j];
                array[j] = tmp;
            }
        }
    }
}