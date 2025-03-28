#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

void *thread_func1(void *arg)
{
    pthread_mutex_lock(&mutex1);
    printf("Thread 1: locked mutex1\n");

    // Simulate some work

    printf("Thread 1: trying to lock mutex2\n");
    pthread_mutex_lock(&mutex2);
    printf("Thread 1: locked mutex2\n");

    pthread_mutex_unlock(&mutex2);
    pthread_mutex_unlock(&mutex1);
    return NULL;
}

void *thread_func2(void *arg)
{
    pthread_mutex_lock(&mutex2);
    printf("Thread 2: locked mutex2\n");

    // Simulate some work

    printf("Thread 2: trying to lock mutex1\n");
    pthread_mutex_lock(&mutex1);
    printf("Thread 2: locked mutex1\n");

    pthread_mutex_unlock(&mutex1);
    pthread_mutex_unlock(&mutex2);
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
