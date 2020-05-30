// thread-exit.c
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void* thread_foo(void* _){
    printf("start thread\n");
    sleep(1);
    printf("exit thread\n");
    _exit(1);
    return NULL;
}

int main(){
    pthread_t tid;
    int err = pthread_create(&tid, NULL, thread_foo, NULL);
    printf("after pthread_create\n");
    sleep(3);
    printf("exit main\n");
}

