#include <pthread.h>
#include <semaphore.h> /* sem_open, sem_close */
#include "scope_lock.hpp"
#include <fcntl.h>     /*      For O_* constants       */
#include <iostream>    


#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>

using ilrd::ScopeLock;

const size_t COUNT = 5;

void *MutexRaceCondTest(void *num);
void *SemRaceCondTest(void *num);
void *BMutexRaceCondTest(void *num);

class Mutex
{
public:
    Mutex() 
    {
        pthread_mutex_init(&m_lock, NULL);
    }
    ~Mutex()
    {
        pthread_mutex_destroy(&m_lock);
    }
    void lock()
    {
        pthread_mutex_lock(&m_lock);
    }
    void unlock()
    {
        pthread_mutex_unlock(&m_lock);
    }
private:
    pthread_mutex_t m_lock;
};

class Semophore
{
public:
    Semophore() : sem(sem_open("semo", O_CREAT, 0666, 0))
    {
        ;
    }
    ~Semophore()
    {
        sem_close(sem);
    }
    void lock()
    {
        sem_wait(sem);
    }
    void unlock()
    {
        sem_post(sem);
    }
private:
    sem_t *sem;
};

Semophore sem;
Mutex mut;
boost::mutex bmut;

int main()
{
    pthread_t thread = {0};
    pthread_t thread2 = {0};

    // std::cout << "------------Semophore Test --------------" <<std::endl;

    // pthread_create(&thread, NULL, SemRaceCondTest, NULL);
    // pthread_create(&thread2, NULL, SemRaceCondTest, NULL);
    // pthread_join(thread,NULL);
    // pthread_join(thread2,NULL);

    std::cout << "------------Pthread Mutex Test --------------" <<std::endl;

    pthread_create(&thread, NULL, MutexRaceCondTest, NULL);
    pthread_create(&thread2, NULL, MutexRaceCondTest, NULL);
    pthread_join(thread,NULL);
    pthread_join(thread2,NULL);

    std::cout << "------------Boost Mutex Test --------------" <<std::endl;

    pthread_create(&thread, NULL, BMutexRaceCondTest, NULL);
    pthread_create(&thread2, NULL, BMutexRaceCondTest, NULL);
    pthread_join(thread,NULL);
    pthread_join(thread2,NULL);    
    




    return (0);
}

void *MutexRaceCondTest(void *num)
{
    (void)num;

    size_t i = 0;

    ScopeLock <Mutex>m_l(&mut);
    for (i = 0 ; i < COUNT ; ++i)
    {
        sleep(1);
        std::cout << i << std::endl;
    }


    return (NULL);
}

void *SemRaceCondTest(void *num)
{
    (void)num;

    size_t i = 0;

    ScopeLock <Semophore>s_l(&sem);
    for (i = 0 ; i < COUNT ; ++i)
    {
        sleep(1);
        std::cout << i << std::endl;
    }

    return (NULL);
}

void *BMutexRaceCondTest(void *num)
{
    (void)num;

    size_t i = 0;

    ScopeLock <boost::mutex>bm_l(&bmut);
    for (i = 0 ; i < COUNT ; ++i)
    {
        sleep(1);
        std::cout << i << std::endl;
    }

    return (NULL);
}