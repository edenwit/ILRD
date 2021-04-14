#include <stddef.h> /* size_t */
#include <stdio.h> /* printf */


#include "c_exam.h"

static void FlipDigitsInNumTest();


int main()
{
	FlipDigitsInNumTest();

	return 0;
}




static void FlipDigitsInNumTest()
{
	int test_arr[] = {1234, -123, 0, 987654321, 123456789, 11000, -211};
	int exp_arr_[] = {4321, -321, 0, 123456789, 987654321, 11, -112};
	size_t arr_size = sizeof(test_arr) / sizeof(test_arr[0]);
	size_t i = 0;
	
	for (i = 0; i < arr_size; ++i)
	{
		if (FlipDigitsInNum(test_arr[i]) != exp_arr_[i])
		{
			printf("Test #%ld failed. tested: %d,\t\t actual: %d,\t\t expected: %d.\n", i + 1, test_arr[i], FlipDigitsInNum(test_arr[i]), exp_arr_[i]);
		}
	}
	
}
