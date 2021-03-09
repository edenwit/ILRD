#include <stdio.h> 							//change from stdio.c

int main(int argc, char *argv[]) 					// change func type to int, change 'Main' to 'main'
{
	int num = 0; 							// not recommended to declare without assignining. initilized to 0.
	const int num2 = 6;
	int num3;							// removed the const
	
	printf("%d\n", num);						// unneccesary line, no value in num yet.
	scanf("%d", &num);						// scanning to &num, not num
	printf("100 divided by %d is %f\n", num, 100/(float)num); 	// 100/num is int but print as %f
	
	char ch = 97;
	
	num3 = num2 - 5; 						// can't assign to const - changed type in begining.
	printf("%d\n", num3); 						// change print from %f to %d
	
	num = 4;							// int can't get float value. changed to 4.
	//(double)num = 4.7;						// error! can't cast int type to another type. 
	
	num = 2 * num++;						// no sequance point between side-effects. unknown order.
	
	return (0);
}
