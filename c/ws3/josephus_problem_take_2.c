#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
void PrintArr(int *arr, size_t n);
size_t Josephus(const size_t n);


int main()
{
	size_t i = 0;
	size_t iters = 41;
	
	for (i = 0; i < iters; ++i)
	{
		printf("\n\n\n---------Josephus Problem with %lu cells-----------\n\n\n",i);
		Josephus(i);
	}
	
	return 0;
}

void PrintArr(int *arr, size_t n)
{	
	size_t i = 0;
	
	for (i = 0; i < n; ++i)
	{
		printf("%d ",arr[i]);
	}
	printf("\n");
			
	return;
}

size_t Josephus(const size_t n)
{
	int *soldairs = NULL;
	int cur_soldair = 0;
	int next_soldair = 1;
	int kill_now = 1;
	size_t kill_count = 0;
	
	if(2 > n)
	{
		printf("Minimum 2 soldairs for Josephus problem to make sense!");
		return 1;
	}
	soldairs = (int *)calloc(n, sizeof(int));
	assert(NULL != soldairs);	
	
	PrintArr(soldairs, n);
	while (n - 1 > kill_count)
	{

		if (0 == soldairs[next_soldair])
		{
			if (1 == kill_now)
			{
				soldairs[next_soldair] = 1;
				PrintArr(soldairs, n);
				kill_now = 0;
				++kill_count;
			}
			else
			{
				kill_now = 1;
				cur_soldair = next_soldair;
			}
		}
		next_soldair = (next_soldair + 1) % n;
	}
	printf("\nLast to stay alive: %d.\n",cur_soldair);
	free (soldairs);
	return cur_soldair;
}
