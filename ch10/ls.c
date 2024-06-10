#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>

static void do_ls(char *path);

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        fprintf(stderr, "%s: no arg", argv[0]);
        exit(1);
    }

    for (int i = 1; i < argc; i++)
    {
        do_ls(argv[i]);
    }

    return 0;
}

static void do_ls(char *path)
{
    DIR *d;
    struct dirent *ent;

    d = opendir(path); // 構造体ストリームを返す、FILE の DIR 版
    if (!d)
    {
        perror(path);
        exit(1);
    }

    while (ent = readdir(d)) // struct dir を返す　ディレクトリエントリ、ディレクトリを表す構造体
    {
        printf("%s\n", ent->d_name);
    }
    closedir(d);
}
