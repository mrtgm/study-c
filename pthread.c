#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_INCREMENTS 1000000

int counter = 0; // 共有リソース

void *increment_counter(void *arg)
{
    for (int i = 0; i < NUM_INCREMENTS; ++i)
    {
        counter++; // 競合状態が発生する箇所
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

    // 期待される結果は 2 * NUM_INCREMENTS ですが、実際の結果は異なる可能性があります
    printf("Final counter value: %d\n", counter);

    return 0;
}
