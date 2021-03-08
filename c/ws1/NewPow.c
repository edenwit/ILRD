
#include <stdio.h>
#include <math.h>

double Power10 (int n)
{
	double base = 1;
	double power = 10;
	int i = 0;

	if(n < 0)
	{
		power = 0.1;
		n = n*-1;
	}
	
	for (i = 0; i < n; i++)
	{
		base = base * power;
	}
	
	return base;
}

int main()
{
	int i;
	int arr_test[] = {1, (-5), 8, (-1), (-3), (-6)};
	double arr_results[] = {10, 0.1*0.1*0.1*0.1*0.1, 1, 0.1, 0.1*0.1*0.1, 0.1*0.1*0.1*0.1*0.1*0.1};
	int array_size = sizeof(arr_test) / sizeof(arr_test[0]);
	
	for (i = 0; i < array_size; i++)
	{   
		printf("Test #%d: got: %f, expacted: %f  ", i + 1, Power10(arr_test[i]),
			arr_results[i]);
		if(Power10(arr_test[i]) == arr_results[i])
		{
			printf("Yess!\n");
		}
		else
		{
			printf("Oh no you didn't!\n");
		}
	}
	return 0;
}


