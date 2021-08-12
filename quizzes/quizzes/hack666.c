#include <stdio.h>
void func2(void *arg)
{
	long f2;
	printf("Enter func2\n");

	/* Area2 */
	*((&f2) + 3) = *((&f2) + 7);
	*((&f2) + 7) = *((&f2) + 11);


	printf("Exit func2\n");
}
void func1()
{
	long f1;
	printf("Enter func1\n");
	func2(&f1);
	printf("Exit func1\n");
}

int main()
{
	const long x = 1;
	long y = 5;

	/* Area1 */
	/*par 1:  *((long *)&x) = 666; */
	/*par 2:  *(((long *)&y) + 1) = 666; */

	printf("x=%lu\n", x);
	func1();

	printf("Exit main\n");

	return 0;
}