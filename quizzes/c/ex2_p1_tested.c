#include <stdio.h> /* printf */

void TF(int num);

int main()
{
	int num=51;
	
	TF(num);
	
	return (0);
}

void TF(int num)
{
	int i = 0;
	int does_div = 0;
	for (i=0; i< num; ++i)
	{
		if ((i+1) % 3 == 0)
		{
			printf("T");
			does_div = 1;
		}
		if ((i+1) % 5 == 0)
		{
			printf("F");
			does_div = 1;
		}		
		if (does_div == 0)
		{
			printf("%d",i + 1);
		}
		printf("\n");
		does_div = 0;
	}
}
