#include <stdio.h>

int collatz(int n);

int main(void)
{
    int n, result;
    printf("Enter a input: ");
    scanf("%i", &n);
    result = collatz(n);
    printf("%i steps\n", result);
}
int collatz(int n)
{
    if (n == 1)
        return 0;
    else if (n % 2 == 0)
        return 1 + collatz(n / 2);
    else
        return 1 + collatz(n * 3 + 1);
    
}