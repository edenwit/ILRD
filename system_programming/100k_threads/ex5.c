#include <stdio.h>
#include <time.h>

#define NUM (1200000000)

int main()
{
    size_t i = 0;
    size_t sum_of_divisors = 0;

    for (i = 1; i <= NUM; ++i)
    {
        if (0 == NUM % i)
        {
            sum_of_divisors += i;
        }
    }

    printf("sum: %ld\n", sum_of_divisors);

    return (0);
}
