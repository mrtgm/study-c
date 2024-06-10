#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <regex.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    int i;

    if (argc < 2)
    {
        fprintf(stderr, "%s", argv[0]);
        exit(1);
    }

    for (i = 1; i < argc; i++)
    {

        if (argv[i] == "/")
        {
            continue;
        }
        else
        {
            char *p = argv[i];
            while (*p)
            {
                if (*p == '/')
                {
                    *p = '\0'; // 一時的にポインタにヌル文字入れて、文字列を切り出すのか・・・

                    if (mkdir(argv[i], 0777) < 0) // aa/aa/aa -> aa, aa/aa, aa/aa/aa というようにディレクトリを作成していく
                    {
                        if (errno != EEXIST)
                        {
                            perror(argv[i]);
                            exit(i);
                        }
                    }
                    *p = '/';
                }
                p++;
            }
        }
    }
    exit(0);
}
