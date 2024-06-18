#include <stdio.h>
#include <string.h>

#define MAX 1000
#define ERROR 1
#define SUCCESS 0

typedef char data_t;

typedef struct
{
    int num;
    data_t data[MAX];
} stack_t;

int push(stack_t *stk, data_t data)
{
    if (stk->num < MAX)
    {
        stk->data[stk->num] = data;
        stk->num++;
        return 0;
    }
    else
    {
        return 1;
    }
}

int pop(stack_t *stk, data_t *pop_data)
{
    if (stk->num > 0)
    {
        *pop_data = stk->data[stk->num];
        stk->num--;
        return 0;
    }
    else
    {
        return 1;
    }
}

int pushOnParenthesis(stack_t *stk, char str)
{
    if (str == '(' || str == '{' || str == '[')
    {
        push(stk, str);
    }
}

int popOnParenthesis(stack_t *stk, char str)
{
    char res;
    char expected;

    switch (str)
    {
    case ')':
        expected = '(';
        break;
    case ']':
        expected = '[';
        break;
    default:
        return 1;
    }

    pop(stk, &res);
    return res == expected; // true-> 1, false-> 0
}

void printStack(stack_t *stk)
{
    for (int i = 0; i < stk->num; i++)
    {
        printf("%c", stk->data[i]);
    }
    printf("\n");
}

int parenthesisCheck(stack_t *stk, char *str)
{
    int ret = 1;
    while (*str != NULL)
    {
        pushOnParenthesis(stk, *str);
        ret = popOnParenthesis(stk, *str);
        str++;

        printStack(stk);

        if (ret == 0)
            break;
    }
    if (stk->num > 0)
        ret = 0;
    return ret;
}

int main()
{
    stack_t st = (stack_t){
        num : 0
    };
    char str[] = "{aaa(a)a}a";
    int res = parenthesisCheck(&st, str);

    printf("%d\n", res);

    return 0;
}

// ３種類の括弧 (), {}, [] を含む文字列において，括弧の対応に整合性がとれているかどうかを判断する関数
// int parenthesisCheck(char str[]) を作れ。この関数は文字列 str 内の括弧の整合性がとれていれば 1 を，とれていなければ 0 を関数値として返す。
// ただし，str 内の括弧以外の文字は無視する。
// もちろん，文字列 str はヌル文字 '\0' で終了しているものとする。
