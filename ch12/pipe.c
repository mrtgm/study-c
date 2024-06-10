
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int pipefd[2]; // read, write でそれぞれ pipe 用の fd を用意
    pid_t cpid;
    char buf;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (pipe(pipefd) == -1) // パイプ作成
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    cpid = fork();
    if (cpid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (cpid == 0)
    {
        close(pipefd[1]); // write 側は close

        while (read(pipefd[0], &buf, 1) > 0) // 1バイトづつ処理
            write(STDOUT_FILENO, &buf, 1);

        write(STDOUT_FILENO, "\n", 1);
        close(pipefd[0]);
        _exit(EXIT_SUCCESS);
    }
    else
    {
        close(pipefd[0]);                           // read 側は close
        write(pipefd[1], argv[1], strlen(argv[1])); // write 用のパイプに繋ぐ
        close(pipefd[1]);
        wait(NULL); // 子プロセスの終了を待つ
        exit(EXIT_SUCCESS);
    }

    exit(0);
}
