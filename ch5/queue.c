#include <stdio.h>

#define QUEUE_SIZE 10
#define SUCCESS 1
#define FAILURE 0

typedef int data_t;

// キュー, 待ち行列, FIFO, 最初の人が最初に出る

data_t queue_data[QUEUE_SIZE];
int queue_head; // 先頭
int queue_num;  // 個数

// データを末尾に追加する
int enqueue(data_t enq_data)
{
    if (queue_num < QUEUE_SIZE)
    {
        queue_data[(queue_head + queue_num) % QUEUE_SIZE] = enq_data; // リングバッファ、先頭より前の空きスペースの有効活用
        queue_num++;
        return SUCCESS;
    }

    else
    {
        return FAILURE;
    }
}

// 先頭のデータを取り出し、データの先頭を移動する
// 　先頭要素の削除は計算量がO(n)だから、先頭を示す数値を持てばO(1)になる
int dequeue(data_t *deq_data)
{
    if (queue_num > 0)
    {
        *deq_data = queue_data[queue_head];
        queue_head = (queue_head + 1) % QUEUE_SIZE;
        queue_num--;
        return SUCCESS;
    }
    else
    {
        return FAILURE;
    }
}

void queuePrint()
{
    for (int i = 0; i < QUEUE_SIZE; i++)
    {
        if ((queue_head + queue_num <= QUEUE_SIZE && queue_head <= i && i < queue_head + queue_num) ||
            (queue_head + queue_num > QUEUE_SIZE && (queue_head <= i || i < (queue_head + queue_num) % QUEUE_SIZE)))
        // 範囲内にあることを確認
        {

            printf("%3d", queue_data[i]);
        }
        else
        {
            printf(".");
        }
    }
    printf("\n");
}

int main(int argc, char *argv[])
{

    int i;
    data_t d;
    queue_head = queue_num = 0;

    for (int i = 0; i <= 7; i++)
    {
        printf("Enqueue%3d:", i);
        enqueue(i);
        queuePrint();
    }

    for (i = 1; i <= 4; i++)
    {
        dequeue(&d);
        printf("Dequeue%3d :", d);
        queuePrint();
    }

    for (i = 8; i <= 15; i++)
    {
        printf("Enqueue%3d:", i);
        if (enqueue(i) == SUCCESS)
            queuePrint();
        else
            printf("Full Queue");
    }

    while (queue_num > 0)
    {
        dequeue(&d);
        queuePrint();
    }

    return 0;
}
