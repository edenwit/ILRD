#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
void PrintArr(int *arr, size_t n);
size_t Josephus(size_t n);


int main()
{
	size_t i = 0;
	size_t iters = 10;
	
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

size_t Josephus(size_t n)
{
	int *soldairs = NULL;
	int cur_soldair = 0;
	int next_soldair = 0;
	int kill_now = 0;
	
	if(2 > n)
	{
		printf("Minimum 2 soldairs for Josephus problem to make sense!");
		return 1;
	}
	soldairs = (int *)calloc(n, sizeof(int));
	assert(NULL != soldairs);	
	
	PrintArr(soldairs, n);
	
	while (1)
	{
		next_soldair = (cur_soldair + 1) % n;
		while ((1 == soldairs[next_soldair]) && (next_soldair != cur_soldair))
		{
			next_soldair = (next_soldair + 1) % n;
			
			if (next_soldair == cur_soldair)
			{
				printf("\nLast to stay alive: %d.\n",cur_soldair);
				free (soldairs);
				return cur_soldair;
			}
		}
		soldairs[next_soldair] = 1;
		PrintArr(soldairs, n);
		
		while ((1 == soldairs[next_soldair]) && (next_soldair != cur_soldair))
		{
			next_soldair = (next_soldair + 1) % n;
			if (next_soldair == cur_soldair)
			{
				printf("\nLast to stay alive: %d.\n",cur_soldair);
				free (soldairs);
				return cur_soldair;
			}
		}
		cur_soldair = next_soldair;
	}
	free (soldairs);
	return 0;
}	
