// ファイルの先頭から数行を出力する

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define _GNU_SOURCE
#define DEFAULT_N_LINES 10
#include <getopt.h>

// cat test | ./head 5
void die(char *message)
{
    perror(message);
    exit(1);
};

void do_head(FILE *file, int lines);

static struct option longopts[] = {
    {"lines", required_argument, NULL, 'n'},
    {"help", no_argument, NULL, 'h'},
    {0, 0, 0, 0}};

int main(int argc, char *argv[])
{
    int opt;
    long max = DEFAULT_N_LINES;

    if (argc < 2)
        die("arg must be provided");

    while ((opt = getopt_long(argc, argv, "n:", longopts, NULL)) != -1)
    {
        switch (opt)
        {
        case 'n':
            max = atoi(optarg);
            break;
        case 'h':
            fprintf(stdout, "hunga");
            break;
        default:
            fprintf(stdout, "hunga");
            break;
        }
    }

    if (optind == argc)
    {
        do_head(stdin, max);
    }
    else
    {
        for (int i = optind; i < argc; i++)
        {
            FILE *f;
            f = fopen(argv[i], "r");

            if (!f)
            {
                perror(argv[i]);
                exit(1);
            }
            do_head(f, max);
            fclose(f);
        }
    }

    exit(0);
}

void do_head(FILE *file, int lines)
{
    int c;
    while ((c = getc(file)) != EOF)
    {
        if (putchar(c) < 0)
            exit(1);

        if (c == '\n')
        {
            lines--;
            if (lines == 0)
                return;
        }
    }
}

// fgets...buf 限界まで
// fgetc...1byte
// gets
