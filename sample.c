#include <stdio.h> // header file for standard input output（標準入出力）

// データ型
// char, short, int, long, float, double, long double, void

// 入出力や文字列の処理は関数
// printf, scanf, gets, puts, strlen, strcpy, strcmp
// - printf: 出力
// - scanf: 入力
// - gets: 文字列の入力
// - puts: 文字列の出力
// - strlen: 文字列の長さ
// - strcpy: 文字列のコピー
// - strcmp: 文字列の比較

// ソースファイル（xxx.c）をコンパイルして、機械語による実行ファイル（xxx）に変換する
// コンパイル時、
// 1. プリプロセッサ（プリコンパイラ）がソースファイルを解析して、コードを変換する（マクロの展開、コメントの削除、条件付きコンパイル）
// 2. コンパイラがプリプロセッサで変換されたコードを解析して、機械語（アセンブリコード）に変換する（オブジェクトファイルの生成）
// 3. リンカがコンパイラで変換された機械語をリンクして、実行ファイルを生成する

// include 文は、プロジェクトによって処理されることで、指定したファイルをソースファイルに挿入する
// ヘッダファイルは関数のプロトタイプ宣言や定数、構造体、列挙型などを定義する


int main() {
    // int hoge = 10; // 変数の宣言
    // hoge = 30 + 20;


    char ss[10]; // 文字列の宣言

    gets(ss); // 文字列の入力
    printf("%s\n", ss); // 文字列の出力

    printf("\a");

    int dt;
    scanf("%d", &dt); // 数値の入力, & はアドレス演算子
    printf("%d\n", dt); // 数値の出力

    //int 8進数、16進数
    int oct = 010; // 8進数
    int hex = 0x10; // 16進数

    //long（長整数）, unsigned int（符号なし整数）, unsigned long（符号なし長整数）
    //double（倍精度浮動小数点数）, long double（長倍精度浮動小数点数）, float（単精度浮動小数点数）


    // printf("Hello, World!\n"); // 文字列の出力
    // printf("ams=%d\n", hoge); // 変数の出力

    // print + format = printf
    // %d: 10進数, %f: 浮動小数点数, %c: 文字, %s: 文字列

    return 0;
}
