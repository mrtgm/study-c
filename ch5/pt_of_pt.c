#include <stdio.h>

typedef struct
{
    int i
} st;

int main()
{
    st a = (st){4};
    st b = (st){8};
    st c = (st){12};

    st *p = NULL;
    st **pp = &p;

    *pp = &b;

    printf("%d\n", p->i);

    *pp = &c;

    st *p2 = &a;
    pp = &p2; // うわなるほど。。。。。参照先に書き込むか、変数を更新するかの違いか。。。。。。基本だった。。。

    printf("%d\n", p->i);

    return 0;
}
