#include <sys/types.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

// int regcoomp

int do_grep(regex_t *pat, FILE *src)
{
    char buf[4096]; // 2^11

    while (fgets(buf, sizeof buf, src)) // バッファから１行ごとに取り出してチェック
    {
        if (regexec(pat, buf, 0, NULL, 0) == 0) // regexec(正規表現, 対象文字列, 0, NULL, 0)
        {
            fputs(buf, stdout);
        };
    }
}

int main(int argc, char *argv[])
{
    regex_t pat;
    int err;
    int i;

    if (argc < 2)
    {
        fputs("なんか入れろ", stdout);
        exit(1);
    }

    printf(argv[1]);

    err = regcomp(&pat, argv[1], REG_EXTENDED | REG_NOSUB | REG_NEWLINE); // メモリ領域に正規表現を割り当て,regfree で解放
    if (err != 0)
    {
        char buf[1024]; // 1024 = 2^10

        regerror(err, &pat, buf, sizeof buf);
        puts(buf);
        exit(1);
    }

    if (argc == 2)
    {
        do_grep(&pat, stdin);
    }
    else
    {
        for (i = 2; i < argc; i++)
        {
            FILE *f;

            f = fopen(argv[i], "r");
            if (!f)
            {
                perror("fuck, invalid file");
                exit(1);
            }
            do_grep(&pat, f);
            fclose(f);
        }
    }
    regfree(&pat);
    exit(0);
}
