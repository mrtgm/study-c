#include <stdio.h>
#include <stdlib.h>

typedef int data_t;

typedef struct node
{
    data_t data;
    struct node *next;
} Node;

#define ERROR 1
#define SUCCESS 0

Node *newList()
{
    Node *n = malloc(sizeof(Node));
    n->data = 1;
    n->next = NULL;
    return n;
}

Node *append(int x, Node *list)
{

    Node **plist = &list;
    while (*plist != NULL)
    {
        plist = &((*plist)->next); // ここは値じゃなくて、list->next へのポインタを取るようにしたい
                                   // つまり、ポインタのポインタになる 単純に list->next ってすると値が入るだけだから
                                   // ポインタのポインタを参照外しすることで、ポインタそのものの向き先を変えられる
    }
    Node *new_list = malloc(sizeof(Node));
    new_list->data = x;
    new_list->next = NULL;
    *plist = new_list;
    return list;
}

Node *prepend(int x, Node **list)
{

    Node *new_list = malloc(sizeof(Node));
    new_list->data = x;
    new_list->next = *list;
    *list = new_list;
    return new_list;
}

Node *insert(int x, int i, Node **list)
{
    if (x < 1)
        return NULL;

    for (int _i = 1; *list != NULL && _i < i; _i++)
    {
        list = &((*list)->next);
    }
    Node *new_list = malloc(sizeof(Node));
    Node **temp = list;
    new_list->data = x;
    new_list->next = *temp;
    *list = new_list;
    return new_list;
}

void rem(int i, Node **list)
{
    if (i < 1)
        return;

    Node **current = list;
    Node *prev = NULL;
    for (int _i = 1; *current != NULL && _i < i; _i++)
    {
        prev = *current;
        current = &((*current)->next);
    }

    if (prev == NULL)
    {
        // 直接リストの先頭を更新
        Node *temp = *current; // 一時的に削除するノードを保持
        *list = temp->next;
        free(temp);
        // temp = NULL; // 解放されたポインタをNULLに設定
    }
    else if (*current != NULL)
    {

        // prev->next = (*current)->next;
        // free(*current);　free するとき、

        // 正しくノードを削除
        Node *temp = *current; // 一時的に削除するノードを保持
        prev->next = (*current)->next;
        printf("%p || %p\n", temp->next, *current); // なんでこれのポインタが同じに・・・・？
        free(temp);
        // temp = NULL; // 解放されたポインタをNULLに設定
    }
}

void rem2(int i, Node **list)
{
    if (i < 1 || *list == NULL)
        return;

    Node **current = list;
    Node *nodeToDelete = NULL;

    for (int _i = 1; *current != NULL && _i < i; _i++)
    {
        current = &((*current)->next);
    }

    nodeToDelete = *current; // NodeTo

    if (nodeToDelete != NULL)
    {
        *current = nodeToDelete->next;
        free(nodeToDelete);
    }
}

void print(Node *list)
{
    printf("{");
    while (list != NULL)
    {
        printf("%d", list->data);
        if (list->next != NULL)
            printf(", ");
        list = list->next;
    }
    printf("}\n");
}

int main()
{
    Node *n = newList();

    append(1, n);
    append(5, n);
    printf("%p: root\n", n);
    prepend(12, &n);
    print(n);
    insert(9, 2, &n);
    print(n);
    rem(3, &n);
    print(n);
    rem(1, &n);
    print(n);
    rem(2, &n);
    print(n);

    return 0;
}
