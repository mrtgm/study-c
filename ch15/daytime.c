#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

static int open_connection(char *host, char *service);

int main(int argc, char *argv[])
{
    int sock;
    FILE *f;
    char buf[1024];

    sock = open_connection((argc > 1 ? argv[1] : "localhost"), "daytime");
    f = fdopen(sock, "r");
    if (!f)
    {
        perror("fdopen(3)");
        exit(1);
    }

    fgets(buf, sizeof buf, f);
    fclose(f);
    fputs(buf, stdout);
    exit(0);
}

static int open_connection(char *host, char *service)
{
    int sock;
    struct addrinfo hints, *res, *ai;
    int err;

    memset(&hints, 0, sizeof(struct addrinfo)); // 0埋め
    hints.ai_family = AF_UNSPEC;                // ヒント：アドレスファミリーはなんでもいい
    hints.ai_socktype = SOCK_STREAM;            // ヒント：TCP を使う

    if ((err = getaddrinfo(host, service, &hints, &res)) != 0) // IPへ名前解決
    {
        fprintf(stderr, "getaddrinfo(3): %s\n", gai_strerror(err));
        exit(1);
    }

    // getaddrinfo の戻り値はリンクリスト、for で取り出し、最初にうまく行ったものを使う
    // IPv4, IPv6 両方返してくるとか

    for (ai = res; ai; ai = ai->ai_next)
    {
        sock = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
        if (sock < 0)
        {
            continue;
        }
        if (connect(sock, ai->ai_addr, ai->ai_addrlen))
        {
            close(sock);
            continue;
        }

        freeaddrinfo(res);
        return sock;
    }

    fprintf(stderr, "socket(2)/connect(2) failed");
    freeaddrinfo(res);
    exit(1);
}
