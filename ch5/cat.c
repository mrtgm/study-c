#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// cat a b c > out
// ファイル名をひとつ以上受け取り、その中身を標準出力に書き込む

static void do_cat(const char *path);
static void do_cat_from_stdin();
static void die(const char *s);

int main(int argc, char *argv[])
{
    int i;

    // argc はデフォルトでひとつ
    if (argc < 2)
    {
        do_cat_from_stdin();
    }

    for (i = 1; i < argc; i++)
    {
        do_cat(argv[i]);
    }
    exit(0);
}

#define BUFFER_SIZE 2048

static void do_cat_from_stdin()
{
    int n;
    unsigned char buf[BUFFER_SIZE];

    for (;;)
    {
        n = read(STDIN_FILENO, buf, sizeof buf);
        if (n == 0)
            break;
        if (n < 0)
            die("error read from stdin");
        if (write(STDOUT_FILENO, buf, n) < 0)
            die("error read from stdin");
    }
    if (close(STDIN_FILENO) < 0)
        die("error read from stdin");
};

static void do_cat(const char *path)
{
    int fd;
    unsigned char buf[BUFFER_SIZE];
    int n;

    fd = open(path, O_RDONLY); // 読み込み専用（O_RDONLY）としてファイルを開く
                               // ファイルディスクリプタを返す
    if (fd < 0)
        die(path); // ファイルが開けなかった場合のエラーチェック

    for (;;)
    {
        n = read(fd, buf, sizeof buf); // ファイルディスクリプタが示すストリームから、buf に読み込む
                                       // 読み込んだバイト数を返す
        if (n < 0)
            die(path); // 読み込みエラーチェック
        if (n == 0)
            break; // 読み込みが終わったらループを抜ける
        if (write(STDOUT_FILENO, buf, n) < 0)
            die(path); // 読み込んだデータを標準出力に書き込む、エラーチェック
    }
    if (close(fd) < 0)
        die(path); // ファイル閉じつつエラーチェック
}

static void die(const char *s)
{
    perror(s); // 標準エラー出力にエラーメッセージを出力
    exit(1);
}

// C では成功なら 0 以上の整数を返す、失敗なら -1 を返すのが一般的
