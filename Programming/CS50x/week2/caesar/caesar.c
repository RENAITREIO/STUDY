#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool only_digits(string key);
char rotate(char c, int n);

int main(int argc, string argv[])
{
    int state = 0;
    if (argc == 2 && only_digits(argv[1]) == true)
    {
        int key = atoi(argv[1]);
        string plaintext = get_string("plaintext: ");
        printf("ciphertext: ");
        for (int i = 0; plaintext[i] != '\0'; i++)
        {
            printf("%c", rotate(plaintext[i], key));
        }
    }
    else
    {
        printf("Usage: %s key", argv[0]);
        state = 1;
    }
    printf("\n");
    return state;
}

bool only_digits(string key)
{
    bool state = true;
    for (int i = 0; key[i] != '\0'; i++)
    {
        if (!isdigit(key[i]))
        {
            state = false;
            break;
        }
    }
    return state;
}

char rotate(char c, int n)
{
    if (isupper(c))
    {
        c = (c - 'A' + n) % 26 + 'A';
    }
    else if (islower(c))
    {
        c = (c - 'a' + n) % 26 + 'a';
    }
    return c;
}
