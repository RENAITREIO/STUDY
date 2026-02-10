#include <cs50.h>
#include <stdio.h>

int get_positive_num(void);

int main(void)
{
    int height = get_positive_num();
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (height - i - 1); j++)
        {
            printf(" ");
        }
        for (int j = 0; j < (i + 1); j++)
        {
            printf("#");
        }
        printf("\n");
    }
}

int get_positive_num(void)
{
    int num = 0;
    do
    {
        num = get_int("Height: ");
    }
    while (num < 1);
    return num;
}
