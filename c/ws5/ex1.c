#include <stdio.h>
#define ARR_SIZE 10

void Print(int x);

struct print_me
{
	int num;
	void (*pf)(int);
};

int main()
{
	size_t i = 0;

	struct print_me print_arr[ARR_SIZE] = {{0}};
	
	for (i = 0; i < ARR_SIZE; ++i)
	{
		print_arr[i].num = (i + 1) * 2;
		print_arr[i].pf = Print;
	}
	for (i = 0; i < ARR_SIZE; ++i)
	{
		print_arr[i].pf(print_arr[i].num);
	}	

	
	return 0;
}

void Print(int x)
{
	printf("%d\n", x);
	return;
}
