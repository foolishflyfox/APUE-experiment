// mutex_lock-ret.c
#include <stdio.h>
#include <pthread.h>
#include <errno.h>

pthread_mutex_t g_lock;

void* foo(void* argv){
    printf("foo begin\n");
    if(pthread_mutex_lock(&g_lock)==0){
        printf("lock g_lock\n");
    }else{
        printf("fail to lock g_lock\n");
    }
    printf("foo end\n");
    return NULL;
}
int main(){
    pthread_t tid;
    pthread_mutexattr_t mutexattr;
    printf("EOWNERDEAD = %d\n", EOWNERDEAD);
    if(pthread_mutexattr_init(&mutexattr)!=0){
        fprintf(stderr, "pthread_mutexattr_init error\n"); return 1;
    }
    if(pthread_mutexattr_setrobust(&mutexattr, PTHREAD_MUTEX_ROBUST)!=0){
        fprintf(stderr, "pthread_mutexattr_setrobust error\n"); return 1;
    }
    if(pthread_mutex_init(&g_lock, &mutexattr)!=0){
        fprintf(stderr, "pthread_mutex_init error\n"); return 1;
    }
    if(pthread_create(&tid, NULL, foo, NULL)){
        fprintf(stderr, "pthread_create error\n"); return 1;
    }
    pthread_mutexattr_destroy(&mutexattr);
    void* tret;
    if(pthread_join(tid, &tret)){
        fprintf(stderr, "pthread_join error\n"); return 1;
    }
    int err = pthread_mutex_lock(&g_lock);
    printf("pthread_mutex_lock return %d\n", err);
}
