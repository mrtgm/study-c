
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

    f = fopen(argv[1], "r");
    if (!f)
        die("file open error");

    int c = 0;
    char buf[2048];
    for (;;)
    {
        fgets(buf, sizeof buf, f);

        if (ferror(f))
            die("error reading");
        if (feof(f))
        {
            c++;
            break;
        }

        c++;
    }

    printf("%d\n", c);

    return 0;
}
