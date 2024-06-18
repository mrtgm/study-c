#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 100
#define SUCCESS 1
#define FAILURE 0

typedef int data_t;

data_t stack_data[STACK_SIZE];
int stack_num;

int push(data_t push_data)
{
    if (stack_num < STACK_SIZE)
    {
        stack_data[stack_num] = push_data;
        stack_num++;
        return SUCCESS;
    }
    else
    {
        return FAILURE;
    }
}

int pop(data_t *pop_data)
{ // スタックの最後を pop_data に入れて削除
    if (stack_num > 0)
    {
        stack_num--;
        *pop_data = stack_data[stack_num];
        return SUCCESS;
    }
    else
    {
        return FAILURE;
    }
}

void stackPrint()
{
    for (int i = 0; i < stack_num; i++)
    {
        printf("%d", stack_data[i]);
    }
    printf("\n");
}

int main()
{

    stack_num = 0;
    for (int i = 0; i <= 5; i++)
    {
        push(i);
        stackPrint();
    }

    for (int i = 0; i <= 5; i++)
    {
        data_t popped;
        pop(&popped);
        printf("%d: popped\n", popped);
        stackPrint();
    }

    // int a[100000000000];
    // a[100000000000] = 2;

    // printf("%d\n", a[100000000000]); // segmentation fault

    // int *a2 = (int *)malloc(sizeof(int) * 100000000000); // ヒープに確保
    // a2[100000000000] = 2;
    // printf("%d\n", a2[100000000000]);

    return 0;
}
