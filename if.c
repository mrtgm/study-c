#include <stdio.h>
#include <math.h>
#include "myh.h"
// <> は、システムのヘッダファイルを指定する, "" は、ユーザーが作成したヘッダファイルを指定する
// c がソース、h がヘッダ
// ヘッダファイルは、関数のプロトタイプ宣言や定数、構造体、列挙型などを定義する

// CPU のビット数が、コンピュータが一度に処理できる最大のビット数
// 32bit, 64bit

int sum(int a, int b){
    printf("%d\n", a + b);
    return a + b;
}

int diff(int a, int b){
    return a - b;
}

int main(){
    printf("%d\n", 3 + 2);
    myprint();

    struct myh myh1;
    myh1.a = 10;
    myh1.b = 20;
    myh1.c = 30;

    printf("%d\n", myh1.a);

    int result = sum(10,20);
    int result2 = diff(10,20);
    printf("sum:%d\n", result);
    printf("diff:%d\n", result2);

    // char
    char z = 125; // 1バイト(8ビット), -128 ~ 127
    printf("%c\n", z); // } が出力される
    char c = 'A'; // 文字, 1バイト(8ビット), デフォルトは符号付き(-128 ~ 127)
    printf("%c\n", c);
    char s[] = "Hello, World!"; // 文字列
    printf("%s\n", s);


    // 配列
    int arr[5]; // 配列の宣言
    arr[0] = 10; // 配列の初期化
    arr[1] = 20;
    printf("配列:%d\n", arr[0]); // 配列の出力


    // 変数は、メモリ上のアドレスに名前をつけたもの
    // ポインタは、変数のアドレスを格納する変数
    int a = 10;
    int *p; // ポインタの宣言

    p = &a; // ポインタに変数のアドレスを代入
    printf("%d\n", *p); // ポインタの値を出力

    a = 20;
    printf("%d\n", *p); // ポインタも変わる

    *p = 30;
    printf("%d\n", a); // 変数も変わる

    // ポインタの演算
    int b = 10;
    int *q = &b; // ポインタの宣言と初期化
    printf("%d\n", q); // アドレス
    printf("%d\n", q + 1); // アドレス + 1


    int test, test2;
    test = 10;
    test2 = 20;
    if (test == 10){
        printf("testは10です\n");
    } else {
        printf("testは10ではありません\n");
    }

    test > test2 ? printf("testはtest2より大きいです\n") : printf("testはtest2より小さいです\n");

    switch(test){
        case 10:
            printf("testは10です\n");
            break;
        case 20:
            printf("testは20です\n");
            break;
        default:
            printf("testは10でも20でもありません\n");
            break;
    }

    for (int i = 0; i < 10; i++){ //カウンター
        printf("%d\n", i);
    }

    do {
        // 一度は処理を行う, https://zenn.dev/kunosu/articles/86f00193262164285f96
        printf("do while\n");
        break;
        // break でループを抜けられる
        printf("do while??\n");
    } while (0);

    while (0){
        // 一度も処理を行わない
        printf("while\n");
    }


    int abb[2][3];
    abb[0][0] = 10;
    abb[0][1] = 20;
    abb[0][2] = 30;


    // 文字列型、char は1バイト（ASCII 1文字だけ）
    // 文字列を扱いたいときは、char の配列として扱わないとだめ
    // 文字列の終端には、\0（ヌル文字）を入れる、いわゆる番兵
    char str[6];
    str[0] = 'H';
    str[1] = 'e';
    str[2] = 'l';
    str[3] = 'l';
    str[4] = 'o';
    str[5] = 0; // 文字列の終端

    printf("%s\n", str); // "Hello

    char str2[6] = {'H', 'e', 'l', 'l', 'o', 0};
    printf("%s\n", str2);

    char str3[6] = "Hello";
    printf("%s\n", str3);

    char str4[] = "Hello"; //省略可
    printf("%s\n", str4);

    // 文字列の長さ, strlen
    for (int j = 0; j < strlen(str4); j++){
        printf("%c\n", str4[j]);
    }


    // C は正常終了で0を返すのが慣例
    return 0;
}
