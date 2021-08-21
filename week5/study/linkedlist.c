#include <stdio.h>
#include <stdlib.h>

//representation of a node
typedef struct node
{
    int number;
    struct node *next;
}
node;

void printList(struct node *n);

int main(void)
{
    //Create the first element of the list, set his number to 1 and point next to null
    node *first = malloc(sizeof(node));
    node *second = malloc(sizeof(node));
    node *third = malloc(sizeof(node));
    if (first == NULL || second == NULL || third == NULL)
    {
        printf("Eror\n");
        return 1;
    }
    first->number = 1;
    first->next = second;
    
    second->number = 2;
    second->next = third;
    
    third->number = 3;
    third->next = NULL;
    
    printList(first);
    
    free(first);
    free(second);
    free(third);
    
    return 0;
}
void printList(struct node *n)
{
    while (n != NULL)
    {
        printf("%i ", n->number);
        n = n->next;
    }
    printf("\n");
}