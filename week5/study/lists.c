#include <stdio.h>
#include <stdlib.h>

//Create the node struct
typedef struct node
{
    int number;
    struct node *next;
}
node;

node *create(int n, node *list);

int main(void)
{
    //Create the pointer to the linked list
    node *list = malloc(sizeof(node));
    
    //Define the first element of the list and check for any error
    node *head = malloc(sizeof(node));
    if (head == NULL)
    {
        printf("ERROR");
        return 1;
    }
    list->next = head;
    head->number = 1;
    head->next = NULL;
    //Create a variable to allocate in to a node
    int n;
    printf("N: ");
    scanf("%i", &n);
    node *no = create(n, list);
    
    list = list->next;
    while(list != NULL)
    {
        printf("%i\n", list->number);
        list = list->next;
    }
    free(list);
    free(head);
    
}
node *create(int n, node *list)
{
    node *a = malloc(sizeof(node));
    a->number = n;
    a->next = list->next;
    list->next = a;
    return a;
}