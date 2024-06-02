#include <stdlib.h>
#include <stdio.h>

char *my_strcpy(char *str) // o(2n) だから定数倍なのでOK
{
    int len = 0;
    char *buf;
    while (*(str++) != NULL)
    {
        len++;
    }
    buf = calloc(len + 1, sizeof(char));

    str -= len + 1;

    while (*buf++ = *str++)
        ;

    return buf - (len + 1);
}

char *my_strcpy2(char *str) // o(2n) だから定数倍なのでOK
{
    char *end = str;
    while (*end)
        end++;

    size_t len = end - str; // オブジェクトのサイズを表すときに慣習的に使うやつ
                            // これ、アドレス同士の比較になるから char で割らないと len 取れないんじゃない？？
                            // いや、1byte だからとれるのか・・・

    char *buf = calloc(len + 1, sizeof(char));
    char *start_buf = buf;

    while (*start_buf++ = *str++)
        ;

    return buf;
}

int main(int *argc, char *argv[])
{
    printf("%s\n", my_strcpy2("Hogeeee"));

    return 0;
}
