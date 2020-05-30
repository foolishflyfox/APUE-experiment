// 11-2.c
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_t ntid;
typedef unsigned long ul;
void printids(const char* s){
    pid_t pid = getpid();
    pthread_t tid = pthread_self();
    printf("%s pid %lu tid %lu (0x%lx)\n", s, (ul)pid, (ul)tid, (ul)tid);
}
void* thr_fn(void* arg){
    printids("new thread: ");
    return NULL;
}
int main(){
    int err = pthread_create(&ntid, NULL, thr_fn, NULL);
    if(err!=0){
        fprintf(stderr, "err %d: can't create thread\n", err);
        return 1;
    }
    printids("main thread:");
    sleep(1);
    return 0;
}

