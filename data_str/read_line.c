#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>

#define ALLOC_SIZE 256

// 行を読み込むバッファ
static char *st_line_buffer = NULL;

// バッファのサイズ
static int st_current_buffer_size = 0;

// バッファの中で、現在の文字列の長さ
static int st_current_used_size = 0;

// st_line_buffer の末尾に１文字追加
// バッファが足りない場合は、拡張する
static void add_character(int ch)
{
    assert(st_current_buffer_size >= st_current_used_size); // いきなりバッファが足りないとかおかしいので、assert でチェック

    // st_current_used_size がバッファに追いついたら拡張
    if (st_current_buffer_size >= st_current_used_size)
    {
        st_line_buffer = realloc(st_line_buffer, (st_current_buffer_size + ALLOC_SIZE) * sizeof(char));
        st_current_buffer_size += ALLOC_SIZE;
    }

    st_line_buffer[st_current_used_size] = ch;
    st_current_buffer_size++;
}

// fp から1行読み込む
// 末尾なら NULL
char *read_line(FILE *fp)
{
    int ch;
    char *ret;

    st_current_used_size = 0;

    while ((ch = getc(fp)) != EOF)
    {
        if (ch == '\n')
        {
            add_character('\0');
            break;
        }
        add_character(ch);
    }
    if (ch == EOF)
    {
        if (st_current_used_size == 0)
        {
            return NULL;
        }
        add_character('\0');
    }

    ret = malloc(sizeof(char) * st_current_used_size);
    strcpy(ret, st_line_buffer);

    return ret;
}

void free_buffer(void)
{
    free(st_line_buffer);
    st_line_buffer = NULL;
    st_current_buffer_size = 0;
    st_current_used_size = 0;
}
