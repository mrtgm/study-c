#include <stdio.h>
#include <ctype.h>

static void upper(char *str)
{
    char *p = str;

    while ((*p++ = (char)toupper((int)(*str++)))) //*str が先に評価されてから加算されるから、これは　*p++='\0'（今の文字を0埋めして次に）を覚えておけばOK
        ;
}

int main(void)
{
    char hoge[] = "testaaaa";

    upper(hoge);

    printf("%s\n", hoge);

    return 0;
}
