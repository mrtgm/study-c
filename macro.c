// マクロは、#include などのように、コンパイル前にプリプロセッサが参照するもの
// コンパイル時に実際のコードに置換される

// 文字列や数値など、グローバルな**定数**を定義するときにマクロを使う

#include <stdio.h>
#define MAX 100

int MAX_I = 200; // これはグローバル変数, mutable

int main(){
    printf("MAX = %d\n", MAX); // 100

    #undef MAX

    return 0;
}
