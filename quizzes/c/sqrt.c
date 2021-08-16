#include <stdio.h> /* printf */
#include <math.h> /* sqrt */
#include <stdlib.h>
#include <assert.h>

#define PECISION_NUM 0.00001
#define MAX2(a, b)  ((a > b) ? (a) : (b))

double Sqrt(double num) ;

int main()
{
	double n = 0.0;
	double jumps = 0.01;

	while (10000 > n)
	{
		if (PECISION_NUM < fabs(sqrt(n) - Sqrt(n)))
		{
			printf("Error at square root of %f . expected: %f, actual: %f, diff: %f\n", n, sqrt(n), Sqrt(n), fabs(sqrt(n) - Sqrt(n)));	
		}
		n += jumps;
	}

	return (0);
}

double Sqrt(double num)
{
    double buttom = 0.0;
    double top = MAX2(num, 1);
    double mid = 0.0;

	assert(0 <= num);

    while((top - buttom) > PECISION_NUM) /* check whether the interval is small enough*/
    { 
        mid = (buttom + top) / 2;
        
        if (mid * mid <= num)
        {
            buttom = mid;
        } 
        else
        {
            top = mid;
        }
    }

    return buttom;
}


