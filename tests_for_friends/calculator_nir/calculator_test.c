#include "calculator.h"
#include <stddef.h>

int main()
{
    size_t i = 0;
    char string[][60] = {
    {"3 + (4/2))"},
    {"2 * (155 + 6) * 4 "},
    {"6 / 2 *(1 +2)"},
    {"  2+5*3^2+5+"},
    {"  2+5*3^2+5"},
    {"      5  + 6 * 4 "},
    {"2 + 24 / 3 * 8"},
    {"1 + aghfhc15"},
    {"1 / 0"},
    {"2/0"},
    {"3 ^ 1 ^ 0"},
    {"0 ^ 0"},
    {"5. 2 + 1"},
    {" 9 / 3 (1 + 2)"},
    {"1"},
    {"--- -- -- -5 +++ ++2 -4"},
    {"2 // 4.1"},
    {"1 + 2 (2 + 2 (1 + 2 * (3 + 2 + 1)+ 1) / 2 + 1) 2 + 2"},
    {"1 ^ 0"},
    {"14 + 5 ^ 2 ^ 3+ 5"},
    {"3 + 2^2^3 / 5"},
    {"1 / (5 +1(5-2))"}
    };
    double result = 0.0;
    calc_status_t status = SUCCESS;

    for (i = 0; i < 22; ++i)
    {
        printf("%s = ",string[i]);

        status = Calculate(string[i], &result);

        printf("%f - ", result);
        printf("status%d\n", status);

    }

    return (0);
}
