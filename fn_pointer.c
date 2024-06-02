#include <stdio.h>

void *fn(int a, int b)
{
    printf("%d\n", a + b);
}

void *fn2(void *(*inner)(int, int)) // 関数ポインタ
{
    return inner(3, 4);
}

void *fn3(void *(*inner[])(int, int))
{ // 関数ポインタの配列
    inner[0](3, 4);
}

int main(int argc, char *argv[])
{
    void *(*pfn)(int, int); // 関数ポインタ
    pfn = fn;

    pfn(1, 2);

    typedef void *(*fn_item)(int, int); // 関数ポインタの型定義
    fn_item fn_array[3];                // 関数ポインタの配列

    fn_array[0] = fn;
    fn_array[0](1, 2);

    void *(*fn_array2[3])(int, int); // 関数ポインタ3個分の配列
    fn_array2[0] = fn;
    fn_array2[0](1, 2);

    typedef fn_item fn_item_array[3]; // 関数ポインタ3個分の配列の、さらに配列
    fn_item_array fn_array3[0] = {
        fn,
        fn,
        fn};
    fn_array3[0][0](1, 2);

    void *(*fn_array4[][3])(int, int) = {
        fn,
    }; // 関数ポインタの多重配列

    fn_array4[0][0](1, 2);

    // 関数ポインタを引数に取る関数
    typedef void *fn_arg_fn(void *(*)(int, int));
    // 関数ポインタの配列を引数に取る関数
    typedef void *fn_arg_fns(void *(*[])(int, int));

    // 関数ポインタの配列を引数に取る関数の、そのポインタ3個分の配列
    typedef fn_arg_fns *fn_arg_fns_item[];

    void *(*fn_arg_fns_array[3])(void *(*[])(int, int)) = {
        fn3};

    void *(*fn_arg_fns_args[3])(int, int) = {
        fn};

    fn_arg_fns_array[0](fn_arg_fns_args);

    int ten[] = {10};
    int *p = ten;
    // p++; // ランダムな値が入るなぁ

    printf("%d\n", p == NULL);
    printf("%d\n", p[0]);
    // printf("%d\n", p[1]);
}
