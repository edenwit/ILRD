#include <stddef.h> /* size_t */
#include <stdio.h>  /* printf */

int Add1(int n);
static void Add1Test();

int main()
{
	Add1Test();

	return 0;
}

int Add1(int n)
{
    int x = 1;
        
    while (n & x)
    {
        n = n ^ x;
        x = x << 1;
    }
    n = n ^ x;
    
    return n;
}

static void Add1Test()
{
	const int input1_arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -1};
	size_t arr_size = sizeof(input1_arr) / sizeof(input1_arr[0]);
	size_t i = 0;
	int res = 0; 

	for (i = 0; i < arr_size; ++i)
	{
		res = Add1(input1_arr[i]);

		if (res != input1_arr[i] + 1)
		{
			printf("Failure at test #%ld: tested: %d, expected: %d, actual: %d\n", i + 1, input1_arr[i], input1_arr[i] + 1, res);
		}
	}
	
	return;	
}
