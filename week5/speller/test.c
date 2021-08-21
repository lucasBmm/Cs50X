#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>

unsigned int hash(const char *word);

int main(void)
{
    char *word = "hello";
    unsigned int hashed = hash(word);
    printf("%i\n", hashed);
    return 0;
}

unsigned int hash(const char *word)
{
    // TODO
    unsigned long hash = 5381;

    for (const char* ptr = word; *ptr != '\0'; ptr++)
    {
        hash = ((hash << 5) + hash) + tolower(*ptr);
    }
    return hash % 2500;
    
}