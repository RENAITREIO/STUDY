#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool isproperc(string key);
char convert(char c, string key);

int main(int argc, string argv[])
{
    int state = 0;
    if (argc == 2)
    {
        for (int i = 0; argv[1][i] != '\0'; i++)
        {
            if (islower(argv[1][i]))
            {
                argv[1][i] = toupper(argv[1][i]);
            }
        }
        if (isproperc(argv[1]))
        {
            string plaintext = get_string("plaintext: ");
            printf("ciphertext: ");
            for (int i = 0; plaintext[i] != '\0'; i++)
            {
                printf("%c", convert(plaintext[i], argv[1]));
            }
        }
        else
        {
            printf("Key must contain 26 characters.");
            state = 1;
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

bool isproperc(string key)
{
    bool state = false;
    if (strlen(key) == 26)
    {
        bool allc = true;
        int count[26] = {0};
        for (int i = 0; key[i] != '\0'; i++)
        {
            if (isupper(key[i]))
            {
                count[key[i] - 'A']++;
            }
            else if (islower(key[i]))
            {
                count[key[i] - 'a']++;
            }
            else
            {
                allc = false;
                break;
            }
        }
        if (allc == true)
        {
            state = true;
            for (int i = 0; i < 26; i++)
            {
                if (count[i] == 0)
                {
                    state = false;
                    break;
                }
            }
        }
    }
    return state;
}

char convert(char c, string key)
{
    if (isupper(c))
    {
        c = toupper(key[c - 'A']);
    }
    else if (islower(c))
    {
        c = tolower(key[c - 'a']);
    }
    return c;
}
