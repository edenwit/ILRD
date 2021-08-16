#include <stddef.h> /* size_t */
#include <stdio.h>  /* printf */
#include <math.h> /* power */

#define PECISION_NUM 0.00001

double Power(double x, int y);
static void PowerTest();

int main()
{
    PowerTest();

    return (0);
}

double Power(double x, int y)
{
    double res = 1;
    size_t i = 0;

    if (y < 0)
    {
        y *= (-1);
        x = 1 / x;
    }

    for (i = 0; i < (size_t)y; ++i)
    {
        res *= x;
    }

    return (res);
}

static void PowerTest()
{
    double base_arr[] = {1, 2, 3, 4, 5, 6, 2.2, 0.3, 9, -3, 20, 0, 0};
    int expo_arr[]     = {2, 0, 4,-2,-4,-1, 7,1, 3,   10, -2, 2, 2, 0};
    size_t arr_size = sizeof(base_arr) / sizeof(base_arr[0]);
    size_t i = 0;
    double power_res = 0.0;
    double pow_res = 0.0;

    for (i = 0; i < arr_size; ++i)
    {
        power_res = Power(base_arr[i], expo_arr[i] );
        pow_res = pow(base_arr[i], expo_arr[i]);

        if (PECISION_NUM < (power_res - pow_res))
        {
            printf("Iter #%ld: Fail. Actual: %f, expacted: %f\n", i + 1, power_res, pow_res);
        }
    }

    return;
}
