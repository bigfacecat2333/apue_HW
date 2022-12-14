#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>

#define CPS     10
#define BUFSIZE CPS
#define BURST   100

static volatile int token = 0;
// volatile：去这个数值的真正的空间（地址的所指位置）去取数值，而非cache中的值

static void alrm_handler(int s)
{
    alarm(1);
    token++;
    if(token > BURST)
        token = BURST;
}

int main(int argc, char *argv[])
{
    int sfd, dfd = 1;
    char buf[BUFSIZE];
    int len, ret, pos;

    if (argc < 2)
    {
        fprintf(stderr, "Usage....\n");
        exit(1);
    }

    signal(SIGALRM, alrm_handler);
    alarm(1);

    do
    {
        sfd = open(argv[1], O_RDONLY);
        if (sfd < 0)
        {
            if (errno != EINTR)
            {
                perror("open()");
                exit(1);
            }
        }
    } while (sfd < 0);

    while (1)
    {
        while (token <= BURST)
            pause();
        token--;

        while((len = read(sfd, buf, BUFSIZE)) < 0)
        {
            if (errno == EINTR)
                continue;
            perror("read()");
            break;
        }
        if (len == 0)
        {
            break;
        }
        pos = 0;
        while (len > 0)
        {
            ret = write(dfd, buf + pos, len);
            if (ret < 0)
            {
                if (errno == EINTR)
                    continue;
                perror("write()");
                exit(1);
            }
            pos += ret;
            len -= ret;
        }
    }

    close(sfd);
    exit(0);
}