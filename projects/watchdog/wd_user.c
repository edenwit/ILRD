#include <stdio.h>
#include <sys/types.h> /* pid_t */
#include <unistd.h>

#include "watchdog.h"

#define UNUSED(X) ((void)(X))
#define RUNS 1000

void towerOfHanoi(int n, char from_rod, char to_rod, char aux_rod);


int main(int argc, char *argv[])
{
	size_t i = 0;
	int n = 20; /* Number of disks */
	
	UNUSED(argc);

    printf("Hi im the user. blah blah blah. pid: %ld\n", getpid());
	
    printf("now im gonna activate the WatchDog security\n");
	WDStart(argv, 5, 1);

	for (i = 0; i < RUNS; ++i)
	{
		printf("progrem running %ld / %ld\n", i, RUNS);
		towerOfHanoi(n, 'A', 'C', 'B');  /* A, B and C are names of rods */
		printf("tower for %d disks\n", n);
	}

	WDStop();
	printf("Deactivate the WatchDog security\n");

	return (0);
}
  
void towerOfHanoi(int n, char from_rod, char to_rod, char aux_rod)
{
    if (n == 1)
    {
/*         printf("\n Move disk 1 from rod %c to rod %c", from_rod, to_rod);
 */        return;
    }
    towerOfHanoi(n-1, from_rod, aux_rod, to_rod);
/*     printf("\n Move disk %d from rod %c to rod %c", n, from_rod, to_rod);
 */    towerOfHanoi(n-1, aux_rod, to_rod, from_rod);
}