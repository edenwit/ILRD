/*
gd wd_user.c watchdog.c ../../ds/src/heap_scheduler/heap_scheduler.c  -I ../../ds/include/ ../../ds/src/uid/uid.c ../../ds/src/task/task.c ../../ds/src/heap/heap.c ../../ds/src/heap_priority_queue/heap_priority_queue.c ../../ds/src/vector/vector.c  -pthread watchdog.h -o wd_user
*/

#include <stdio.h>	   /* printf */
#include <sys/types.h> /* pid_t */
#include <unistd.h>
#include <signal.h> /* singals */

#include "watchdog.h"

#define UNUSED(X) ((void)(X))
#define RUNS (5)
#define LOOPS (2)

void towerOfHanoi(int n, char from_rod, char to_rod, char aux_rod);

int main(int argc, char **argv)
{
	size_t i = 0;
	size_t j = 0;
	int n = 30; /* Number of disks */

	UNUSED(argc);

	for (j = 1; j <= LOOPS; ++j)
	{
		printf("Hi im the user. blah blah blah. pid: %d\n", getpid());

		printf("now im gonna activate the WatchDog. %ld / %d\n", j, LOOPS);
		WDStart(argv, 5, 1);

		for (i = 1; i <= RUNS; ++i)
		{
			printf("User %d: progrem running %ld / %d\n", getpid(), i, RUNS);
			towerOfHanoi(n, 'A', 'C', 'B'); /* A, B and C are names of rods */
		}

		WDStop();

		printf("Deactivate the WatchDog security  %ld / %d\n", j, LOOPS);
	}

	return (0);
}

void towerOfHanoi(int n, char from_rod, char to_rod, char aux_rod)
{
	if (n == 1)
	{
		/*         printf("\n Move disk 1 from rod %c to rod %c", from_rod, to_rod);  */
		return;
	}
	towerOfHanoi(n - 1, from_rod, aux_rod, to_rod);
	/*     printf("\n Move disk %d from rod %c to rod %c", n, from_rod, to_rod);
 */
	towerOfHanoi(n - 1, aux_rod, to_rod, from_rod);
}