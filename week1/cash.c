#include <stdio.h>
#include <math.h>

int main(void)
{
    //Declare the money variables
    float money;
    int quarter = 0, dimes = 0, nickels = 0, pennies = 0;

    //Ask for a valid money value
    do
    {
        printf("Change owed: ");
        scanf("%f", &money);
    }
    while (money <= 0);
    //Round the number
    float dollars = round(money * 100);

    //Count the cash necessary
    while (dollars >= 25)
    {
        dollars -= 25;
        quarter++;
    }
    
    while (dollars >= 10)
    {
        dollars -= 10;
        dimes++;
    }
    
    while (dollars >= 5)
    {
        dollars -= 5;
        nickels++;
    }
   
    while (dollars >= 1)
    {
        dollars -= 1;
        pennies++;
    }
    
    printf("%i\n", quarter + dimes + nickels + pennies);
}
