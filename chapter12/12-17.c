// 12-17.c
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;

void prepare(void){
    printf("preparing locks ...\n");
    if(pthread_mutex_lock(&lock1))
        fprintf(stderr, "can't lock lock1 in prepare handler\n");
    if(pthread_mutex_lock(&lock2))
        fprintf(stderr, "can't lock lock2 in prepare handler\n");
}
void parent(void){
    printf("parent unlocking locks ...\n");
    if(pthread_mutex_unlock(&lock1))
        fprintf(stderr, "can't unlock lock1 in parent handler\n");
    if(pthread_mutex_unlock(&lock2))
        fprintf(stderr, "can't unlock lock2 in parent handler\n");
}
void child(void){
    printf("child unlocking locks ...\n");
    if(pthread_mutex_unlock(&lock1))
        fprintf(stderr, "can't unlock lock1 in child handler\n");
    if(pthread_mutex_unlock(&lock2))
        fprintf(stderr, "can't unlock lock2 in child handler\n");
}
void* thr_fn(void *arg){
    printf("thread started ...\n");
    pause();
    return 0;
}

int main(){
    int err;
    pid_t pid;
    pthread_t tid;
    if((err = pthread_atfork(prepare, parent, child)) != 0){
        fprintf(stderr, "can't install fork handlers: %s\n", strerror(err));
        return 1;
    }
    if((err = pthread_create(&tid, NULL, thr_fn, NULL)) != 0){
        fprintf(stderr, "can't create thread: %s\n", strerror(err));
        return 1;
    }
    sleep(2);
    printf("parent about to fork ...\n");
    if((pid = fork()) < 0) {
        perror("fork failed"); return 1;
    }else if (pid==0){
        printf("child returned from fork\n");
    }else{
        printf("parent returned from fork\n");
    }
    return 0;
}

