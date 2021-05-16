#include <stdio.h> /* printf */
#include <assert.h> /* assert */
#include <math.h> /* floor */


#define CHARS 256

void FindMissingNumsMath(int *arr, int n);
void FindMissingNumsXor(int *arr, int n);

static void FindMissingNumsMathTest();
static void FindMissingNumsXorTest();

void PrintArr(char * arr, size_t arr_size);

int main()
{
	FindMissingNumsMathTest();
	FindMissingNumsXorTest();

	return 0;
}


void PrintArr(char * arr, size_t arr_size)
{
	size_t i = 0;
	for (i = 0; i < arr_size; ++i)
	{
		printf("%c ", arr[i]);

	}
	printf("\n");
		
	return;
}

void FindMissingNumsMath(int *arr, int n)
{
	long n_sum = 0;
	long arr_sum = 0;
	int missing_nums_sum = 0;
	float missing_nums_avg = 0;
	int arr_lower_than_avg_sum = 0;
	int n_lower_than_avg_sum = 0;	
    int num1 = 0;
    int num2 = 0;
    int set  = 0;
    size_t i = 0;

    assert(NULL != arr);

    for (i = 0; i < (n - 2); ++i)
    {
        arr_sum += arr[i];
    }

	n_sum = ((n * (n + 1)) / 2);

	missing_nums_sum = n_sum - arr_sum;
	missing_nums_avg = (float)missing_nums_sum / 2;
	
    for (i = 0; i < n - 2; ++i)
    {
    	if (arr[i] <= missing_nums_avg)
    	{
    		arr_lower_than_avg_sum += arr[i];
    	}
    }	
   	
	n_lower_than_avg_sum = ((int)(missing_nums_avg) * ((int)(missing_nums_avg) + 1) / 2);

	num1 = n_lower_than_avg_sum - arr_lower_than_avg_sum;
	num2 = missing_nums_sum - num1;
	
    printf("Missing Nums are: %d, %d.\n", num1, num2);
    
    return;
}

void FindMissingNumsXor(int *arr, int n)
{
	int xor_val = 0;
    int num1 = 0;
    int num2 = 0;
    int set  = 0;
    size_t i = 0;

    assert(NULL != arr);

    xor_val = arr[0];

    for (i = 1; i < n - 2; ++i)
    {
        xor_val ^= arr[i];
    }

    for (i = 1; i <= n; ++i)
    {
        xor_val ^= i;
    }

    set = xor_val & (~(xor_val - 1));

    for (i = 0; i < n - 2; i++)
    {
        if (arr[i] & set)
        {
            num1 ^= arr[i];
        }

        else
        {
            num2 ^= arr[i];
        }
    }

    for (i = 1; i <= n; ++i)
    {
        if (i & set)
        {
            num1 ^= i; 
        }

        else
        {
            num2 ^= i;
        }
    }
    printf("Missing Nums are: %d, %d.\n", num2, num1);
    
    return;
}

static void FindMissingNumsMathTest()
{
	int arr[] = {1, 2, 12, 5, 3, 4, 6, 7, 9, 10};
	size_t arr_size = sizeof(arr) / sizeof(arr[0]);
	
	FindMissingNumsMath(arr, arr_size + 2);
	
	return;
}
static void FindMissingNumsXorTest()
{
	int arr[] = {1, 2, 12, 5, 3, 4, 6, 7, 9, 10};
	size_t arr_size = sizeof(arr) / sizeof(arr[0]);
	
	FindMissingNumsXor(arr, arr_size + 2);
	
	return;
}
