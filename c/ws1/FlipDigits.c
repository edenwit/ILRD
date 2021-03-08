#include <stdio.h>

int FlipDigits (int num);

int main()
{	
	int result_recieved = 0;
	int i = 0;
	int arr_test_inputs[] = {1234,51,0,9,-34,-3456,3134,12340, 1004,1345};
	int arr_test_results[] = {4321,15,0,9,-43,-6543,4313,4321, 4001,54031};
	int array_size = sizeof(arr_test_inputs) / sizeof(arr_test_inputs[0]);
	for ( i = 0; i < array_size; i++ )
	{
		printf("Input: %d\t ;",arr_test_inputs[i]);
		printf("Result expacted: %d\t ;",arr_test_results[i]);
		result_recieved = FlipDigits(arr_test_inputs[i]);
		printf("Actual result: %d\t ; ",result_recieved);
		if(result_recieved == arr_test_results[i])
		{
			printf("Success!\n");
		}
		else
		{
			printf("Fail!\n");
		}
	}
}

int FlipDigits (int num)
{
	//printf("%d\n",num);
	int flip_num = 0;
	while(num != 0)
	{	
		flip_num *= 10;
		flip_num += num % 10;
		num /= 10;
	}
	//printf("%d\n",flip_num);
	return flip_num;
}
