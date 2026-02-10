#include <cs50.h>
#include <stdio.h>

int get_positive_num(void);

int main(void)
{
    int cash = get_positive_num();
    printf("%d\n", (cash / 25 + cash % 25 / 10 + cash % 25 % 10 / 5 + cash % 25 % 10 % 5 / 1));
}

int get_positive_num(void)
{
    int num = 0;
    do
    {
        num = get_int("Change owed: ");
    }
    while (num < 1);
    return num;
}
