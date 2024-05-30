#include <stdio.h>

struct struct_nested
{
    struct struct_nested *next;
    int a;
};

struct person
{
    char *name;
    int age;
};

struct company
{
    char *name;
    struct person stuff[10];
};

typedef struct
{
    char *name;
    int age;
} person2;


int main(){

    struct company c1;
    c1.name = "Company1";
    struct person p1 = {"Alice", 20};
    c1.stuff[0] = p1;
    c1.stuff[1] = (struct person){"Bob", 30};
    // 構造体の初期化、配列の場合、複合リテラルってもので一時的な構造体を作る


    struct struct_nested s1;
    s1.next = NULL;

    struct struct_nested s2;
    s1.next = &s2; //ポインタ変数に変数のアドレスを代入

    s1.a = 10;
    s2.a = 20;

    printf("%d\n", s1.a);
    printf("%d\n", s1.next->a); //ポインタ変数のメンバにアクセスするときは、アロー演算子を使う

    // 共用体
    // 構造体と同じように、型の違うメンバをひとつにまとめる
    // 共用体はメモリを共有する
    // 　一度に使えるメンバはひとつだけ
    // 　共用体のサイズは、メンバの中で最も大きいものに合わせられる
    // メモリを節約するために使われる

    union person{
        char name[16];
        int age;
    };

    union person u1 = {"Alice"}; //初期化の方法は構造体と同じ

    printf("%s\n", u1.name);
    printf("%zuバイト\n", sizeof(u1)); //zu は size_t の型指定子

    u1.age = 20;
    printf("%d\n", u1.age);
    printf("%zuバイト\n", sizeof(u1));
    printf("%s\n", u1.name); //一個のメンバしか許さないので、消える

    // 列挙型
    // 列挙型は、整数値に名前をつける
    enum ERROR{
        OK = 0,
        NG = -1
    };

    enum ERROR e = OK;
    printf("%d\n", e);


    return 0;
}
