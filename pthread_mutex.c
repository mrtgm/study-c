#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_INCREMENTS 1000000

int counter = 0; // 共有リソース
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *increment_counter(void *arg)
{
    for (int i = 0; i < NUM_INCREMENTS; ++i)
    {
        pthread_mutex_lock(&mutex);
        counter++; // 排他制御で保護された箇所
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main()
{
    pthread_t thread1, thread2;

    // 2つのスレッドを作成
    if (pthread_create(&thread1, NULL, increment_counter, NULL) != 0)
    {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }
    if (pthread_create(&thread2, NULL, increment_counter, NULL) != 0)
    {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    // スレッドの完了を待機
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // 期待される結果は 2 * NUM_INCREMENTS
    printf("Final counter value: %d\n", counter);

    // ミューテックスの破棄
    pthread_mutex_destroy(&mutex);

    return 0;
}
