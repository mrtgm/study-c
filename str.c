#include <stdio.h>
#include <string.h>


int add(int *a, int *b){
    return *a + *b; // ポインタから値を取り出して計算
}

int main(){
    char str[] = "Hello";

    printf("%s\n", str);

    for (int i = 0; i < 5; i++){
        printf("%c\n", str[i]);
    }

    printf("%lu個の文字列\n", strlen(str));

    //数値のコピー
    int a, b;
    a = 20;
    b = a;
    printf("%d\n", b);

    //文字列のコピー
    char str2[10];
    strcpy(str2, str);

    printf("%d\n", strlen(str2));
    printf("%d\n", sizeof(str2));

    // 文字列の比較, == はメモリアドレスの比較になってしまう
    if (strcmp(str, str2) == 0){
        printf("同じ\n");
    } else {
        printf("違う\n");
    }

    // 文字列の連結
    char str3[20] = "Hello, ";
    char str4[10] = "World!";
    printf("%s\n", strcat(str3, str4));
    //str3にstr4を連結するので、str3のサイズは合計値以上である必要がある

    //ポインタきたあああああ

    // ポインタとはメモリのアドレスを保持する変数
    // すべてのプログラムは、メモリ上に展開される（変数も関数も）　その番地をアドレスという
    // OS が任意のアドレスを割り当てる、そのアドレスをポインタが保持する

    // 通常の変数は、実データとメモリのアドレスを保持している
    a = 200;
    printf("%d\n", a); // a の値を表示
    printf("%p\n", &a); // a のアドレスを取り出して表示

    // &: アドレス演算子. 変数のアドレスを取り出す
    // *: 間接演算子, ポインタ変数からアドレスの値を取り出す
    // ポインタ変数の宣言は、変数の型の前に * をつける

    // ポインタ変数は、メモリのアドレスのみを保持する変数
    int *p; // ポインタ変数の宣言
    p = &a; // a のアドレスを p に代入
    printf("%p\n", p); // p の値（a のアドレス）を表示
    printf("%d\n", *p); // メモリのアドレスにある値を取り出して表示

    int z = 300;
    int *p2 = &z; //宣言と取り出しで、おんなじ * が使われるが、意味が違う
    printf("%p\n", p2);
    printf("%d\n", *p2);

    printf("%d\n", *(&a)); // ポインタからアドレス取り出し->アドレスから値取り出し

    // ポインタのポインタ
    // ポインタ変数もメモリ上に保存されているはずなので、そのアドレスを取り出すこともできる
    int **pp = &p; // ポインタのポインタの宣言
    printf("%p\n", pp); // ポインタのポインタの値（p のアドレス）を表示

    int zz = 200;
    int *p3 = &zz;
    printf("%p\n", p3);
    int **pp2 = &p3;
    printf("%p\n", pp2);

    // 配列とポインタ
    // 配列の名前はポインタと同じ 配列の名前は、配列の先頭要素のアドレスを表す

    char mystr[] = "Hello";
    char *p4;
    p4 = mystr; // mystr は配列の先頭要素のアドレスを示す

    printf("%s\n", mystr);
    printf("%p\n", mystr);
    printf("%c\n", *p4); // p4 の値（mystr の先頭要素）を表示

    // 配列はメモリアドレスが連続しているので、ポインタ演算と呼ばれる作業で中身を取り出せる
    int myarrr[] = {10, 20, 30, 40, 50};
    int *p5 = myarrr; // 配列の先頭要素のアドレスをポインタに代入
    printf("%d\n", *p5); // p5 の値（myarrr の先頭要素）を表示
    printf("%p\n", p5);
    printf("%d\n", *(p5 + 2)); // p5 の値（myarrr の先頭要素）に 2 を足して表示
    printf("%p\n", p5 + 2);

    // ポインタの演算
    // CPU は、ポインタの演算を行うとき、ポインタの型のサイズを考慮して演算を行う
    // int 型のポインタの場合、4 バイトずつ移動する（int 型は 4 バイト）
    // char 型のポインタの場合、1 バイトずつ移動する


    // ポインタと文字列
    // 文字列は、char型の配列で、最後にヌル文字（\0）が入る
    char myss[] = "Hello";
    char *p6 = myss;
    printf("%c\n", *p6); // p6 の値（myss の先頭要素）を表示
    // myss = "Hi";  配列には代入できない

    // ポインタ変数に文字列を代入することが可能
    char *mystrr = "Hello World!";
    char *mystrr2;
    printf("%s\n", mystrr); // この辺謎、メモリ的にはどうなってるんだろう（あとヒープとか出てこないけどなんで？？）

    mystrr = "Hi"; // 再代入できる
    printf("%s\n", mystrr);
    printf("%d\n", strlen(mystrr));

    // mystrr2 = strcat(mystrr, "World");
    // printf("%s\n", mystrr2);

    //関数に引数としてポインタ（メモリのアドレス）を渡す
    //ポインタ渡さないと、引数に渡した値はコピーされる、コピーは負担になる
    //参照渡すことで、コピーせずに呼び出し元で大本の変数を変更することができる

    int aaa = 10, zzz = 20;
    int re = add(&aaa, &zzz);
    printf("%d\n", re);

    return 0;
}



