#include <stdio.h>
#include <stdlib.h>

extern char **environ;

int main(void)
{
    char **p;

    for (p = environ; *p; p++)
    {
        printf("%s\n", *p);
    }

    return 0;
}
