#include <stdio.h>
#include <string.h>

struct person {
    char *name;
    int age;
};

struct person my_func(struct person p){ //構造体を引数に取る関数、コピーされる
    p.age = 30;
    return p;
};

struct person *my_func_p(struct person *p) {
    p->age = 30;
    return p;
};

int main(){
    struct person p1;
    p1.name = "Alice";
    p1.age = 20;

    printf("%s\n", p1.name);

    //構造体の配列
    struct person persons[10]; //ここは配列の要素数を指定する
    persons[0].name = "Alice Array";
    persons[0].age = 20;

    persons[9].name = "Bob Array";
    persons[9].age = 30;

    printf("%s\n", persons[9].name);

    //すっごい便利な初期化方法
    struct person p2 = {"Alice", 20};
    struct person p3 = {.age = 20, .name = "Alice"}; //こういう書き方もできる
    printf("%s\n", p3.name);

    //構造体同士の代入
    p2 = p3; //型が同じなら代入可能　このとき、p2 に p3 の値がコピーされる

    //構造体のポインタ
    struct person *p4;
    p4 = &p2;
    printf("%s\n", (*p4).name); //メンバーにアクセス
    printf("%s\n", p4->name); //あるいはこう書くこともできる（アロー演算子）
    p4->age = 100;
    printf("%d\n", p2.age); //p4 によって p2 の値が変更されていることがわかる


    //構造体の関数の返り値
    struct person p5 = my_func(p2);
    printf("%d\n", p5.age);

    //構造体を関数の引数に入れる場合など、不要なコピーを防ぐためにポインタ渡しがよく使われる
    struct person *p6 = my_func_p(&p2);
    printf("%p\n", p6); //ポインタ変数が示す変数のアドレス
    printf("%p\n", &p6); //ポインタ変数自身のアドレス
    printf("%p\n", *p6); //ポインタ変数が示す値自体のアドレス

    printf("%p\n", p2); //変数が持つ値自体のアドレス
    printf("%p\n", &p2); //変数のアドレス

    // *p6 = p2 は同じ値を示す

    (*p6).age = 200;
    printf("%d\n", p2.age);

    return 0;
}
