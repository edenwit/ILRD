/*parent.c: the parent program*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>

#define UNUSED(X) ((void)X)

static void TestPhase1();
static void TestPhase2(char *argv[]);

int main (int argc, char *argv[])
{
	UNUSED(argc);

	TestPhase1();
	TestPhase2(argv);

	return (0);
}


static void TestPhase1()
{
    int pid = 0;
    int status = 0;
	int ret = 0;
    char *myargs [] = { NULL };
    char *myenv [] = { NULL };

	while (!status)
	{
		pid = fork();

		if (0 == pid)
		{
			execve ("dummy", myargs, myenv);
		}

		printf("parent pid: %d Waiting for child pid: %d.\n", getpid(), pid);

		ret = waitpid (pid, &status, 0);

		if (-1 == ret)
		{
			printf ("parent:error\n");
		}

		if (ret == pid)
		{
			printf ("Parent: Child process waited for.\n");
		}

		printf("status: %d\n",WEXITSTATUS(status));
	}

	return;
}

static void TestPhase2(char *argv[])
{
	int status = 0;

	while (((status = system(argv[1])), (!WIFSIGNALED(status) &&
											(WTERMSIG(status) != SIGINT && WTERMSIG(status) != SIGQUIT)) &&
												WIFEXITED(status) && (WEXITSTATUS(status) == EXIT_SUCCESS)))
		{
			printf("returnd status :%d\n", WEXITSTATUS(status));
		}

		if (SIGINT == WTERMSIG(status))
		{
			printf("process was interruped\n");
		}
		if (SIGQUIT == WTERMSIG(status))
		{
			printf("process was SIGQUIT\n");
		}

		return;
}
