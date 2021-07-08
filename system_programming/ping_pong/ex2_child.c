#define _POSIX_SOURCE

#include <signal.h> /* singals */
#include <stdio.h> /* printf */
#include <unistd.h> /* pause, sleep */
#include <sys/types.h> /* pid_t */

#define UNUSED(X) ((void)X)

int flag = 1;

void Handler(int x);
  
int main()
{
	struct sigaction handler = {0};

	handler.sa_handler = Handler;

	sigaction(SIGUSR1, &handler, NULL);
	sigaction(SIGUSR2, &handler, NULL);

    while (1)
	{
			if (1 == flag)
			{
				printf("PONG\n");
				flag = 0;
				kill(getppid(), SIGUSR2);
			}
	}

	return (0);
}
  
/* signal handler functions */

void Handler(int x)
{
	UNUSED(x);
	flag = 1;

	return;
}