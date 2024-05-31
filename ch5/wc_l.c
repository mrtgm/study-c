#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <regex.h>

static void do_wc(const char *path);
static void die(const char *arg);

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        die("you need more argument");
    }

    for (int i = 1; i < argc; i++)
    {
        do_wc(argv[i]);
    }

    exit(0);
}

#define BUFFER_SIZE 2048

int word_counter(const unsigned char *str, const char *target)
{
    int counter = 0; // ここで初期化しないと、count に代入されなかったときに謎の値が入る
    while (*str != '\0')
    {
        if (*str == *target) // ここでポインタが指すアドレスの値を比較している、文字列なので先頭文字の比較になる
        {
            counter++;
        }
        str++; // これは？？　ポインタのアドレスをインクリメントしている？？（*(str + 1) と同じ？）
    }

    // この実装だと1文字と1文字の比較しかできんなあ

    // 文字列とか配列とか、その辺の話をはっきりさせる必要あるなあ
    // このとき str はポインタのアドレスを指している
    // *str == '\0' は、ポインタが指しているアドレスの値が '\0' かどうかを判定している
    // つまり、ポインタが指しているアドレスが '\0' になるまでループを回す

    // 文字列と数値型のかんけいってどうなってたっけ・・・

    return counter;
}

static void do_wc(const char *path)
{
    int fd;
    int counter;
    unsigned char buf[BUFFER_SIZE];

    fd = open(path, O_RDONLY);

    if (fd < 0)
        die(path);

    for (;;)
    {
        int n = read(fd, buf, sizeof buf);
        if (n == 0)
            break;
        if (n < 0)
            die(path);

        printf("%d: result\n", word_counter(buf, "\n"));
    }

    close(fd);
}

static void die(const char *arg)
{
    perror(arg);
    exit(1);
}
