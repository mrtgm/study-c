// マクロは、#include などのように、コンパイル前にプリプロセッサが参照するもの
// コンパイル時に実際のコードに置換される

// 文字列や数値など、グローバルな**定数**、簡単なGetterを定義するときにマクロを使う

#include <stdio.h>
#define MAX 100
#define ADD(a, b) ((a) + (b))

// 組み込みのマクロ
// __FILE__ : ファイル名
// __LINE__ : 行番号
// __DATE__ : コンパイル日付
// __TIME__ : コンパイル時刻
// __func__ : 関数名
// __VA_ARGS__ : 可変長引数


int MAX_I = 200; // これはグローバル変数, mutable

int main(){
    printf("MAX = %d\n", MAX); // 100

    printf("%s\n", __FILE__); // macro.c
    printf("%d\n", __LINE__); // 25行目
    printf("%s\n", __DATE__); // コンパイル日付
    printf("%s\n", __TIME__); // コンパイル時刻
    printf("%s\n", __func__); // main

    //マクロ用の制御構文
    #ifdef MAX
        printf("MAX is defined\n");
    #else
        printf("MAX is not defined\n");
    #endif

    printf("ADD(1, 2) = %d\n", ADD(1, 2)); // 3

    #undef MAX

    //型修飾子
    //何もしなければsigned型になる（半分をマイナス、半分をプラスとして使う）

    int a;
    long int b;
    printf("sizeof(a) = %d\n", sizeof(a)); // 4
    printf("sizeof(b) = %d\n", sizeof(b)); // 8

    signed char c; // char は数値として扱うことができる
    unsigned char d;

    c = 127; //ASCII は 0〜127（128文字）なので、signed char の最大値に収まる
    d = 127;

    printf("c = %d\n", c); // 127
    printf("d = %d\n", d); // 127
    printf("c = %c\n", c); // DEL
    printf("d = %c\n", d); // DEL


    return 0;
}
