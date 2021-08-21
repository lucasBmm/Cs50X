#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const int MAX = 50000;

void mergesort(int numbers[], int min, int max);

void merge(int vetor[], int comeco, int meio, int fim);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./mergesort filename.txt\n");
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Cannot open file\n");
        return 1;
    }
    FILE *output = fopen("mergesorted.txt", "w");
    int numbers[MAX];
    int i = 0, j = 0;
    while (fscanf(file, "%i", &i) != EOF)
    {
        numbers[j] = i;
        j++;
    }
    mergesort(numbers, 0, MAX-1);

    for (i = 0; i < MAX; i++)
    {
        fprintf(output, "%i\n", numbers[i]);
    }
    return 0;
    fclose(file);
    fclose(output);
}

void mergesort(int numbers[], int min, int max)
{
    int half = floor(min + max) / 2;
    if(min < max)
    {
        mergesort(numbers, min, half);
        mergesort(numbers, half+1, max);
        merge(numbers, min, half, max);
    }
    return;
}
void merge(int vetor[], int comeco, int meio, int fim) 
{
    int com1 = comeco, com2 = meio+1, comAux = 0, tam = fim-comeco+1;
    int *vetAux = (int*)malloc(tam * sizeof(int));

    while(com1 <= meio && com2 <= fim){
        if(vetor[com1] < vetor[com2]) {
            vetAux[comAux] = vetor[com1];
            com1++;
        } else {
            vetAux[comAux] = vetor[com2];
            com2++;
        }
        comAux++;
    }

    while(com1 <= meio)
    { 
        vetAux[comAux] = vetor[com1];
        comAux++;
        com1++;
    }

    while(com2 <= fim) 
    {   
        vetAux[comAux] = vetor[com2];
        comAux++;
        com2++;
    }

    for(comAux = comeco; comAux <= fim; comAux++)
    {    
        vetor[comAux] = vetAux[comAux-comeco];
    }

    free(vetAux);
}
