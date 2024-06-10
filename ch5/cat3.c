
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++)
    {
        FILE *f;

        char *path = argv[i];
        f = fopen(path, "r"); // FILE へのポインタ作成、readonly
        if (!f)
        {
            perror(path);
            exit(1);
        }

        int c;
        while ((c = fgetc(f)) != EOF) // EOFに達した or エラーの場合はEOFを返す
        {
            switch (c)
            {
            case '\t':
                fputs("!IJI", stdout);

            case '\n':
                fputs("$t", stdout);

            default:
                if (putchar(c) < 0) // putchar は putc(c, stdout) の意味
                    exit(1);
            }
        };

        fclose(f);
    }

    return 0;
}
