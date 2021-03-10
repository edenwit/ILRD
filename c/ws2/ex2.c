#include <stdio.h>  /* size_t, printf */
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */
int *CopyArr (int *p_arr, size_t len);
int IntArrCmp(const int *p1, const int *p2, size_t len); /* assume both arrays are equares */


int main()
{
	int arr_1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	size_t arr_size = sizeof(arr_1) / sizeof(arr_1[0]);
	int *arr_2 = CopyArr(arr_1, arr_size);
	size_t i = 0;

	printf("Array 1: \n");
	for ( i = 0; i < arr_size; i++ )
	{
		printf("%d ",arr_1[i]);
	}
	printf("\nArray 2: \n");
	for ( i = 0; i < arr_size; i++ )
	{
		printf("%d ",arr_2[i]);
	}
		printf("\n");
	if(IntArrCmp(arr_1,arr_2,arr_size) == 0)
	{
		printf ("Success!\n");
	}
	else
		printf("Fail!\n");
	return 0;
}

int *CopyArr (int *p_arr, size_t len)
{	
	size_t remain_len = len;

    int *p_copy = (int *)malloc(len * sizeof(int));

	while(remain_len > 0)
    {
    	*p_copy = *p_arr;
		++p_copy; ++p_arr;
		--remain_len;
    }

    return p_copy - len;
}

int IntArrCmp(const int *p1, const int *p2, size_t len)
{
	assert (p1 != NULL && p2 != NULL);
	while(0 < len)	
	{
		if( *p1 == *p2)
		{
			++p1; ++p2;
		}
		else
		{
			return 1;
		}
		--len;
	}
	return 0;
}

