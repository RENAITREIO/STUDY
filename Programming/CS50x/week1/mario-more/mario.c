#include <cs50.h>
#include <stdio.h>

int get_positive_num(void);
void print_hashes(int n);

int main(void)
{
    int height = get_positive_num();
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (height - i - 1); j++)
        {
            printf(" ");
        }
        print_hashes(i);
        printf("  ");
        print_hashes(i);
        printf("\n");
    }
}

void print_hashes(int n)
{
    for (int j = 0; j < (n + 1); j++)
    {
        printf("#");
    }
}

int get_positive_num(void)
{
    int num = 0;
    do
    {
        num = get_int("Height: ");
    }
    while (num < 1 || num > 8);
    return num;
}
