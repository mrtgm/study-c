#include <stdio.h>
#include <string.h>

int add(int a, int b){
    return a + b;
}

int mysub(int *a, int *b){
    *a = *a - *b; // ポインタから値を取り出して計算, a のアドレスの値を変更
    return *a;
}

int test(int a, int b){
    return a + b;
}


int main(){
    int a = 10, b = 20;
    printf("%d\n", add(a, b));
    printf("%d\n", a);

    // 関数のプロトタイプ、中身は別に定義、関数内に書くこともできる
    int test(int a, int b);

    printf("%d\n", mysub(&a, &b));
    printf("%d\n", a);

    printf("%d\n", test(10, 20));

    // 型変換
    // 式内型変換：演算子の両側で型が異なる場合、大きい方に合わせる

    // 代入型変換：左辺のサイズが右辺より小さい場合、切り捨てられる

    // 型キャスト：明示的に型を変換する

    return 0;
}
