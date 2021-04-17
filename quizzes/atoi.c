#include <stdio.h> /* printf */

#define DEC_DIGITS 10

int AtoiBase10(const char *s);
static void AtoITest();

int main()
{
	AtoITest();
	
	return 0;
}



int AtoiBase10(const char *s)
{
    int to_num = 0;
	int sign = 1;

	while (' ' == *s)
	{
		++s;
	}
	if ('-' == *s)
	{
		sign = -1;
		++s;
	}
	
    while (('\0' != *s) && ('0' <= *s && '9' >= *s))
    {
        to_num = (to_num * DEC_DIGITS) + *s - '0';
		++s;
    }
 
    return to_num * sign;
}

static void AtoITest()
{
	char *str_tests[] = {"1", "0", "-1", "20000001", "-2000001", "200g13031"};
	int exp_nums[] = {1, 0, -1, 20000001, -2000001, 200};
	size_t size_of_arr = sizeof(exp_nums) / sizeof(exp_nums[0]); 
	size_t i = 0;
	
	for (i = 0; i < size_of_arr; ++i)
	{
		if (AtoiBase10(str_tests[i]) != exp_nums[i])
		{
			printf("number #%ld from string '%s' base %d: %d, expected: %d.\n",i ,str_tests[i], AtoiBase10(str_tests[i]), 10, exp_nums[i]);	
		}
	}
	return;
}
