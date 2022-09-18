#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

void *func(void *p)
{
    while(1)
    {
        pause();
    }
    pthread_exit(NULL);
}

int main()
{
    int i;
    pthread_t tid;
    for(i = 0; ; i++)
    {
        int err = pthread_create(&tid, NULL, func, NULL);
        if(err)
        {
            fprintf(stderr, "pthread_create():%s\n", strerror(err));
            break;
        }
    }
    printf("%d\n",i);
}