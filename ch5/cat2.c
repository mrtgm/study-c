#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void die(char *path);
void do_cat(char *path);

void die(char *path)
{
    char *message = path;
    if (message == NULL)
    {
        message = "undefined error";
    }
    perror(message);
    exit(1);
}

// lseek(2)
// dup(2)
// dup2(2)
// ioctl(2)
// fcntl(2)

void do_cat(char *path)
{
    char buf[2048];
    int fd = open(path, O_RDONLY);

    if (fd < 0)
        die(path);

    for (;;)
    {
        size_t bit_size = read(fd, buf, sizeof buf); // errno 変数をチェック
        if (bit_size < 0)
            die(path);
        if (bit_size == 0)
            break;
        if (write(STDOUT_FILENO, buf, bit_size) < 0)
            die(path);
    }

    if (close(fd) < 0)
        die(path);
}

int main(int argc, char *argv[])
{

    for (int i = 1; i < argc; i++)
    { // 先頭は自身のパス
        do_cat(argv[i]);
    }

    return 0;
}
