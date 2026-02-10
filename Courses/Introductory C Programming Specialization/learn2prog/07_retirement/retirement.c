#include <stdio.h>
#include <stdlib.h>

struct _retire_info
{
    int months;
    double contribution;
    double rate_of_return;
};

typedef struct _retire_info retire_info;

void retirement(int startAge, double initial, retire_info working, retire_info retired);

int main(void)
{
    int startAge = 327;
    double startMoney = 21345;
    retire_info work = {
        .months = 489,
        .contribution = 1000,
        .rate_of_return = 0.045 / 12
    };
    retire_info retire = {
        .months = 384,
        .contribution = -4000,
        .rate_of_return = 0.01 / 12
    };
    retirement(startAge, startMoney, work, retire);
    return 0;
}

void retirement(int startAge, double initial, retire_info working, retire_info retired)
{
    int totalMonths = working.months + retired.months;
    for (int i = 0; i < totalMonths; i++)
    {
        printf("Age %3d month %2d you have $%.2lf\n", startAge / 12, startAge % 12, initial);
        if (i < working.months)
        {
            initial += (initial * working.rate_of_return + working.contribution);
        }
        else
        {
            initial += (initial * retired.rate_of_return + retired.contribution);
        }
        startAge++;
    }
}
