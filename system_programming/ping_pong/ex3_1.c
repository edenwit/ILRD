#define _POSIX_SOURCE
#define _POSIX_C_SOURCE 199309L

#include <signal.h>	   /* singals */
#include <stdio.h>	   /* printf */
#include <unistd.h>	   /* pause, sleep */
#include <sys/types.h> /* pid_t */
#include <stdlib.h>

#define UNUSED(X) ((void)X)

int flag = 1;

void Handler(int sig);

int main(int argc, char *argv[])
{
	pid_t pid = 0;
	struct sigaction handler = {0};

	handler.sa_handler = Handler;

	sigaction(SIGUSR2, &handler, NULL);

	pid = (pid_t)atoi(argv[1]);

	if (0 > pid)
	{
		printf("argv error.\n");
		return (1);
	}

	/* if process is the child */

	while (1)
	{
		if (1 == flag)
		{
			printf("PING\n");

			flag = 0;
			kill(pid, SIGUSR1);
		}
	}

	return (0);
}

/* signal handler functions */

void Handler(int sig)
{
	UNUSED(sig);
	flag = 1;

	return;
}