#include <stdio.h> /* printf */
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */
#include <string.h> /* memcpy */

#define CHARS 256

int IsNumInArr(char *arr, size_t arr_size, char to_find);
static void IsNumInArrTest();

void ShiftArr(char *arr, size_t arr_size, size_t n);
void ShiftArrTest();

void PrintArr(char * arr, size_t arr_size);

int main()
{
	IsNumInArrTest();
	ShiftArrTest();

	return 0;
}

int IsNumInArr(char *arr, size_t arr_size, char to_find)
{
    int LUT[CHARS] = {0};
 	size_t i = 0;
 	
    for (i = 0; i < arr_size; ++i)
    {
		LUT[(int)(arr[i])] = 1;
    } 
    
    return (LUT[(int)to_find]);
}

void ShiftArr(char *arr, size_t arr_size, size_t n)
{
	char *temp_arr = (char *)malloc(sizeof(char) * n);
	n = n % arr_size;

	assert(arr);
	
	memcpy(temp_arr, arr + (arr_size - n), n);
	memmove(arr + n, arr, (arr_size - n));
	memmove(arr, temp_arr, n);			
	
	free(temp_arr);
	
	return;	
}



static void IsNumInArrTest()
{
	char chars_arr[] = {'a', 't', 'c', '1', '1', '1', 'Z'};
	size_t arr_size = sizeof(chars_arr) / sizeof(chars_arr[0]);
	
	printf("Attempt 1: %d.\n", IsNumInArr(chars_arr, arr_size, 'Z'));
	printf("Attempt 1: %d.\n", IsNumInArr(chars_arr, arr_size, 'c'));	
	printf("Attempt 1: %d.\n", IsNumInArr(chars_arr, arr_size, 'x'));		

	return;
}


void ShiftArrTest()
{
	char chars_arr[] = {'a', 't', 'c', '1', '1', '1', 'Z'};
	size_t arr_size = sizeof(chars_arr) / sizeof(chars_arr[0]);
	
	printf("Attempt 1: \n Before: \n");
	PrintArr(chars_arr, arr_size);
	
	ShiftArr(chars_arr, arr_size, 5);
	
	printf("Attempt 1: \n After: \n");
	PrintArr(chars_arr, arr_size);	

	return;	
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
