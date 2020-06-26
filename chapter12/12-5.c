// 12-5.c
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

#ifndef MUTEX_TYPE
#define MUTEX_TYPE PTHREAD_MUTEX_NORMAL
#endif

pthread_mutex_t gm1, gm2, gm3;
void* foo(void* argv){
    if(pthread_mutex_lock(&gm2)){
        fprintf(stderr, "foo lock gm2 error\n");
        return NULL;
    }
    sleep(5);
    return NULL;
}
void sig_alrm(int signo){
    printf("3: dead-lock\n");
    _exit(0);
}
int main(){
    pthread_t tid;
    pthread_mutexattr_t mutexattr;
    setbuf(stdout, NULL);
    pthread_mutexattr_init(&mutexattr);
    pthread_mutexattr_settype(&mutexattr, MUTEX_TYPE);
    pthread_mutex_init(&gm1, &mutexattr);
    pthread_mutex_init(&gm2, &mutexattr);
    pthread_mutex_init(&gm3, &mutexattr);
    // 解锁时再解锁
    int err = pthread_mutex_unlock(&gm1);
    if(err==0) printf("1:undefined   ");
    else printf("1:err-%d   ", err);
    // 不占用时解锁
    if(pthread_create(&tid, NULL, foo, NULL)!=0){
        fprintf(stderr, "pthread_create error\n"); 
    }
    err = pthread_mutex_unlock(&gm2);
    if(err==0) printf("2:undefined   ");
    else printf("2:err-%d   ", err);
    // 没有解锁时加锁
    pthread_mutex_lock(&gm3);
    signal(SIGALRM, sig_alrm);
    alarm(3);
    err = pthread_mutex_lock(&gm3);
    if(err==0) printf("3:undefined\n");
    else printf("3:err-%d\n", err);
}

