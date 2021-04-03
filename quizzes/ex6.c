#include <string.h>
#include <assert.h>
#include <stdio.h>

int IsRotation(const char *s1, const char *s2);

int main()
{
	char *test_arr[] = {"12345", "abcdef", "badmentor", "hello"};
	char *exp_arr[] = {"45123", "defabc", "mentorbad", "ohell"};
	size_t i = 0;
	size_t size_of_array = sizeof(test_arr) / sizeof(test_arr[0]);

	for (i = 0; i < size_of_array; ++i)
	{
		if (!IsRotation(test_arr[i], exp_arr[i]))
		{
			printf ("Test with %s and exp %s failed.\n", test_arr[i], exp_arr[i]);
		}
	}
	
	return 0;
}

int IsRotation(const char *s1, const char *s2)
{
	size_t len_s1 = 0;
	size_t i = 0;
	char *ps2 = NULL;
	
	assert(s1);
	assert(s2);
	
	ps2 = (char *)s2;
	len_s1 = strlen(s1);
	
	if (len_s1 != strlen(ps2))
	{
		return 0;
	}
	
	while (*ps2 != '\0' && *ps2 != *s1)
	{
		if (0 == strncmp(s1, ps2 + i, (len_s1 - i)))
		{
			if (0 == strncmp((s1 + len_s1 - i), ps2, i))
			{
				return 1;
			}
		}
		++i;
		++s2;
	}
	return 0;
}
