#include <stdio.h>

int main(void)
{
    // Variables
    long number, i = 0, number2 = 0, n;
    int total = 0, digits = 0;
    // Receives card number
    do
    {
        printf("Number: ");
        scanf("%i", &number);
        number2 = number;
        n = number;

    }
    while (number < 10);

    // Check if it's valid
    while (number > 0)
    {
        digits++;
        number /= 10;
        long valid = number % 10;
        number /= 10;
        // Beak the number if it's greater then 10
        if (valid * 2 > 10)
        {
            total += (valid * 2) % 10;
            total += 1;

        }
        else
        {
            total += valid % 10 * 2;
        }
    }
    // Count how many digits the number have
    while (number2 > 0)
    {
        digits++;
        long valid2 = number2 % 10;
        number2 /= 10;
        number2 /= 10;
        total += valid2;
    }
    while (n > 99)
    {
        n /= 10;
    }

    // Verify if it's Visa
    if (digits >= 13 && n / 10 == 4 && total % 10 == 0)
    {
        printf("VISA\n");

    }
    // Verify if it's American Express
    else if (digits > 14 && (n == 34 || n == 37))
    {
        printf("AMEX\n");

    }
    // Verify if it's MasterCard
    else if (digits > 10 && (n > 50 && n < 56))
    {
        printf("MASTERCARD\n");

    }
    // And it's none of the above, say it's invalid
    else
    {
        printf("INVALID\n");
    }
}


