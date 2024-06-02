#include <stdio.h>

int p_funk(int *inn) // ポインタ変数、アドレスしか受け付けない
{
    // inn + 100;
    // return inn;
    printf("%p\n", inn); // ポインタ変数
    return *inn;         // 値を返却
}

int p_funk2(char arr[]);
int p_funk3(char *arr[]);
int p_funk4(int a, int b)
{
    return a + b;
}

// 関数ポインタを引数に取る関数
int p_funk5(int (*func)(int, int), int a, int b)
{
    printf("%d: p_funk5\n", func(a, b));
    return func(a, b);
}

// *s++ = *t++ について
void strcpy(char *s, char *t)
{
    while (*s++ = *t++) // 前置と後置、後置はすべてが先に行われる
                        // 1.*tが評価される
                        // 2.tに加算される
                        // 3.*sが評価される（値が*s（アドレス）に書きこまれる）
                        // 4.sが加算される
        ;
};

// 関数ポインタ

int main(void)
{

    int i;
    int *pi = &i;  // int* を int* へ。同じ型なので問題なし。
    void *pv = &i; // int* を void* へ。問題なし。

    void (*(*comp_fn)[3])(void *(*[])(void));

    // 関数ポインタ
    int (*p_func[2])(int, int); // 関数ポインタの配列
    p_func[0] = p_funk4;
    p_func[1] = p_funk4;

    for (int i = 0; i < 2; i++)
    {
        printf("%d\n", p_func[i](1, 2));
    }

    // 関数を受け取る関数ポインタ

    int (*p_func10)(int (*)(int, int)); // 関数ポインタを引数に取る関数ポインタ
    int (*p_func20)(void (*[])(void));
    int (*p_funk30)(void (*)(void));

    p_funk5(p_funk4, 1, 2);

    int p = 10;   // 値が所有するアドレスの取得
    int *pq = &p; // ポインタ変数の宣言, アドレスしか渡せない
    *pq += 10;    // 値を変更

    int p2;
    p2 = p++;
    printf("%d\n", p2);

    // pq += 1; アドレス自体の変更(これは segmentation fault になる)

    printf("%d\n", p);
    printf("%p\n", &p);
    printf("%p\n", pq);

    p_funk(&p);
    p_funk(pq);
    // p_funk(p);　int *arg を期待する関数に値は渡せない
    // p_funk(*pq);
    // p_funk(100000);

    char my_arr[4] = {'A', 'B', 'C', '\0'};
    char my_arr2[8] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', '\0'};

    printf("%s\n", my_arr);          //%は変換
    printf("%p\n", my_arr);          // my_arr は先頭のポインタ
    printf("%c\n", *my_arr);         // ポインタが示すのは先頭の値
    printf("%lu\n", sizeof my_arr);  // 4
    printf("%lu\n", sizeof my_arr2); // 8
    printf("%lu\n", sizeof *my_arr); // 1

    //*++argv[0]
    // 配列の先頭を示すポインタにひとつ加算してから値を取り出す

    printf("%c\n", *(my_arr + 1)); // B アドレスを一つ先に進める

    printf("%c\n", my_arr[1]);   // B
    printf("%c\n", ++*my_arr);   // 1. * + my_arr が先に評価され、値が得られる
                                 // 2. 値に加算される (A->B)
    printf("%c\n", ++my_arr[0]); // 1. my_arr[0]が先に評価され、値が得られる
                                 //  1. my_arr[0] = *(my_arr + 0)
                                 //  2. my_arr が評価され、値が得られる
                                 // 2. 値に加算される (B->C)
    printf("%c\n", (*my_arr)++); // 1. *my_arr が先に評価され、値が得られる
                                 // 2. 値に加算される（C->D）

    // printf("%c\n", *my_arr++);
    // error: lvalue required as increment operand,
    // lvalue ... 左辺値
    // ++ は modifiable（変更可能な）左辺値に対してしか使えない、配列に対しては使えない
    // ポインタ変数に対しては使える

    printf("%c\n", my_arr[0]); // A
    printf("%s\n", my_arr);    // A

    char *p_a = my_arr;
    printf("%lu\n", sizeof p_a);

    char a = 'A';
    char b = 'B';

    char *p_arr[2]; // ポインタの配列
    p_arr[0] = &a;
    p_arr[1] = &b;

    p_funk2(my_arr);
    p_funk3(p_arr);

    int ary[3] = {1, 2, 3};
    int(*p_man)[3] = &ary; // 配列の要素をバラし、各要素へのポインタ配列にする記法
    printf("%d\n", p_man[0][0]);

    return 0;
}

int p_funk2(char arr[]) // Cでは配列を引数として渡せない、ポインタを渡すことになる
                        // char *arr と同義
                        // 配列を期待する関数であっても char *arr のように書くのが普通
{
    printf("%c:p_funk2\n", *arr);

    int count = 0;
    while (*(arr + count) != '\0') // NULL 文字を見つけるまでポインタに加算し、アドレスを増やす
    {
        count++;
    }

    printf("%d\n", count);               // 文字数
    printf("%lu:p_funk2\n", sizeof arr); // 8、ポインタのサイズ

    return count;
};

int p_funk3(char *arr[]) // ポインタの配列を期待する
                         // charr **arr と同義
{
    int count = 0;
    printf("%c\n", **arr);
    printf("%c\n", *arr[0]);
    printf("%c\n", *arr[1]);

    while (arr[count] != NULL) // まず手前の配列の終端を確認する必要ある
    {
        if (*(arr[count]) != NULL) // 奥側の配列の終端確認を && にして while 文に書くとエラーする、なぜかは不明・・・
            return 0;
        count++;
    }

    for (int i = 0; i < count; i++)
    {
        printf("%c\n", *(arr[i]));
    }
    return count;
};
