#include <stdio.h> /* printf, size_t */

void ReverseAndDecapitalize(char *str1, size_t arr_len);

int main()
{
	char str[]="I LOVE NEW YORK";
	size_t lengh = (sizeof(str) / sizeof(str[0])) - 1;
	printf("String before swap: \t %s\n",str);
	ReverseAndDecapitalize(str, lengh);
	printf("String after  swap: \t %s\n",str);
	return (0);
}

void ReverseAndDecapitalize(char *str1, size_t arr_len)
{
	char temp = 0;
	size_t runs = arr_len / 2;
	while( runs > 0)
	{
		if (*str1 >= 65 && *str1 <= 90)
		{
			*str1 += 32;		
		}
		if (*(str1 + (runs*2)) >= 65 && *(str1 + (runs*2)) <= 90)
		{
			*(str1 + (runs*2)) += 32;		
		}
		temp = *str1;
		*str1 = *(str1 + (runs*2));
		*(str1 + (runs*2)) = temp;		
		--runs;
		++str1;
	}
	if (arr_len % 2 == 1 && *(str1)  >= 65 && *(str1) <= 90)
	{
		*(str1) += 32;			
	}
}
