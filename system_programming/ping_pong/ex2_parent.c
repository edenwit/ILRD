#define _POSIX_SOURCE

#include <signal.h> /* singals */
#include <stdio.h> /* printf */
#include <unistd.h> /* pause, sleep */
#include <sys/types.h> /* pid_t */

#define UNUSED(X) ((void)X)

int flag = 0;

void Handler(int x);
  
int main()
{
    pid_t pid = 0;
	struct sigaction handler = {0};
	char *myargs [] = { NULL };
    char *myenv [] = { NULL };
	
	handler.sa_handler = Handler;

	sigaction(SIGUSR1, &handler, NULL);
	sigaction(SIGUSR2, &handler, NULL);	

	/* get child process */
	pid = fork();
    
    if (0 > pid)
	{
        printf("fork error.\n");
        return(1);
    }
    
	/* if process is the child */
	else if (0 == pid)
	{
		execve ("ex2_child", myargs, myenv);
	}
  
    else /* parent */
    {
		while (1)
		{
			if (1 == flag)
			{
				printf("PING\n");

				flag = 0;
				kill(pid, SIGUSR1);
			}
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