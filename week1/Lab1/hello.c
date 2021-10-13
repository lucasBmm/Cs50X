#include <stdio.h>
#include <string.h>

int main(void)
{
    //Declare the name variable, an array in this case
    char name[255];

    //Ask for the user name and add it to the variable
    printf("What is your name?\n");
    scanf("%s", name);

    //Print the message to the user
    printf("Hello, %s\n", name);
    return 0;
}