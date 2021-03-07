int flip_digits (int num)
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

int main()
{
	int i;
	int arr_test_inputs[]={1234,51,0,9,-34,-3456,3134,12340, 1004};
	int arr_test_results[]={4321,15,0,9,-43,-6543,4313,4321, 4001};
	for (i=0;i<8;i++)
	{
		printf("Input: %d\n",arr_test_inputs[i]);
		printf("Result expacted: %d\n",arr_test_results[i]);
		printf("Actual result: %d\n",flip_digits(arr_test_inputs[i]));
			
	}
}

