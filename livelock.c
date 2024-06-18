#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int condition1 = 0;
int condition2 = 0;

void *thread_func1(void *arg)
{
    while (1)
    {
        // pthread_mutex_lock(&mutex);
        if (condition1 == 0)
        {
            printf("Thread 1: working\n");
            condition1 = 1;
            // pthread_mutex_unlock(&mutex);
            sleep(1); // Simulate some work
        }
        else
        {
            // pthread_mutex_unlock(&mutex);
            sched_yield(); // Yield to the other thread
        }
    }
    return NULL;
}

void *thread_func2(void *arg)
{
    while (1)
    {
        // pthread_mutex_lock(&mutex);
        if (condition2 == 0)
        {
            printf("Thread 2: working\n");
            condition2 = 1;
            // pthread_mutex_unlock(&mutex);
            sleep(1); // Simulate some work
        }
        else
        {
            // pthread_mutex_unlock(&mutex);
            sched_yield(); // Yield to the other thread
        }
    }
    return NULL;
}

int main()
{
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, thread_func1, NULL);
    pthread_create(&thread2, NULL, thread_func2, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}
