#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    //Check if correct usage
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    char *key = argv[1];
    
    //Check if it's a valid key
    for (int i = 0; i < strlen(key); i++)
    {
        if (isalpha(key[i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    // Convert from string to int
    int number = atoi(key);
    
    //Ask the user the text
    char plain[256];
    printf("Plaintext: ");
    fgets(plain, 256, stdin);
    plain[strlen(plain) - 1] = '\0';
    //Converts text to cipher
    for (int i = 0; i < strlen(plain); i++)
    {
        if (isalpha(plain[i]))
        {
            if (isupper(plain[i]))
            {
                int tmp = 0;
                tmp = plain[i] - 65;
                tmp = (tmp + number) % 26;
                plain[i] = tmp + 65;
            }
            else
            {
                int tmp = 0;
                tmp = plain[i] - 97;
                tmp = (tmp + number) % 26;
                plain[i] = tmp + 97;
            }
        }
    }
    // Print the encrypted text
    printf("ciphertext: %s\n", plain);
}