#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

#define THREADS (30000)
#define NUM (1200000000)
#define RANGE (NUM / THREADS)

pthread_t threads[THREADS] = {0};
int sum_of_divisors = 0;

void *SumDivisors(void *index);
int CreateThreads(pthread_t *threads_arr);
void PrintArray(int *arr);
void TestArray(int *arr);

int main()
{
    size_t i = 0;
    void *return_val = NULL;
    size_t sum = 0;

    CreateThreads(threads);

    for (i = 0; i < THREADS; i++)
    {
        pthread_join(*(threads + i), &return_val);
        sum += (size_t)return_val;
    }

    printf("sum: %ld\n", sum);

    return 0;
}

int CreateThreads(pthread_t *threads_arr)
{
    size_t i = 0;
    size_t j = 0;

    for (i = 1; i <= NUM; i = i + RANGE)
    {
        pthread_create(threads_arr + j, NULL, SumDivisors, (void *)i);
        ++j;
    }

    return (0);
}

void *SumDivisors(void *index)
{
    size_t i = (size_t)index;
    size_t j = RANGE + ((size_t)index);
    size_t sum_of_divisors = 0;

    for (; i <= j; ++i)
    {
        if (0 == NUM % i)
        {
            sum_of_divisors += i;
        }
    }

    return ((void *)sum_of_divisors);
}