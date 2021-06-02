#include <stdio.h> /* printf */
#include <math.h> /* sqrt */
#include <stdlib.h>

#define PECISION_NUM 0.0001

double Sqrt(double num) ;

int main()
{
	double n = 0.0;
	double jumps = 1.0;

	while (10000 > n)
	{
		if (PECISION_NUM < fabs(sqrt(n) - Sqrt(n)))
		{
			printf("Error at square root of %lf . expected: %lf, actual: %lf, diff: %f\n", n, sqrt(n), Sqrt(n), fabs(sqrt(n) - Sqrt(n)));	
		}
		n += jumps;
	}

	return (0);
}

double Sqrt(double num) 
{
	double i = 1.0;
	double precision = 0.00001;

	while ((i * i) <= num)
	{
		++i;
	}
	
	--i;
	
	while ((i * i) < num)
	{
		i += precision;
	}	

   return (i);
}


