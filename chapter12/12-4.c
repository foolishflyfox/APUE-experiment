// 12-4.c
#include <pthread.h>
#include <stdio.h>

int makethread(void* (*fn)(void*), void *arg){
    pthread_t tid;
    pthread_attr_t attr;
    int err = pthread_attr_init(&attr);
    if(err != 0) return err;
    err = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    if(err == 0) pthread_create(&tid, &attr, fn, arg);
    pthread_attr_destroy(&attr);
    return err;
}

