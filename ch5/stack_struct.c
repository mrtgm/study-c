#include <stdio.h>

#define MAX 1000
#define ERROR 1
#define SUCCESS 0

typedef int data_t;

typedef struct
{
    int stack_num;
    data_t stack_data[MAX];
} stack_t;

int push(stack_t *stk, data_t push_data)
{
    if (stk->stack_num < MAX)
    {
        stk->stack_data[stk->stack_num] = push_data;
        stk->stack_num++;
        return SUCCESS;
    }
    else
    {
        return ERROR;
    }
}

int pop(stack_t *stk, data_t *pop_data)
{
    if (stk->stack_num > 0)
    {
        stk->stack_num--;
        *pop_data = stk->stack_data[stk->stack_num];
        return SUCCESS;
    }
    else
    {
        return ERROR;
    }
}

void stackPrint(stack_t *stk)
{
    for (int i = 0; i < stk->stack_num; i++)
    {
        printf("%d", stk->stack_data[i]);
    }
    printf("\n");
}

stack_t init()
{
    return (stack_t){
        stack_num : 0
    };
}

int stackEmpty(stack_t *stk)
{
    int res = stk->stack_num > 0 ? 0 : 1;
    return res;
}

int main(int argc, char *argv[])
{
    stack_t st = init();
    int res = stackEmpty(&st);

    printf("%d: if 1 means empty\n", res);

    for (int i = 0; i < 5; i++)
    {
        push(&st, i);
        stackPrint(&st);
    }
}
