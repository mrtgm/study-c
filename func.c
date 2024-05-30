#include <stdio.h>
#include <string.h>

int add(int a, int b){
    return a + b;
}

int mysub(int *a, int *b){ // ポインタを引数に取る
    *a = *a - *b; // ポインタから値を取り出して計算, a のアドレスの値を変更
    return *a;
}

int test(int a, int b){
    return a + b;
}

void rec(int n){
    if (n == 0){
        return;
    }else {
        printf("%d\n", n);
        rec(n - 1);
    }
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

    int arr[] = {1,2,3};
    *arr = 10;
    printf("%d\n", *arr);

    // 型変換
    // 式内型変換：演算子の両側で型が異なる場合、サイズが大きい方に合わせる
    // 代入型変換：左辺のサイズが右辺より小さい場合、切り捨てられる
    // 型キャスト：明示的に型を変換する

    //式内型変換
    int x = 10;
    double y = 20.5;
    printf("%f\n", x + y); // 30.500000

    //代入型変換
    int c = y;
    printf("%d\n", c); // 20

    double d = 124.5;
    printf("%d\n", (int)d); // 124

    //再帰
    rec(10);

    //値渡し、参照渡し

    //値渡しはコピーされる、参照渡しは変数のアドレスを引数として渡す
    int new_a = mysub(&a, &b); // 参照渡し
    printf("%d\n", new_a); // -10 - 20 = -30

    double new_d;
    // scanf("%lf", &new_d); //参照渡ししてるので、値が書き換わる
    // printf("%f\n", new_d);

    struct student {
        char name[20];
        int age;
    };

    struct student s;

    // s.name = "taro"; エラー、なぜなら配列に直接代入できない、ポインタ経由で代入する

    // ポインタ演算
    char *p = s.name;
    *p = 't';
    *(p + 1) = 'a';
    *(p + 2) = 'r';
    *(p + 3) = 'o';
    // ポインタ演算の簡易な書き方
    s.name[0] = 't';
    s.name[1] = 'a';
    s.name[2] = 'r';
    s.name[3] = 'o';

    // もしくは
    strcpy(s.name, "taro");

    printf("%s\n", s.name);

    struct new_student {
        char* name;
        int age;
    } s1, s2; //構造体の定義とセットで宣言できる

    s1.name = "taro"; // ポインタなので代入できる
    s2.name = "jiro";

    printf("%s\n", s1.name);
    printf("%s\n", s2.name);


    // typedef struct を使って構造体を宣言することもできる
    typedef struct{
        char *name;
        int age;
    } person2; //名前は後置

    person2 p2; //変数を宣言するとき、struct は不要


    char hongg[20] = "hello";
    char *pnnn = hongg; // ポインタの型は配列の型と一致させる
    *pnnn = 'H'; // ポインタを使って配列の値を変更
    *pnnn++;
    *pnnn = 'E';
    *pnnn++;
    *pnnn = 'L';

    printf("%s\n", hongg);

    return 0;
}
