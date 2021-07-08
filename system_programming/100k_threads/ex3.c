#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>


#define NUM_OF_THREADS (100000)

static void *AssignValToArr(void *i);
static void PrintArr(int *arr);

pthread_t thread_id[NUM_OF_THREADS] = {0};
int arr[NUM_OF_THREADS] = {0};

pthread_attr_t attr = {0};

pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

int main()
{
    pthread_t thread_id[NUM_OF_THREADS] = {0};
    size_t i = 0;

    while (i < NUM_OF_THREADS)
    {
        while (0 != pthread_create((thread_id + i), NULL, AssignValToArr, (void *)i));
        pthread_detach(*(thread_id + i));
        ++i;
    }

    sleep(10);

    PrintArr(arr);

    return (0);
}

static void *AssignValToArr(void *i)
{
    arr[(size_t)i] = (size_t)i;

    return (NULL);
}

static void PrintArr(int *arr)
{
    size_t i = 0;

    for (i = 0; i < NUM_OF_THREADS; ++i)
    {
        if (i != (size_t)arr[i])
        {
            printf("failed at #%ld : %d\n", i, arr[i]);
            return;
        }
    }

    return;
}