#define _POSIX_SOURCE
#define _POSIX_C_SOURCE 199309L

#include <signal.h>	   /* singals */
#include <stdio.h>	   /* printf */
#include <unistd.h>	   /* pause, sleep */
#include <sys/types.h> /* pid_t */

#define UNUSED(X) ((void)X)

int flag = 0;
pid_t pid = 0;

void Handler(int sig, siginfo_t *siginfo, void *data);

int main(int argc, char *argv[])
{
	struct sigaction handler = {0};

	handler.sa_sigaction = Handler;
	handler.sa_flags = SA_SIGINFO;

	printf("PID: %d\n", getpid());

	sigaction(SIGUSR1, &handler, NULL);

	pause();

	while (1)
	{
		if (1 == flag)
		{
			printf("PONG\n");

			flag = 0;

			kill(pid, SIGUSR2);
		}
	}

	return (0);
}

/* signal handler functions */

void Handler(int sig, siginfo_t *siginfo, void *data)
{
	UNUSED(sig);

	pid = siginfo->si_pid;
	flag = 1;

	return;
}