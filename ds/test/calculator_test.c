#include "calculator.h"
#include <stddef.h>

int main()
{
    size_t i = 0;
    char string[8][100] = {{"      5  + 6 * 4 "}, {"24 / 3 / 8"},
    {"1 + aghfhc15"},
    {"5 + 6 * 4 "},
    {"56 14 * 16 "},
    {"56 * 2 + 2"},
    {"14 + 5 ^ 2 ^ 3+ 5"},
    {"3 + 2^2^3"}
    };
    double result = 0.0;

    for (i = 0; i < 8; ++i)
    {
        Calculate(string[i], &result);
    }

    return (0);
}