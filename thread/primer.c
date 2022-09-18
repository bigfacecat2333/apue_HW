#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pthread.h>
#include <unistd.h>
#include <wait.h>
#include <string.h>

#define LEFT  30000000
#define RIGHT 30000200
#define N     RIGHT - LEFT + 1

static void *handler(void *p)  // 同时跑很多份， p都指向了main中的变量num
{
    int n = *(int *)p;  // 竞争点， 如果num只有一个，n可能还没初始化就有多个线程再用同一个地址
    int i, j, mark;
    for (i = LEFT + n; i <= RIGHT; i += N)
    {
        mark = 1;
        for (j = 2; j <= i / 2; j++)
        {
            if (i % j == 0)
            {
                mark = 0;  // i非质数
                break;
            }
        }
        if (mark)
        {
            printf("%d is a primer [%d]\n", i, n);
        }
    }
    pthread_exit(p);
}

// 交叉算法计算 池类算法涉及到*竞争*
int main()
{
    pthread_t Ptid[N];
    void *ptr = NULL;

    for (int n = 0; n < N; n++)
    {
        int *num = malloc(sizeof(int));
        *num = n;
        int err = pthread_create(Ptid + n, NULL, handler, num);  // 不能直接传n的地址
        if (err)
        {
            fprintf(stderr, "%s\n", strerror(err));
            exit(1);
        }
    }

    for (int n = 0; n < N; n++)
    {
        pthread_join(Ptid[n], ptr); // 回收
        free(ptr);
    }

    exit(0);
}
