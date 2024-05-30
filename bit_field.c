#include <stdio.h>

// ビットフィールドとは
// 1バイト以下の変数を定義するときに、メモリを節約するために使われる
// 通常の下限値は、1バイト(8ビット)だが、ビットフィールドを使うと、1ビットから定義できる


struct normal{
    int a; // 4バイトの変数
};

struct bit_field
{
    unsigned int a : 1; // 1ビットの変数
    unsigned int b : 1; // 1ビットの変数
    unsigned int c : 1; // 1ビットの変数
    unsigned int d : 1; // 1ビットの変数
    unsigned int e : 1; // 1ビットの変数
    unsigned int f : 1; // 1ビットの変数
    unsigned int g : 1; // 1ビットの変数
    unsigned int h : 1; // 1ビットの変数
}; //ビット長を分割して定義することができる


// 複数のメンバが、同じメモリを共有する
// あるメンバによってメモリ空間を変更すると、他のメンバにも影響が及ぶ
// ようは同じメモリ空間に対する getter/setter を複数定義できるってことか・・・　なんかかっこいい

union bit_field_sample
{
    struct bit_field bf;
    unsigned char c;
};

struct hoge {
    int a;
    union {
        struct {
            unsigned int a : 1;
            unsigned int b : 1;
            unsigned int c : 1;
            unsigned int d : 1;
        };
        unsigned char e;
    };
} Hoge;


int main(){
    printf("sizeof(struct normal) = %d\n", sizeof(struct normal)); // 4
    printf("sizeof(struct bit_field) = %d\n", sizeof(struct bit_field)); // 4

    union bit_field_sample bfs;

    bfs.c = 0;
    bfs.bf.a = 1;
    printf("bfs.c = %d\n", bfs.c); // 1

    bfs.c = 0;
    bfs.bf.b = 1;
    printf("bfs.c = %d\n", bfs.c); // 2

    Hoge.e = 0;
    Hoge.a = 1;





    return 0;
}
