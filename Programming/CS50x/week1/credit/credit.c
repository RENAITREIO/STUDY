#include <cs50.h>
#include <stdio.h>

long get_positive_num(void);
bool check_valid(long num);
void check_bits(long num);

int main(void)
{
    long num = get_positive_num();
    if (check_valid(num))
    {
        check_bits(num);
    }
    else
        printf("INVALID\n");
}

long get_positive_num(void)
{
    long num = 0;
    do
    {
        num = get_long("Change owed: ");
    }
    while (num < 1);
    return num;
}

bool check_valid(long num)
{
    bool isValid = 0;
    int sum = 0;
    int count = 0;
    while (num > 0)
    {
        int temp = (num % 10) * (count % 2 + 1);
        while (temp > 0)
        {
            sum += temp % 10;
            temp /= 10;
        }
        num /= 10;
        count++;
    }
    if (sum % 10 == 0)
        isValid = 1;
    return isValid;
}

void check_bits(long num)
{
    int length = 2;
    while (num >= 100)
    {
        length++;
        num /= 10;
    }
    if (length == 15 && (num == 34 || num == 37))
        printf("AMEX\n");
    else if (length == 16 && (num >= 51 && num <= 55))
        printf("MASTERCARD\n");
    else if ((length == 13 || length == 16) && num / 10 == 4)
        printf("VISA\n");
    else
        printf("INVALID\n");
}
