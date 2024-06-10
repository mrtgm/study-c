
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void die(char *message)
{
    perror(message);
    exit(1);
};

int main(int argc, char *argv[])
{
    FILE *f;

    if (argc > 2 || argc == 1)
    {
        die("arg must be only filename");
    }

    if ((f = fopen(argv[1], "r")) == NULL)
        die("file open error");

    for (int i = 1; i < argc; i++)
    {
        for (;;)
        {
            char buff[16];
            size_t read = fread(buff, sizeof(char), sizeof buff, f); // fread は \0 終端を期待しない
            if (ferror(f))
                die("error");
            size_t written = fwrite(buff, sizeof(char), read, stdout); // ここは read のサイズか、そりゃそうか・・・
            if (written < read)
                die("error");
            if (read < sizeof buff) // 読み込み終わったと見なし、ループを抜ける
                break;
        }
    }
}
