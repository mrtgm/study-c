#include <stdio.h>

int main (int argc, char *argv[]){
    // 引数は char 型のポインタの配列
    printf("Hello, World\n"); //argv[0]には実行ファイルのパスが入る


    printf("argc=%d\n", argc); // 引数の数

    for (int i=0; i < argc; i++) {
        printf("argv[%d]=%s\n", i, argv[i]);
    }

    return 0;
}
