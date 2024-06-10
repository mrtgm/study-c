#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    pid_t pid;

    if (argc != 3)
    {
        fprintf(stderr, "Usage %s\n", argv[0]);
        exit(1);
    };

    pid = fork(); // プロセスの複製、以降の処理は２つのプロセスで行われる

    fprintf(stdout, "process %s, pid %d\n", argv[0], pid);

    if (pid < 0)
    {
        fprintf(stderr, "error %s\n", argv[0]);
        exit(1);
    }

    if (pid == 0) // 子プロセスの方で呼ばれる処理
    {
        execl(argv[1], argv[1], argv[2], NULL);
        perror(argv[1]); // 　呼び出しから戻ったら失敗
        exit(99);
    }
    else
    {
        // 親プロセスで呼ばれる処理、pid は子プロセスのプロセスID
        int status;

        waitpid(pid, &status, 0);
        printf("child finished: %d\n", pid);
        if (WIFEXITED(status))
            printf("exit status=%d\n", WEXITSTATUS(status));
        else if (WIFSIGNALED(status))
            printf("signal sig=%d\n", WTERMSIG(status));
        else
            printf("abnormal exit\n");
        exit(0);
    }

    return 0;
}
