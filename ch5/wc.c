#include <stdio.h>

int main(void)
{
    char str[] = "Sample\n\nText\nMoeMoe";
    char *p = str;
    char *tp;
    char *buf;

    while ((tp = strtok(p, "\n")) != NULL)
    {
        buf = (char *)malloc(strlen(tp) + 1);
        // 動的にメモリを確保できるってことか、buf のサイズはループごとに変動するから動的に確保する必要がある
        strcpy(buf, tp);
        printf("%s\n", buf);
        free(buf);
        p = NULL;
    }
    return 0;
}
