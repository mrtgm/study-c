#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>
#include <errno.h>
#include <string.h>

#define MAX_EVENTS 10
#define BUFFER_SIZE 1024

void handle_error(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

int main()
{
    int kq, nev, fd1, fd2;
    struct kevent changes[2];
    struct kevent events[MAX_EVENTS];
    char buffer[BUFFER_SIZE];

    // Open files
    fd1 = open("file1.txt", O_RDONLY | O_NONBLOCK);
    if (fd1 == -1)
        handle_error("open file1");

    fd2 = open("file2.txt", O_RDONLY | O_NONBLOCK);
    if (fd2 == -1)
        handle_error("open file2");

    // Create kqueue
    kq = kqueue();
    if (kq == -1)
        handle_error("kqueue");

    // Initialize kevent structures
    EV_SET(&changes[0], fd1, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
    EV_SET(&changes[1], fd2, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);

    // Event loop
    while (1)
    {
        nev = kevent(kq, changes, 2, events, MAX_EVENTS, NULL);
        printf("events length: %d\n", nev);

        if (nev == -1)
        {
            if (errno == EINTR)
                continue; // Interrupted by signal
            handle_error("kevent");
        }

        for (int i = 0; i < nev; ++i)
        {
            int read_fd = events[i].ident;
            ssize_t bytes_read = read(read_fd, buffer, BUFFER_SIZE);

            printf("???? %zd bytes from fd %d\n", bytes_read, read_fd);

            if (bytes_read == -1)
            {
                printf("Closed file descriptor %d\n", read_fd);

                if (errno != EAGAIN)
                    handle_error("read");
            }
            else if (bytes_read == 0)
            {
                // End of file
                close(read_fd);
                printf("Closed file descriptor %d\n", read_fd);
            }
            else
            {

                // Successfully read data
                buffer[bytes_read] = '\0'; // Null-terminate for printing
                printf("Read %zd bytes from fd %d: %s\n", bytes_read, read_fd);
            }
        }
    }

    // Cleanup
    close(fd1);
    close(fd2);
    close(kq);
    return 0;
}
