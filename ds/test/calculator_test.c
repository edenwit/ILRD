#include "calculator.h"
#include <stddef.h>

int main()
{
    size_t i = 0;
    char string[10][50] = {
    {"(155 + 6) * 4 "},
    {"6 / 2 *(1 +2)"},
    {"  2+5*3^2+5+"},
    {"      5  + 6 * 4 "},
    {"2 + 24 / 3 * 8"},
    {"1 + aghfhc15"},
    
    {"1"},
    {"56 * 2 + 2"},
    {"14 + 5 ^ 2 ^ 3+ 5"},
    {"3 + 2^2^3 / 5"}
    };
    double result = 0.0;

    for (i = 0; i < 10; ++i)
    {
        Calculate(string[i], &result);
    }

    return (0);
}