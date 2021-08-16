
#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <stdatomic.h>


#define LOOPS 100
#define UNUSED(X) ((void)X)

static void *Foo(void *arg);

atomic_size_t g_x = 0;

int main()
{
	pthread_t thread1 = {0};
	pthread_t thread2 = {0};
	pthread_t thread3 = {0};
	pthread_t thread4 = {0};
	pthread_t thread5 = {0};
	pthread_t thread6 = {0};
	pthread_t thread7 = {0};
	pthread_t thread8 = {0};	

	size_t j = 0;

	for (j = 0; j < 100000; ++j)
	{

		if ((0 != pthread_create(&thread1, NULL, Foo, NULL))
		||(0 != pthread_create(&thread2, NULL, Foo, NULL))
		||(0 != pthread_create(&thread3, NULL, Foo, NULL))
		||(0 != pthread_create(&thread4, NULL, Foo, NULL))
		||(0 != pthread_create(&thread5, NULL, Foo, NULL))
		||(0 != pthread_create(&thread6, NULL, Foo, NULL))
		||(0 != pthread_create(&thread7, NULL, Foo, NULL))
		||(0 != pthread_create(&thread8, NULL, Foo, NULL)))
		{
			return (1);
		}

		pthread_join(thread1, NULL);
		pthread_join(thread2, NULL);
		pthread_join(thread3, NULL);
		pthread_join(thread4, NULL);
		pthread_join(thread5, NULL);
		pthread_join(thread6, NULL);
		pthread_join(thread7, NULL);
		pthread_join(thread8, NULL);		

		if (LOOPS * 8 != g_x)
		{
			printf("g_x is %d\n", g_x);
		}

		g_x = 0;
	}
	
 	return (0);
}

static void *Foo(void *arg)
{
	sig_atomic_t i = 0;

	UNUSED(arg);

	for (i = 0; i < LOOPS; ++i)
	{
 		/* __sync_fetch_and_add(&g_x, 1); */ 
		++g_x; 
	}

	return (NULL);
}