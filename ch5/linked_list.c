// 先頭のノードを示すポインタ
// 後は[データ、ポインタ]の構造体を数珠つなぎ、最後尾のポインタは NULL
// ノードの挿入削除が簡単O(1)だが、アクセスがO(n)
// 柔軟に値を追加したいので、ヒープ領域で動的にメモリ確保する

#include <stdlib.h>
#include <stdio.h>

#define SUCCESS 1
#define FAILURE 0

typedef int data_t;

typedef struct nodetag
{
    data_t data;
    struct nodetag *next;
} node_t;

node_t *nodeNew(data_t dt, node_t *nxt)
{
    node_t *ndPtr;
    ndPtr = malloc(sizeof(node_t));
    if (ndPtr == NULL)
    {
        return NULL; // 割当失敗
    }
    else
    {
        ndPtr->data = dt;
        ndPtr->next = nxt;
        return ndPtr;
    }
}

// 先頭
int nodePrepend(node_t **ndPtrPtr, data_t dt)
{
    node_t *ndPtr;

    ndPtr = nodeNew(dt, *ndPtrPtr);
    if (ndPtr == NULL)
        return FAILURE;
    *ndPtrPtr = ndPtr;
    return SUCCESS;
}

// 末尾
int nodeAppend(node_t **ndPtrPtr, data_t dt)
{
    node_t *ndPtr;

    ndPtr = nodeNew(dt, NULL);
    if (ndPtr == NULL)
        return FAILURE;

    // かっこいい書き方しすぎだろここ・・・
    while (*ndPtrPtr != NULL) // ここは list が空の場合実行されない
    {
        ndPtrPtr = &((*ndPtrPtr)->next); // 連結リストの最後尾の *next のポインタを取得して代入
                                         // 代入により ndPtrPtr は *list へのポインタではなくなる
    }
    *ndPtrPtr = ndPtr; // *list が空の場合、ここは *list を上書きする
                       // *next のポインタを新しい値を示すポインタで上書きする

    return SUCCESS;
}

int nodeInsert(node_t **ndPtrPtr, int n, data_t dt)
{
    node_t *ndPtr;

    if (n < 0)
        return FAILURE;

    for (int i = 0; i < n && *ndPtrPtr != NULL; i++)
    {
        ndPtrPtr = &((*ndPtrPtr)->next);
    }

    ndPtr = nodeNew(dt, *ndPtrPtr);
    if (ndPtr == NULL)
        return FAILURE;
    *ndPtrPtr = ndPtr;
    return SUCCESS;
}

int nodeDelete(node_t **ndPtrPtr, int n)
{
    node_t *ndPtr;

    while (n > 0 && *ndPtrPtr != NULL)
    {
        ndPtrPtr = &((*ndPtrPtr)->next); // n の一つ手前の *next へのポインタ（つまり n）
        n--;
    }

    if (*ndPtrPtr != NULL)
    {
        ndPtr = (*ndPtrPtr)->next; // n の *next を取り出す
        free(*ndPtrPtr);           // n を取り出して free
        *ndPtrPtr = ndPtr;         // n の一つ手前の *next を、n の *next で置き換える
    }
}

int listPrint(node_t *ndPtr)
{
    printf("{");
    while (ndPtr != NULL)
    {
        printf("%d", ndPtr->data);
        ndPtr = ndPtr->next;
    }
    printf("}\n");
}

int main()
{
    node_t *list = NULL;
    nodeAppend(&list, 1);
    printf("%d\n", list->data);
    listPrint(list);
    nodeAppend(&list, 2);
    nodeAppend(&list, 4);
    printf("%d\n", list->data);
    listPrint(list);
    nodePrepend(&list, 3);
    printf("%d\n", list->data);
    listPrint(list);
}
