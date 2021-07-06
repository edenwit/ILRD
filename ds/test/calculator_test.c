#include <stddef.h>
#include <stdio.h> /* printf */

#include "calculator.h"

int main()
{
    size_t i = 0;
    char string[][60] = {
    {"6+(5"},
    {"6(+5"},
    {"(-2)^0.5"},
    {"0^-5+"},
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
    {"9/3(1+2)"},
    {"1"},
    {"--- -- -- -5 +++ ++2 -4"},
    {"2 // 4.1"},
    {"1 + 2 (2 + 2 (1 + 2 * (3 + 2 + 1)+ 1) / 2 + 1) 2 + 2"},
    {"1 ^ 0"},
    {"14 + 5 ^ 2 ^ 3+ 5"},
    {"3 + 2^2^3 / 5"},
    {" // 1 + 23 54+ 1"},
    {" 14 ^ -3"},
    {" 0 ^ 0.2"},
    {"0 ^ -12"},
    {"(2)4)5)6)"},
    {"2(2(2(2)))"}
    };
    double result = 0.0;
    calc_status_t status = SUCCESS;
    size_t arr_size = sizeof(string) / sizeof(string[0]);

    for (i = 0; i < arr_size; ++i)
    {
        printf("%s = ",string[i]);
        result = -999.0;

        status = Calculate(string[i], &result);

        if(SUCCESS != status)
        {
            switch (status)
            {
                case INVALID_EQUETION:
                {
                    printf("INVALID EQUETION\n");
                    break;
                }
                case MATH_ERROR:
                {
                    printf("MATH ERROR\n");
                    break;
                    
                }   
                default:
                {
                    printf("SYSTEMFAIL\n");
                }            
            }
        }
        else
        {
            printf("%f\n", result);
        }
    }

    return (0);
}
