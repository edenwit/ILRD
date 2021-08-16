#include <stdio.h>

void Main(int argc, char *argv[])
{
	int num;
	const int num = 6;
	const int num3;
	
	printf("%d\n", num);
	scanf("%d", num);
	printf("100 divided by %d is %f\n", num, 100/num);
	
	char ch = 97;
	
	num3 = num2 - 5;
	printf("%f\n", num3);
	
	num = 4.7;
	(double)num = 4.7;
	
	num = 2 * num++;
	
	return (0);
}
