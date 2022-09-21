#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdarg.h>

#include "proto.h"

#define IPSIZE 1024
#define SERVERPORT "2333" // 一般超过1024

static void debug(char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);

    printf("DEBUG ");
    printf(fmt, va_arg(ap, int));

    va_end(ap);
}

int main()
{
    int sfd;
    struct sockaddr_in laddr; // local addr
    struct sockaddr_in raddr; // remote addr
    struct msg_st *rbuf;
    char ip[IPSIZE];

    int pkglen = sizeof(struct msg_st) + NAMEMAX;
    debug("%d\n", pkglen);
    rbuf = malloc(pkglen);
    if (rbuf == NULL)
    {
        perror("malloc()");
        exit(1);
    }

    sfd = socket(AF_INET, SOCK_DGRAM, 0 /*IPPROTO_UDP*/); // 1 create socket
    if (sfd < 0)
    {
        perror("socket()");
        exit(1);
    }
    // 3 sockaddr create and transform
    laddr.sin_family = AF_INET;                     // 指定协议
    laddr.sin_port = htons(atoi(SERVERPORT));       // 指定网络通信端口 （字节序问题）
    inet_pton(AF_INET, "0.0.0.0", &laddr.sin_addr); // IPv4点分式(指定传输地址全255就是广播)转二进制数 （格式转换问题）

    if (bind(sfd, (void *)&laddr, sizeof(laddr)) < 0)  // 2 bind socket to addr
    {
        perror("bind()");
        exit(1);
    }

    /*！！！！！！*/
    socklen_t raddr_len = sizeof(raddr);
    /*！！！！！！*/
    while (1)
    {
        recvfrom(sfd, rbuf, pkglen, 0, (void *)&raddr, &raddr_len); // 4 报式(无连接)套接字每次通信都需要知道对方是谁
        inet_ntop(AF_INET, &raddr.sin_addr, ip, IPSIZE);
        printf("%s %d\n", ip, ntohs(raddr.sin_port));
        printf("%s %d %d\n", rbuf->name, ntohl(rbuf->math), ntohl(rbuf->chinese));
        fflush(NULL);
    }

    close(sfd);  // 5

    exit(0);
}
