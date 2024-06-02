#include <stdio.h>

void func(int (*ary)[3]) // （int * を3個分の配列）の配列 ary
{
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("ary[%d][%d]=%d\n", i, j, ary[i][j]);
        }
    }
}

int main(void)
{
    int ary2[][3] = {
        {1, 2, 3}, {4, 5, 6}};

    func(ary2);

    return 0;
}
